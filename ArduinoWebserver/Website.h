#ifndef Website_H
#define Website_H

#include "String.h"
#include "ResponseProvider.h"

using string = Standard::string;

namespace Webcontent
{
class Website
{
private:
  string html_{"NOT FOUND"};
  Response_Provdier *response_provdier_{nullptr};

public:
  Website(){};
  Website(string html, Response_Provdier *RP) : html_{html}, response_provdier_{RP} {};
  const string generate_site(const string parameters) const
  {
    if (response_provdier_)
    {
      return response_provdier_->generate_response(parameters);
    }
    return html_;
  };
};
} // namespace Webcontent
#endif