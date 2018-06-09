#ifndef CONNECTION_H
#define CONNECTION_H
#define ESP8266 Serial1
#define BUFFER_SIZE  128

class Connection{

private:
char buffer[BUFFER_SIZE];

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

  
  public:

  Connection(){
    ESP8266.begin(115200);
  }
  
  int reset(){
    ESP8266.println("AT+RST");
    while(!ESP8266.available());
    if(ESP8266.find("ready")){
      clearBuffer();
      return 1;
  }
  clearBuffer();
  return 0;
 }

 int status() {
    ESP8266.println("AT+CIPSTATUS");
    while(!ESP8266.available());
    if(ESP8266.find("STATUS:2")){
      clearBuffer();
      return 2;
    }
 }
  
  int connectNet(){
    String cmd = "AT+GMR";
    ESP8266.println(cmd);
    while(!ESP8266.available());
    if(ESP8266.find("OK")){
      clearBuffer();
      return true;
    }
  }

  char* getIP(){
     ESP8266.println("AT+CIFSR");
     while(!ESP8266.available());
     ESP8266.find("+CIFSR:STAIP,\"");
     ESP8266.readBytesUntil('"' , buffer, BUFFER_SIZE);
     clearBuffer();
     return buffer;
  }

  char* enableMultipleConnections(){
    return sendCommand("AT+CIPMUX=1", 1000);
  }

  int enableServer (){
    sendCommand("AT+CIPSERVER=1,80",1000);
    while(!ESP8266.available());
    if(ESP8266.find("OK")){
      clearBuffer();
      return 1;
    }
    clearBuffer();
    return 0;
  }

  void sendData(String id, String response){
    String cmd = "AT+CIPSEND=";
    cmd += id;
    cmd += ",";
    cmd += response.length();
    sendCommand(cmd, 1000);
    Serial.println(cmd);
    sendCommand(response, 1000);
  }
  
  void closeClientConnection(String connectionId){
    String cmdCIPCLOSE = "AT+CIPCLOSE="; 
    cmdCIPCLOSE += connectionId;
    sendCommand(cmdCIPCLOSE, 1000);
  }

  String readData(){
    return ESP8266.readString();
  }
};

#endif
