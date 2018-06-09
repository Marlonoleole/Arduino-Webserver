# Arduino-Webserver
A project to allow an arduino to be used as a webserver so that iot Projects can hosts their own websites or allow connections from another device using html requests.

# Current Status
the project can be run on a Mega 2560 as the device supports hardware serial interupts. that is to say a if a serial event happens from the serial network device the execution of the program will be interrupted and the connection will be handled.

Currently the solution uses AT commands to communicate with an ESP2866. This is currently hardcoded into the server and should be sepparated to open up the use on platforms which do not use At commands or even directly on the esp by abstracting the connection out of the server. 

# TODO
- [ ] Sepperate the server and the connection to the netwrok device to open up the server running on different modules
- [ ] Document the structure of the program
- [ ] write a how-to to allow people using the solution 
- [ ] add a setup method to allow setting up the device if it is not connected to a network (such as moved)
