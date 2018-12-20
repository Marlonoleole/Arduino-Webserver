#ifndef PARAM_Handler_H
#define PARAM_Handler_H

#include "String.h"
#include "Arduino.h"
using string = Standard::string;

//#include "Arduino.h"
//TODO: Abstraction Here!!
namespace Webcontent
{
class ParameterHandler
{
  public:
    const string handle(const string parameters) const
    {
        Serial.println(parameters);
        return parameters;
    };
};

} // namespace Webcontent
#endif