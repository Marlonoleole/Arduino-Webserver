
#include "Website.h"
#include "ParameterHandler.h"
#include "String.h"

using string = Standard::string;
#include <iostream>

int main()
{
    Webcontent::ParameterHandler handle{};
    char link[] = "ABC";
    Webcontent::Website site{link, &handle};
    char params[] = "Test";
    std::cout << site.generate_site(params).c_str() << std::endl;
}