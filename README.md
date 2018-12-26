# Arduino Webserver
## Table of Contents
* [About](#About)
* [Current Status](#Current-Status)
* [How To](#How-To)
* [Notes](#Notes)
* [Documentation](#Documentation)
    * [Hardware](#Hardware)
    * [Software](#Software)
* [TODO](#TODO)

## About
This project is aimed at providing a simple solution to handle a server for handling HTTP requests on the arduino platform.

## Current Status
The project can be run on a Mega 2560 as the device supports hardware serial interupts. that is to say a if a serial event happens from the serial network device the execution of the program will be interrupted and the connection will be handled.

## How To
To create a Website there is a defined class to act as a container for html data and a object which extends the Respondse_Provider super class. This is optional as it does not need to be provided. In the event that this is not provided, the string that is passed in the constructor is used instead.

An example setup which will set a bool parameter globally defined is given below:
 ```c++
class Lamp_handle : public Response_Provdier
{
    string generate_response(string parameters)
    {
        if (parameters == string("?L=1"))
        {
            light_on = true;
        }
        else
        {
            light_on = false;
        }
        return "<!doctype html><html><head><title>PlaceHolder</title></head><body><H1>This is a placeholder site for now, </H1></body></html>";
    }
};

server *serv = new server();
Website site{"<!doctype html><html><head><title>PlaceHolder</title></head><body><H1>This is a placeholder site for now, </H1></body></html>", new Lamp_handle()};
serv->add_site("/", site);
```
Please check the Arduino-Webserver.ino file for a more indepth example.

## Notes
This systems uses its own string implementation. this might be evident from the line:
```c++
using string = Standard::string;
```
that is present in several of the source files

Several source files with the .cc extension and a Makefile is present in the repository, these are testfiles that are used for debugging and testing basic functionality, these may be out of date as some changes might have been performed to the clases when they are integrated into the server system. 

## Documentation
Documentation should be provided soon
### Hardware
### Software

## TODO
[] Provide Documentation
[] Look into Abstracting the connection
[] Look into providing a master and a slave configuration for the server
