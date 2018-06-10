#include "SiteMap.h"
#include "Connection.h"

Connection conn;
SiteMap siteMapping;

boolean SetupDone = false;


void handleConnections(){
  //TODO: add modifiying the parameters for the model here
  if(SetupDone){
    int connectionId; 
    Serial.println("Something received");
    String data = conn.readData();
    if(data.indexOf("+IPD,")>0){
      
      Serial.println("Received Data");
      Serial.println(data);

      //analysing the data
      String request = data.substring(data.indexOf("+IPD"), data.indexOf("HTTP"));
      //Splitting around the comma
      String id;
      String GET;

      int start = request.indexOf(",");
      int i = start+1;
      while(request.charAt(i)!=','){
        i++;
      }
      id=request.substring(start+1, i);

      start = request.indexOf(":GET ");
      GET = request.substring(start+5, request.length()-1);

      String req;
      if(GET.indexOf("?")>=0){
        Serial.println("Parameters found");
        String param = GET.substring(GET.indexOf("?"), GET.length());
        String newGET = GET.substring(0, GET.indexOf("?"));
        req = siteMapping.website(newGET.c_str(), param.c_str());
      }else{
        req = siteMapping.website(GET.c_str(), 0);
      }
      //Send the correct Data Back
      conn.sendData(id, req);
      conn.closeClientConnection(id);
      Serial.println("closing connection");
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
        if(conn.status() == 2){
          Serial.println("\nConnected to Network");
          Serial.println("Allowing multple connection");
          conn.enableMultipleConnections();
          Serial.println("Starting Server");
          if(conn.enableServer()){
            SetupDone = true;
            Serial.println("Setting up Mapping for sites");
            //TODO: Debuggning function to setup the map later the user will have to add their own map
            siteMapping.setupMap();
            Serial.println("Setup Done");
            return true;
          }
         }else{
           Serial.write(".");
           //TODO: PUT Setup Here after a Timeout
         }
      }
    }  
   return false;
  }
