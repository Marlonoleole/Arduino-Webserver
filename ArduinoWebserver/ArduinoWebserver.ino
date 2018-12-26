#include "SiteMapping.h"
#include "String.h"
#include "Website.h"
#include "Server.h"
#include "globals.h"
#include "ResponseProvider.h"

using Server::server;
using Webcontent::Response_Provdier;
using Webcontent::Website;
using webMapping::Sitemap;

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
    Serial.begin(115200);
    Serial.println("adding and testing site");
    serv->add_site("/", site);
    Serial.println("Starting Server");
    if (serv->StartServer())
        Serial.println("Server Started Succesfully");
    else
        Serial.println("There was a problem Starting the server");
    pinMode(22, OUTPUT);
    digitalWrite(22, LOW);
    light_on = false;
}

void loop()
{
    if (light_on)
        digitalWrite(22, HIGH);
    else
        digitalWrite(22, LOW);
}

void serialEvent1()
{
    serv->handleConnections();
}
