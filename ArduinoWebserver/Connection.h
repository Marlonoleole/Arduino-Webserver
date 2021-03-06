/*
 * Connection.h
 *
 * Created: 21/04/2019 20:04:56
 *  Author: Marlon Abeln
 */ 


#ifndef CONNECTION_H
#define CONNECTION_H
#include "ClientConnection.h"
#include "String.h"

using string = Standard::string;
const static string reset_command{"AT+RST"};
const static string mode_command{"AT+CWMODE"};
const static string multiple_connections_command{"AT+CIPMUX"};
const static string server_command{"AT+CIPSERVER"};
const static string send_command{"AT+CIPSEND"};
const static string status_command{"AT+CIPSTATUS"};
const static string close_connection_command{"AT+CIPCLOSE"};
const static int delay_time{100};

class Connection
{
	private:
	bool setup_done{};
	void clear_buffer();
	string send(const string command);

	public:
	Connection();
	bool reset();
	bool data_available();
	int status();
	bool wifimode(const string mode);
	bool enable_multiple_connections(const bool value);
	bool enable_server(const bool value);
	void SendData(const string id, const string response);
	ClientConnection readData();
	void close_connection(const string client_id);
};

#endif