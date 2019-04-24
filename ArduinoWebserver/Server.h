/*
 * Server.h
 *
 * Created: 21/04/2019 20:06:40
 *  Author: Marlon Abeln
 */ 


#ifndef SERVER_H
#define SERVER_H
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
		bool SetupDone{false};

		public:
		server() : conn{}, siteMapping{new Sitemap()}, SetupDone{false}{}
		~server(){delete siteMapping;}
		void add_site(string link, Website site)
		{
			siteMapping->add(link, site);
		}
		void handleConnections()
		{
			if (SetupDone&&conn.data_available())
			{
				ClientConnection conFrame = conn.readData();
				if(conFrame.ID_!=string("-1"))
				{
					Website site = siteMapping->get(conFrame.request_);
					conn.SendData(conFrame.ID_, site.generate_site(conFrame.parameters_));
					conn.close_connection(conFrame.ID_);
				}
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