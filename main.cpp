
/*

Main file:
Initializes the server, receives requests and reroutes to other functions for the response

*/

#ifndef CONSTANTS_H
    #include "constants.hpp"
#endif

#include <iostream>
#include <SFML\Network.hpp>

#ifndef METHODS_H
    #include "methods\methods.hpp"
#endif

// Main function
int main(int argc, char* argv[])
{
    // Fetch port value
    int port = 32100;
    if(argc > 1) port = atoi(argv[1]);

    // Initialize listener
    sf::TcpListener listener;
    std::cout << "[SERVER] Connecting to port " << port << "...\n";
    if(listener.listen(port) != sf::TcpSocket::Status::Done)
    {
        std::cout << "[ERROR] Unable to connect to the port\n";
        std::cout << "[FATAL] 101\n";
        exit(101);
    }
    std::cout << "[SERVER] successfully connected to port " << port << "\n";

    // Keep looping through the following instructions
    while(true)
    {
        std::cout << "\n\n\n";
        
        // Get a conection
        std::cout << "[SERVER] Waiting for inbound connection...\n";

        sf::TcpSocket client;
        if(listener.accept(client) != sf::TcpSocket::Status::Done)
        {
            std::cout << "[ERROR] Impossible to connect to the received client\n";
        }
        else
            std::cout << "[SERVER] Client connected successfully\n";

        // Receive data on that connection
        char buffer[MAX_RECEIVING_BYTES];
        size_t received;

        if(client.receive(buffer, sizeof(buffer), received) != sf::TcpSocket::Status::Done)
        {
            std::cout << "[ERROR] Problems receiving data from the client\n";
            continue;
        }

        std::cout << "[SERVER] Received client request\n";

        // Deal with the request
        manageRequest(client, buffer, received);
    }
}