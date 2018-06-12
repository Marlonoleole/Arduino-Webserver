#include "Server.h"
#include "SiteMap.h"
#include "Websites.h"
#include "Website.h"
#include "TestInputHandler.h"

void setup() {
  if(StartServer()){
    Serial.println("Server Online");
    Serial.println("adding siteMap");
    SiteMap *mapping = new SiteMap();
    Website test (testSite);
    InputHandler *testhandler = new TestInputHandler();
    test.addInputHandler(testhandler);
    mapping->add("/",test);
    Serial.println(mapping->website("/2",0));
    addMapping(mapping);
  }else{
  }
}

void loop(){
  //this should call the main function of the controller for your model
}

void serialEvent1(){
  handleConnections();
}
