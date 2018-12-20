
#include "SiteMapping.h"

void webMapping::Sitemap::add(string link, Website site)
{
    site_mapping_.add(link, site);
}
Website webMapping::Sitemap::get(string link)
{

    if ((site_mapping_.get(link)))
    {
        Website site{*site_mapping_.get(link)};
        return site;
    }
    else
        return not_found;
}
