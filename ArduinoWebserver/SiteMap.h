#ifndef SITEMAP_H
#define SITEMAP_H
#include "Website.h"
#include "Websites.h"
#include "StringMap.h"

class SiteMap{
 private:
  StringMap<Website> sMap;

public:
  SiteMap(){}

  int add(const char* url, Website site){
    return sMap.putValue(url, site);
  }
   
 char* website(char* site, char* parameters){
    Website *data = sMap.getValue(site);
    if(data){
      return data->getSite(parameters);
    }else{
      Serial.println("Not Found");
      return notFound;
    }
   }
 };
#endif

