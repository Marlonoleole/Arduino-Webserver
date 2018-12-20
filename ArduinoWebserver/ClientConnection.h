#ifndef CLIENTCONNECTION_h
#define CLIENTCONNECTION_h
#include "String.h"
#include "Arduino.h"
using string = Standard::string;

struct ClientConnection
{
    string ID_{};
    string request_{};
    string parameters_{};
    ClientConnection(){}
    ClientConnection(const string &ID, const string &request, const string &parameters) :ID_(ID), request_(request),parameters_(parameters){}
};

#endif
