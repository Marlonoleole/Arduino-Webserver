/*
 * ClientConnection.h
 *
 * Created: 21/04/2019 20:04:29
 *  Author: Marlon Abeln
 */ 


#ifndef CLIENTCONNECTION_h
#define CLIENTCONNECTION_h
#include "String.h"
using string = Standard::string;

struct ClientConnection
{
	string ID_{"-1"};
	string request_{};
	string parameters_{};
	ClientConnection(){}
	ClientConnection(const string &ID, const string &request, const string &parameters) :ID_(ID), request_(request),parameters_(parameters){}
};

#endif