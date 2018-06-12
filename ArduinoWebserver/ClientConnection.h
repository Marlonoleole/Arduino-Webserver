#ifndef CLIENTCONNECTION_h
#define CLIENTCONNECTION_h

struct ClientConnection {
  char* ID;
  char* request;
  char* parameters;

  ClientConnection(const char* ID, const char* request, const char* parameters){
    this->ID = ID;
    this->request = request;
    this->parameters = parameters;
  }
  
};

#endif

