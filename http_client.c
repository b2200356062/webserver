#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
// define address için gerekli
#include <netinet/in.h>
// converting network address!
#include <arpa/inet.h>

/*client socket için:
create socket with socket()
connect to some remote address: connect()
recieve data with recv()
*/ 

int main(int argc, char **argv){
    
    char* address = argv[1];

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in c_address;
    c_address.sin_family = AF_INET;
    c_address.sin_port = htons(44082);
    inet_aton(address, &c_address.sin_addr);

    int connection_status = connect(client_socket, (struct sockaddr*)&c_address, sizeof(c_address));
    if(connection_status == -1){
        printf("connection error");
        return 1;
    }

    char request[] = "GET / HTTP/1.1\r\n\r\n";
    char response[4096];

    send(client_socket, request, sizeof(request), 0);
    recv(client_socket, response, sizeof(response), 0);

    printf("response from the server: %s ", response);

    close(client_socket);
    return 0;

}