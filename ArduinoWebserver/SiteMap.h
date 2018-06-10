#ifndef SITEMAP_H
#define SITEMAP_H
#include "Websites.h"
#include "Website.h"
#include "StringMap.h"
#include "TestInputHandler.h"

class SiteMap{
 private:
  StringMap<Website> sMap;

public:
  SiteMap(){}
  
  int setupMap(){
    //TODO: Currently a debugigng feature to ensure that the StringMap is working as intended remove once all the features of it work as intended
    Website testSite (test);
    TestInputHandler *handler = new TestInputHandler();
    testSite.addInputHandler(handler);
    sMap.putValue("/", testSite );
    //sMap.putValue("/Test", new Website(testSite));
    return 1;
  }
  
 char* website(char* site, char* parameters){
    Website *data = sMap.getValue(site);
    if(data){
      return data->getSite(parameters);
    }else{
      return notFound;
    }
   }
 };
#endif

