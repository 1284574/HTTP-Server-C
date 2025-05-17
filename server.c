#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main()
{
    FILE *html_data;
    html_data = fopen("index.html", "r");

    // open a html file and read
    // store a buffer for read data
    char response[1024];
    fgets(response, 1024, html_data);
    // gets next char from a stream, specify how many bytes to put into output buffer
    
    char header[2048] = "HTTP/1.1 200 OK\r\n\n"; // http response header
    strcat(header, response); // concatenate header with the response
    
    // create a socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    // socket() needs a communication domain for communication, type for communication semantics - UDP/TCP
    // protocol argument is 0 to match socket type with correct protocol

    // define socket address
    // where our server is going to serve the data
    struct sockaddr_in address;
    address.sin_family = AF_INET; // address family
    address.sin_port = htons(8001); // service port
    address.sin_addr.s_addr = INADDR_ANY; // set address to accept any incoming message
    // bind() - give the socket address to a file descriptor (server_socket) and specify the length in bytes of
    // address struct pointed to by address
    bind(server_socket, (const struct sockaddr *) &address, sizeof(address));
    // listen() for connections on a socket
    // take in socket file descriptor (server_socket) and max length of queue to which the file descriptor
    // can grow - 5
    listen(server_socket, 5);

    int client_socket; // client side socket
    // infinite while loop
    while(1)
    {
        // accept() extracts first connection request on queue for listening socket
        // the file descriptor argument creates a new connected socket and returns a new file descriptor referring to socket
        client_socket = accept(server_socket, NULL, NULL);
        // send() transmits a message to a socket, takes in client fd, the header (buffer), size, and flags - 0
        send(client_socket, header, sizeof(header), 0);
    }
    return 0;

}