#ifndef WEBSITES_H
#define WEBSITES_H

#include "Website.h"

Website testSite ("<!doctype html>\
<html>\
<head>\
<title>PlaceHolder</title>\
</head>\
<body>\
<H1>This is a placeholder site for now, </H1>\
</body>\
</html>");

String notFound = "<!doctype html>\
<html>\
<head>\
<title>404: Page not found </title>\
</head>\
<body>\
<H1>Error 404!</H1>\
<H2>Page Not Found<H2>\
</body>\
</html>";

String invalidParam = "<!doctype html>\
<html>\
<head>\
<title>Invalid Parameters </title>\
</head>\
<body>\
<H1>Error with your Parameters!</H1>\
<H2>Error with your parameters, please check them!<H2>\
</body>\
</html>";
#endif
