/*
 * USART0.h
 *
 * Created: 20/04/2019 18:56:08
 *  Author: Marlon Abeln
 */ 


#ifndef USART1_H_
#define USART1_H_
#include "String.h"
#include <avr/interrupt.h>
#include <math.h>
void USART1_Transmit(unsigned char data);
void Serial1_WriteString(string message);
void Serial1_PrintString(string message);

#ifndef USART1_BUFFER_SIZE
# warning "USART Buffer Size not defined"
#define USART1_BUFFER_SIZE 120
#endif
#ifndef USART1BAUD
# warning "NO USART1 BAUDRTATE DEFINED"
#define USART1BAUD 9600
#endif
#ifndef F_CPU
# warning "F_CPU not defrined for USART1"
#define F_CPU 16000000UL
#endif

char  *USART1_Buffer_ = 0;
volatile unsigned int USART1_Read_Pos_ = 0;
volatile unsigned int USART1_Write_Pos_ = 0;

#ifdef USART1DOUBLE
#define USART1_UBAUD (int)round(((((double)F_CPU / ((double)USART1BAUD * 8.0))) - 1.0))
#else
#define USART1_UBAUD (int)round(((((double)F_CPU / ((double)USART1BAUD * 16.0))) - 1.0))
#endif

void USART1_Init()
{
	/* Enable Interrupts */
	SREG|=0x80;
	/* Enable receiver and Transmitter receive interrupts */
	#ifdef USART1DOUBLE
	UCSR1A=(1<<U2X1);
	#endif 
	UCSR1B=(1<<RXEN1|1<<TXEN1|1<<RXCIE1);
	/* Setting Baud Rate */
	UBRR1L= (unsigned int) USART1_UBAUD;
	UBRR1H=(unsigned int)(USART1_UBAUD>>8);
	/* Set frame format: 8data, 1 stop bit */
	UCSR1C=(0<<UMSEL11|0<<UMSEL10|0<<UPM10|0<<UPM11|0<<USBS1|1<<UCSZ10|1<<UCSZ11|0<<UCSZ12);
	/* Spawning the buffer */
	if(!USART1_Buffer_)
		USART1_Buffer_= new char[USART1_BUFFER_SIZE];
} // USART0_Init

void USART1_Transmit(unsigned char data)
{
	/* wait for empty transmit buffer */
	while(!(UCSR1A & (1<<UDRE1)));
	
	/* Putting data into buffer to send the data */
	UDR1 = data;
}

unsigned char USART1_Receive( void )
{
	/* wait for data to be received */
	while(!(UCSR1A & (1<<RXC1)));
	
	/* Getting and returning received data */
	unsigned char data = UDR1;
	return data;
}
bool Serial1_Available()
{
	return USART1_Read_Pos_!=USART1_Write_Pos_;
}
volatile char Serial1Read()
{
	if(Serial1_Available())
	{
		char data =USART1_Buffer_[USART1_Read_Pos_++];
		if(USART1_Read_Pos_>=USART1_BUFFER_SIZE)
		{
			USART1_Read_Pos_=0;
		}
		return data;
	}
	else
		return '\0';
}
Standard::string Serial1_ReadString()
{
	char *strdata = new  char [USART1_BUFFER_SIZE+1];
	unsigned long lngth = 0;
	while(Serial1_Available())
	{
		strdata[lngth++] = Serial1Read();
	}
	strdata[lngth] = '\0';
	Standard::string return_data = Standard::string(strdata);
	delete[] strdata;
	return return_data;
}
void Serial1_PrintString(string message)
{
	Serial1_WriteString(message);
	USART1_Transmit('\r');
	USART1_Transmit('\n');
}
void Serial1_WriteString(string message)
{
	int i = 0;
	while (message[i])
	{
		USART1_Transmit(message[i]);
		++i;
	}
}
ISR(USART1_RX_vect)
{
	USART1_Buffer_[USART1_Write_Pos_++]=USART1_Receive();
	if(USART1_Read_Pos_ == USART1_Write_Pos_)
	{
		++USART1_Read_Pos_;
		if(USART1_Read_Pos_ >=USART1_BUFFER_SIZE)
		{
			USART1_Read_Pos_ = 1;
		}
	}
	if(USART1_Write_Pos_>=USART1_BUFFER_SIZE)
	USART1_Write_Pos_ = 0;
}
#endif /* USART1_H_ */