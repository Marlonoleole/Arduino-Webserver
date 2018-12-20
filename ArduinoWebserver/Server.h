#ifndef SERVER_H
#define SERVER_H

#include "Arduino.h"
#include "String.h"
#include "Connection.h"
#include "SiteMapping.h"
#include "ClientConnection.h"
using webMapping::Sitemap;
using string = Standard::string;

namespace Server
{
class server
{
  private:
    Connection conn{};
    Sitemap *siteMapping{};
    boolean SetupDone{false};

  public:
    void addMapping(Sitemap *mapping)
    {
        siteMapping = mapping;
    }
    void handleConnections()
    {
        if (SetupDone)
        {
            ClientConnection conFrame = conn.readData();
            Website site = siteMapping->get(conFrame.request_);
            Serial.println(site.generate_site(conFrame.parameters_));
            conn.SendData(conFrame.ID_, site.generate_site(conFrame.parameters_));
            conn.close_connection(conFrame.ID_);
        }
    }
    bool StartServer()
    {
        bool success = true;
        success = success && conn.reset();
        success = success && conn.wifimode("2");
        success = success && conn.enable_multiple_connections(true);
        success = success && conn.enable_server(true);
        SetupDone = success;
        return success;
    }
};
} // namespace Server

#endif