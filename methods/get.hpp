/*

Get header:
Manages the responses to the get requests

*/

#ifndef GET_H
    #define GET_H
#endif

#include <iostream>
#include <SFML/Network.hpp>

#ifndef UTILIS_H
    #include "../utilis.hpp"
#endif

void sendResponse(sf::TcpSocket &client, const char* request_path, const char* status, const char *type);

// Function to check and fetch the data for the response
void manageGet(sf::TcpSocket &client, char* request, size_t request_length)
{
    // Find the first space in the request (the one just before the requested filepath)
    char* start = strchr(request, ' ');
    if(!start) {
        std::cout << "[ERROR] No space found after method declaration\n";
        return;
    }
    start++;

    // Find the second thpace in the request (the one just after the requested filepath)
    char* end = strchr(start, ' ');
    if(!end)
    {
        std::cout << "[ERROR] No closing space found for the request path\n";
        return;
    }

    // Fetch the request filepath
    size_t request_path_length = end - start;
    char request_path[request_path_length+15];
    const char* const_request_path = request_path;
    sprintf(request_path, "../Frontend%.*s", request_path_length, start);

    // Log the client's request
    std::cout << "-v-v-v-v-v-v-v-\n[HTTP-GET-REQUEST]\nPath: " << request_path << "\n-^-^-^-^-^-^-^-\n";

    char open_path[] = "../Frontend";

    bool request_is_legit = fileIncluded(request_path, open_path);
    bool path_is_file = std::filesystem::is_regular_file(const_request_path);

    // Check if the file is accessible by the client
    if(!request_is_legit) {
        std::cout << "[ERROR] File path requested by the client is forbidden\n";
        std::cout << "[HTTP-RESPONSE] Error 403 - Forbidden\n";
        sendResponse(client, "../Frontend/errors/403.html", "403 ERROR", "text/html");
        return;
    }
    // Check if the file exists
    if(!path_is_file) {
        std::cout << "[ERROR] File path requested by the client was not found\n";
        std::cout << "[HTTP-RESPONSE] Error 404 - Not found\n";
        sendResponse(client, "../Frontend/errors/404.html", "404 ERROR", "text/html");
        return;
    }

    // Allocate space to store the response content type
    char filetype[32] = "*/*";
    char* extension = getFileExtension(request_path);

    // Get the response content type
    if(!strcmp(extension, "html")) strcpy(filetype, "text/html");
    else if(!strcmp(extension, "txt")) strcpy(filetype, "text/*");
    else if(!strcmp(extension, "js")) strcpy(filetype, "text/javascript");
    else if(!strcmp(extension, "css")) strcpy(filetype, "text/css");
    else strcpy(filetype, "*/*");

    // Reroute to the response function
    sendResponse(client, const_request_path, "200 OK", filetype);
    
    return;
}

// Function to build and send a response to a get request to a client
void sendResponse(sf::TcpSocket &client, const char* request_path, const char* status, const char *type)
{
    // Fetch the file content
    size_t file_size = std::filesystem::file_size(request_path);
    char content[file_size+1];
    readFile(request_path, content, sizeof(content));

    // Fetch the file size
    char tmp_str[10];
    tmp_str[0] = '\0';
    sprintf(tmp_str, "%i", file_size);

    

    // Fetch all response components and their length
    char header[10+strlen(status)];
    header[0];
    sprintf(header, "HTTP/1.1 %s", status);

    char content_type[20+strlen(type)];
    content_type[0] = '\0';
    sprintf(content_type, "\r\nContent-Type: %s", type);

    char content_length[22+strlen(tmp_str)];
    content_length[0] = '\0';
    sprintf(content_length, "\r\nContent-Length: %s", tmp_str);

    char connection[30];
    connection[0] = '\0';
    sprintf(connection, "\r\nConnection: close\r\n\r\n");



    // Fetch the length of the response
    size_t len = strlen(header) + strlen(content_type) + strlen(content_length) + strlen(connection) + strlen(content);

    // Allocate space for the response
    char response[len+1];

    // Build the response
    response[0] = '\0';
    strncat(response, header, len);
    strncat(response, content_type, len);
    strncat(response, content_length, len);
    strncat(response, connection, len);
    strncat(response, content, len);
    response[len] = '\0';

    // Send the response to the client
    client.send(response, sizeof(response));

    // Log the response
    std::cout << "-v-v-v-v-v-v-v-\n[HTTP-RESPONSE]\n";
    std::cout.write(response, strlen(header) + strlen(content_type) + strlen(content_length) + strlen(connection) - 4);
    std::cout << "\nFile: \""<< request_path <<"\"\n-^-^-^-^-^-^-^-";

    return;
}