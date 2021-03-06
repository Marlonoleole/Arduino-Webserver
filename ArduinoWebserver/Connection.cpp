/*
 * Connection.cpp
 *
 * Created: 21/04/2019 20:08:29
 *  Author: Marlon Abeln
 */ 
#define USART1DOUBLE
#define F_CPU 16000000UL
#define	USART1BAUD 115200
#define USART1_BUFFER_SIZE 1000
#include "Connection.h"
#include "USART1.h"
#define USART0BAUD 9600
#include "USART0.h"
#include <util/delay.h>
void Connection::clear_buffer()
{
	while (Serial1_Available())
	{
		Serial1Read();
	}
}
string Connection::send(const string command)
{
	Serial1_PrintString(command);
	_delay_ms(1000);
	while (!Serial1_Available());
	string data = Serial1_ReadString();
	Serial0_PrintString(data);
	return data.c_str();
}
Connection::Connection()
{
	USART1_Init();
	USART0_Init();
	clear_buffer();
}
bool Connection::reset()
{
	string data = send(reset_command);
	if (data.find_first_of("OK") >= 0)
	return true;
	return false;
}
int Connection::status()
{
	string data = send(status_command);
	if (data.find_first_of('1') > 0)
	return 1;
	else if (data.find_first_of('2') > 0)
	return 2;
	else if (data.find_first_of('3') > 0)
	return 3;
	else if (data.find_first_of('4') > 0)
	return 5;
	else
	return 6;
}
bool Connection::wifimode(const string mode)
{
	string s_mode = mode_command;
	s_mode += "=";
	s_mode += mode;
	string data = send(s_mode.c_str());
	if (data.find_first_of("OK") > 0)
	return true;
	return false;
}
bool Connection::enable_multiple_connections(const bool value)
{
	string s_mode = multiple_connections_command;
	s_mode += ("=");
	if (value)
	s_mode += "1";
	else
	s_mode += "0";
	string data = send(s_mode.c_str());
	if (data.find_first_of("OK") > 0)
	return true;
	return false;
}
bool Connection::enable_server(const bool value)
{
	string s_mode = server_command.c_str();
	s_mode += "=";
	if (value)
	s_mode += "1,80";
	else
	s_mode += "0";
	string data = send(s_mode.c_str());
	if (data.find_first_of("OK"))
	return true;
	return false;
}
void Connection::SendData(const string id, const string response)
{
	string s_mode = send_command;
	s_mode += "=";
	s_mode += id;
	s_mode += ",";
	s_mode += Standard::parse_int(response.size());
	send(s_mode);
	Serial0_PrintString("Responding");
	send(response);
}
ClientConnection Connection::readData()
{
	if (Serial1_Available())
	{
		Serial0_PrintString("GOT SOMETHING");
		string data = Serial1_ReadString();
		if (data.find_first_of("+IPD") >= 0)
		{
			//Serial.println(data.c_str());
			string client_id = data.substr(data.find_first_of("+IPD") + 5, 1);
			int request_length = (data.find_first_of("HTTP") - 1) - (data.find_first_of("GET") + 4);
			string request = data.substr(data.find_first_of("GET") + 4, request_length);
			int parameter_location = request.find_first_of('?');
			string parameters = "";
			if (parameter_location >= 0)
			{
				parameters = request.substr(parameter_location, request.size() + 1);
				request = request.substr(0, parameter_location);
			}
			Serial0_PrintString("Responding to client with ID:");
			Serial0_PrintString(client_id);
			ClientConnection retobj = ClientConnection(client_id, request, parameters);
			return retobj;
		}
	}
	return ClientConnection();
}
void Connection::close_connection(const string client_id)
{
	string s_mode = close_connection_command;
	s_mode += "=";
	s_mode += client_id;
	send(s_mode);
}
bool Connection::data_available()
{
	return Serial1_Available();
}