#include "String.h"
#include "Website.h"
#include "Server.h"
#include "globals.h"
#include "ResponseProvider.h"

using Server::server;
using Webcontent::Response_Provdier;
using Webcontent::Website;

class Lamp_handle : public Response_Provdier
{
    string generate_response(string parameters)
    {
        if (parameters == string("?L=1"))
        {
            light_on = true;
        }
        else
        {
            light_on = false;
        }
        return "<!doctype html><html><head><title>PlaceHolder</title></head><body><H1>This is a placeholder site for now, </H1></body></html>";
    }
};

server *serv = new server();
Website site{"<!doctype html><html><head><title>PlaceHolder</title></head><body><H1>This is a placeholder site for now, </H1></body></html>", new Lamp_handle()};

void setup()
{
    //Server Setup
    Serial.begin(115200);
    Serial.println("adding and testing site");
    serv->add_site("/", site);
    Serial.println("Starting Server");
    if (serv->StartServer())
        Serial.println("Server Started Succesfully");
    else
        Serial.println("There was a problem Starting the server");

    //Procedure Setup
    pinMode(22, OUTPUT);
    digitalWrite(22, LOW);
    light_on = false;
}

void loop()
{
        digitalWrite(22, light_on);
}

/**
 * This is an interupt method calling the servers handle method, beause this is an interrupt,
 * the main program can run and only be interrupted by the server when it needs to.
 * For long (or very many) messages, this can be a problem as it can prevent the main program from
 * running proprely (checking on sensors or so), therefore, the main controller might be better on its own
 * micro controller and asks this device which variables it should take.
 **/
void serialEvent1()
{
    serv->handleConnections();
}
