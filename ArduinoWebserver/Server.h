#include "SiteMap.h"
#include "Connection.h"
#include "ClientConnection.h"

Connection conn;
SiteMap *siteMapping;

boolean SetupDone = false;

void addMapping(SiteMap* mapping){
  siteMapping = mapping;
  Serial.println(siteMapping->website("/",0));
}

void handleConnections(){
  if(SetupDone){
    ClientConnection* data = conn.readData();
    if(data){
      Serial.println("Got data");
      char* id = data->ID;
      char* req = data-> request;
      char* param = data->parameters;
      char* resp = siteMapping->website(req, param);
      conn.sendData(id, resp);
      conn.closeClientConnection(id);
      delete(data);
    }
  }
}

bool StartServer(){
  Serial.begin(115200);
   while(!Serial);
    Serial.println("Serial Started");
    if(conn.reset()){
      Serial.println("Module is ready");
      Serial.println("Waiting for connection to internet");
      while(!SetupDone){
        int count = 0;
        if(conn.status() == 2){
          Serial.println("\nConnected to Network");
          Serial.println("Allowing multple connection");
          conn.enableMultipleConnections();
          Serial.println("Starting Server");
          if(conn.enableServer()){
            Serial.println(conn.getIP());
            SetupDone = true;
            Serial.println("Setup Done");
            return true;
          }
         }else{
           Serial.write(".");
           count++;
           if(count = 10){
            return false;
           }
         }
      }
    }  
   return false;
  }
