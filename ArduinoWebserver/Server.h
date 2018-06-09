#define ESP8266 Serial1
#define BUFFER_SIZE  128
#include "SiteMap.h"

char buffer[BUFFER_SIZE];
SiteMap siteMapping;

boolean SetupDone = false;

void clearBuffer(){
  while (ESP8266.available() > 0) {
    char a = ESP8266.read();
  }
}

char* sendCommand(String Command, int waitTime){
  ESP8266.println(Command);
  delay(waitTime);
  return ESP8266.read();
}

boolean connectNet(){
  String cmd = "AT+GMR";
  ESP8266.println(cmd);
  for(int i = 0; i<1000; i++){
    delay(1000);
    if(ESP8266.find("OK")){
     return true;
    }
  }
}

void sendData(int id, String response)
{
  String cmd = "AT+CIPSEND=";
  cmd += id;
  cmd += ",";
  cmd += response.length();
  sendCommand(cmd, 1000);
  sendCommand(response, 1000);
  Serial.println(cmd + response);
}

void handleConnections(){
  //TODO: add modifiying the parameters for the model here
  if(SetupDone){
     int connectionId; 
    Serial.println("Something received");
    String data = ESP8266.readString();
    if(data.indexOf("+IPD,")>0){
      
      Serial.println("Received Data");
      Serial.println(data);
      
      int getReq = data.indexOf(":GET ");
      int HTTP = data.indexOf("HTTP/");
      String getrequest = data.substring(getReq+5, HTTP-1);

      int clientID = data.indexOf("+IPD,");
      String clientIDstr = data.substring(clientID+5, clientID+7);
      Serial.println(String("Client: ") + clientIDstr + " requests: " + getrequest);
      delay(1000);

      //Send the correct Data Back!
      sendData(connectionId, siteMapping.website(getrequest));
      
      String cmdCIPCLOSE = "AT+CIPCLOSE="; 
      cmdCIPCLOSE += connectionId;
      sendCommand(cmdCIPCLOSE, 1000);
      Serial.println("closing connection");
  }
 }
 clearBuffer();
}

bool StartServer(){
  Serial.begin(115200);
  ESP8266.begin(115200);
   while(!Serial);
    Serial.println("Serial Started");
    ESP8266.println("AT+RST");
    while(!ESP8266.available());
    if(ESP8266.find("ready")){
      clearBuffer();
      Serial.println("Module is ready");
      Serial.println("Waiting for IP");
      while(!SetupDone){
        ESP8266.println("AT+CIPSTATUS");
        while(!ESP8266.available());
        if(ESP8266.find("STATUS:2")){
          Serial.println("\nConnected and got IP");
          ESP8266.println("AT+CIFSR");
          while(!ESP8266.available());
          ESP8266.find("+CIFSR:STAIP,\"");
          ESP8266.readBytesUntil('"' , buffer, BUFFER_SIZE);
          Serial.println(buffer);
          clearBuffer();
          sendCommand("AT+CIPMUX=1", 1000);
          Serial.println("Starting Server");
          sendCommand("AT+CIPSERVER=1,80",1000);
          while(!ESP8266.available());
          if(ESP8266.find("OK")){
            Serial.println("SUCCESS");
          }
          clearBuffer();
          SetupDone = true;
          Serial.println("Setting up Mapping for sites");
          siteMapping.setupMap();
          Serial.println("Setup Done");
          return true;
          }else{
            Serial.write(".");
            //TODO PUT Setup Here after a Timeout
          }
      }  
  }
  return false;
}
