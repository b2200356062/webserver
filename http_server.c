#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

// define address için gerekli
#include <netinet/in.h>

// server socket flow
/*
create a socket with socket()
bind the socket to an IP and port with bind()
listen() for connections
accept() a connection
send() or recv() data 
*/

int main(){

    // open a file to server
    FILE* html_data;
    html_data = fopen("index.html", "r");
    char buffer[128];
    char response_data[1024] = {'\0'};

    while(fgets(buffer, sizeof(buffer), html_data) != NULL){
        strcat(response_data, buffer);
    }

    // dosyadan karakter okuma

    fgets(response_data, 1024, html_data);
    
    char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
    strcat(http_header, response_data);

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(44082);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

    listen(server_socket , 5 );

    int client_socket;
    while(1){
        client_socket = accept(server_socket, NULL, NULL);
        send(client_socket, http_header, sizeof(http_header), 0);
        close(client_socket);
    }

	
    return 0;
}

