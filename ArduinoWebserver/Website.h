#ifndef WEBSITE_H
#define WEBSITE_H

#include "InputHandler.h"

struct Website{
 private:
 char* html;
 InputHandler *handler;

public:
  Website(char* data){
    this->html = data; 
    this->handler = 0;
  }

  Website(){
   this->html =0;
   this->handler =0; 
  }

  int addInputHandler(InputHandler *handler){
    this->handler = handler;
  }

  char* getSite(char* parameters){
    if(handler&&(parameters !=0)){
       handler->handle(parameters); 
    }
    return html;
  }
};

#endif
