/*
 * Serial.cpp
 *
 * Created: 20/04/2019 16:32:14
 * Author : Marlon Abeln
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "String.h"
#include "Memory.h"
#include "Website.h"
#include "Server.h"
#include "ResponseProvider.h"



int main(void)
{
	//Setting up the server
	Server::server serv {};
	Website site{"<!doctype html><html><head><title>PlaceHolder</title></head><body><H1>This is a placeholder site for now, </H1></body></html>", 0};
	serv.add_site("/", site);
	 if (serv.StartServer())
		;
	 else
		
		//the main task to handle connections
	while(1)
	{	
		serv.handleConnections();
	}
	//TODO: Implement handling multiple connections from one string.
	//TODO: Add Ability to host a server on a network
	//TODO: Investigate saving data to EEPROM
}