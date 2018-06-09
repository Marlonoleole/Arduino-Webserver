#ifndef SITEMAP_H
#define SITEMAP_H
#include "Websites.h"
#include "Website.h"
#include "StringMap.h"
class SiteMap{
 private:
  StringMap<Website> sMap;

public:
  SiteMap(){}
  
  int setupMap(){
    //TODO: Currently a debugigng feature to ensure that the StringMap is working as intended remove once all the features of it work as intended
    sMap.putValue("/", testSite );
    //sMap.putValue("/Test", new Website(testSite));
    return 1;
  }

  String website(String request){
    int index = request.indexOf('?');
    String site = request;
    String *parameters = 0; 
    if(index>0){
      site = request.substring(0,index);
      *parameters = request.substring(index, request.length());
    }
    Website data = *sMap.getValue(site.c_str());
    String returnstrn(data.getSite(parameters->c_str()));
    Serial.println(returnstrn);
    if(returnstrn != 0){
      return returnstrn;
    }
    return notFound;
   }
 };
#endif

