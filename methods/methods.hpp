/*

Methods header:
Checks the http request method and reroutes to the corresponding function

*/

#ifndef METHODS_H
    #define METHODS_H
#endif

#include <string.h>
#include <SFML\Network.hpp>

#ifndef GET_H
    #include "get.hpp"
#endif

// Function to reroute to the correct method
void manageRequest(sf::TcpSocket &client, char *request, size_t request_length)
{
    // Find the adress of the first space in the request (the one right after the request method declaration)
    char* end = strchr(request, ' ');

    // Find the method name length and allocate space in the memory for its storage
    size_t len = end - request;
    char method[len+1];

    // Fill in the method name
    for(int i = 0; i < len; i++) method[i] = request[i];
    method[len] = '\0';

    // Find the method used by the client and reroute to the proper function for the response
    if(strcmp(method, "GET") == 0) manageGet(client, request, request_length);

    return;
}