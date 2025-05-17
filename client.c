#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

#include <arpa/inet.h>
// TCP Client
int main(int argc, char* argv[])
{
    char* addr;
    addr = argv[1];
    // 1st arg will be the address of server
    // stored in addr pointer
    // create socket
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // connect to an address
    struct sockaddr_in remote;
    remote.sin_family = AF_INET;
    remote.sin_port = htons(80);
    // have to convert address from IP
    // inet_aton() - converts Internet host address (addr) from CLA to
    // into binary from (in network byte order) and stores it (remote)
    inet_aton(addr, (struct in_addr *) &remote.sin_addr.s_addr);
    // connect() - connects socket referred to by file descriptor to the address, also takes in size of address
    connect(client_socket, (struct sockaddr*) &remote, sizeof(remote));
    // HTTP request - Ex: GET
    char request[] = "GET / HTTP/1.1\r\n\r\n";
    // response buffer
    char response[4096];
    // send request
    send(client_socket, request, sizeof(request), 0);
    // recieve response from server
    recv(client_socket, &response, sizeof(response), 0);

    printf("response from the server: %s\n", response);
    // close client socket after recieving response from server
    close(client_socket);

    return 0;

}