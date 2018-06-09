#include "Server.h"

void setup() {
  if(StartServer()){
    Serial.println("Server Online");
  }else{
    //TODO: run Setup;
  }
}

void loop(){
  //this should call the main function of the controller for your model
}

void serialEvent1(){
  handleConnections();
}
