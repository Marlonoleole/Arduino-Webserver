#ifndef TESTHANDLER_H
#define TESTHANDLER_H

class TestInputHandler : public InputHandler {
  public:
  TestInputHandler() : InputHandler() {}
  void handle(char *parameters){
    String param(parameters);
    Serial.println(param);
  }
};

#endif
