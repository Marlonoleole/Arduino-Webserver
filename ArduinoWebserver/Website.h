#ifndef Website_H
#define Website_H

#include "String.h"
#include "ParameterHandler.h"

using string = Standard::string;

namespace Webcontent
{
class Website
{
  private:
    string html_{"NOT FOUND"};
    ParameterHandler *handler_{};

  public:
    Website(){};
    Website(string html, ParameterHandler *handler) : html_{html}, handler_{handler} {};
    const string generate_site(const string parameters) const
    {
        handler_->handle(parameters);
        return html_;
    };
};
} // namespace Webcontent
#endif