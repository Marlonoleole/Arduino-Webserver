#ifndef RESPONSEP_H
#define RESPONSEP_H

#include "String.h"

using string = Standard::string;

namespace Webcontent
{
class Response_Provdier
{
  public:
    virtual string generate_response(string parameters) = 0;
};
} // namespace Webcontent
#endif