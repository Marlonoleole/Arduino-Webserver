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
    char *site = request.c_str();
    char *parameters = 0; 
    if(index>0){
      site = request.substring(0,index).c_str();
      *parameters = request.substring(index, request.length()).c_str();
    }
    Website *data = sMap.getValue(site);
    if(data){
      return String(data->getSite(parameters));
    }else{
      return notFound;
    }
   }
 };
#endif

