/*
 * SiteMapping.h
 *
 * Created: 21/04/2019 20:07:39
 *  Author: Marlon Abeln
 */ 


#ifndef SITE_MAP_H
#define SITE_MAP_H

#include "Website.h"
#include "Hashmap.h"
#include "string.h"

using Map::Hashmap;
using Webcontent::Website;
using string = Standard::string;
namespace webMapping
{
	class Sitemap
	{
		private:
		Hashmap<string, Website> site_mapping_{};
		const Website not_found{};

		public:
		Sitemap() : site_mapping_{} {};
		void add(string link, Website site);
		Website get(string link);
	};
} // namespace webMapping
#endif