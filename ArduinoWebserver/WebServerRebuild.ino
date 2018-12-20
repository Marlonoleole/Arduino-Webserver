#include "SiteMapping.h"
#include "String.h"
#include "Website.h"
#include "ParameterHandler.h"
#include "Server.h"

using Server::server;
using Webcontent::ParameterHandler;
using Webcontent::Website;
using webMapping::Sitemap;

server *serv = new server();
ParameterHandler *pa = new ParameterHandler();
Website site{"<!doctype html><html><head><title>PlaceHolder</title></head><body><H1>This is a placeholder site for now, </H1></body></html>", pa};
Sitemap *mapp = new Sitemap();

void setup()
{
    Serial.begin(115200);
    Serial.println("adding and testing site");
    mapp->add("/", site);
    Serial.println((mapp->get("/").generate_site("ABC").c_str()));
    serv->addMapping(mapp);
    if (serv->StartServer())
        Serial.println("Server Started Succesfully");
    else
        Serial.println("There was a problem Starting the server");
}

void loop()
{
}

void serialEvent1()
{
    serv->handleConnections();
}