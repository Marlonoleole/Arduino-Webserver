/*
 * USART0.h
 *
 * Created: 20/04/2019 18:56:08
 *  Author: Marlon Abeln
 */ 


#ifndef USART0_H_
#define USART0_H_
#include "String.h"
#include <math.h>
#include <avr/interrupt.h>
using Standard::string;

void USART0_Transmit(unsigned char data);
void Serial0_WriteString(string message);
void Serial0_PrintString(string message);

#ifndef USART0_BUFFER_SIZE
# warning "USART0 Buffer Size not defined"
#define USART0_BUFFER_SIZE 120
#endif
#ifndef USART0BAUD
# warning "NO USART0 BAUDRTATE DEFINED"
#define USART0BAUD 9600
#endif
#ifndef F_CPU
# warning "F_CPU not defrined for USART0"
#define F_CPU 16000000UL
#endif

char  *USART0_Buffer_=0;
volatile unsigned int USART0_Read_Pos_ = 0;
volatile unsigned int USART0_Write_Pos_ = 0;

#ifdef USART0DOUBLE
#define USART0_UBAUD (int)round(((((double)F_CPU / ((double)USART0BAUD * 8.0))) - 1.0))
#else
#define USART0_UBAUD (int)round(((((double)F_CPU / ((double)USART0BAUD * 16.0))) - 1.0))
#endif

void USART0_Init()
{
	/* Enable Interrupts */
	SREG|=0x80;
	#ifdef USART1DOUBLE
	UCSR1A=(1<<U2X1);
#endif
	/* Enable receiver and Transmitter receive interrupts */
	UCSR0B=(1<<RXEN0|1<<TXEN0|1<<RXCIE0);
	/* Setting Baud Rate */
	UBRR0H=(unsigned int)(USART0_UBAUD>>8);
	UBRR0L= (unsigned int) USART0_UBAUD;
	/* Set frame format: 8data, 2 stop bit */
	UCSR0C=(1<<USBS0 | 3<<UCSZ00);
	/* Spawning the buffer */
	if(!USART0_Buffer_)
		USART0_Buffer_ = new char[USART0_BUFFER_SIZE];
} // USART0_Init

void USART0_Transmit(unsigned char data)
{
	/* wait for empty transmit buffer */
	while(!(UCSR0A & (1<<UDRE0)));
	
	/* Putting data into buffer to send the data */
	UDR0 = data;
}

unsigned char USART0_Receive( void )
{
	/* wait for data to be received */
	while(!(UCSR0A & (1<<RXC0)));
	
	/* Getting and returning received data */
	unsigned char data = UDR0;
	return data;
}
bool Serial0_Available()
{
	return USART0_Read_Pos_!=USART0_Write_Pos_;
}
volatile char Serial0Read()
{
	if(Serial0_Available())
	{
		char data =USART0_Buffer_[USART0_Read_Pos_++];
		if(USART0_Read_Pos_>=USART0_BUFFER_SIZE)
		{
			USART0_Read_Pos_=0;
		}
		return data;
	}
	else
		return '\0';
}
Standard::string Serial0_ReadString()
{
	char *strdata = new  char [USART0_BUFFER_SIZE+1];
	unsigned long lngth = 0;
	while(Serial0_Available())
	{
		strdata[lngth++] = Serial0Read();
	}
	strdata[lngth] = '\0';
	Standard::string return_data = Standard::string(strdata);
	delete[] strdata;
	return return_data;
}
void Serial0_PrintString(string message)
{
	Serial0_WriteString(message);
	USART0_Transmit('\r');
	USART0_Transmit('\n');
}
void Serial0_WriteString(string message)
{
	int i = 0;
	while (message[i])
	{
		USART0_Transmit(message[i]);
		++i;
	}
}
ISR(USART0_RX_vect)
{
	USART0_Buffer_[USART0_Write_Pos_++]=USART0_Receive();
	if(USART0_Read_Pos_ == USART0_Write_Pos_)
	{
		++USART0_Read_Pos_;
		if(USART0_Read_Pos_ >=USART0_BUFFER_SIZE)
		{
			USART0_Read_Pos_ = 1;
		}
	}
	if(USART0_Write_Pos_>=USART0_BUFFER_SIZE)
	USART0_Write_Pos_ = 0;
}
#endif /* USART0_H_ */