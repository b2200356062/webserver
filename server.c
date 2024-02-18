#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>  // close için
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <netinet/in.h>


// server socket flow
/*
create a socket with socket()
bind the socket to an IP and port with bind()
listen() for connections
accept() a connection
send() or recv() data 
*/

int main() { 

    // create server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1){
        fprintf(stderr, "socket error");
        return 1;
    }

    //define server address
    struct sockaddr_in server_adress;
    server_adress.sin_family = AF_INET;
    server_adress.sin_port = htons(44082);

    
    server_adress.sin_addr.s_addr = INADDR_ANY;
    // binf server socket to server address
    bind(server_socket, (struct sockaddr*) &server_adress, sizeof(server_adress));

    listen(server_socket, 5);

    // client to connect
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    char server_message[256] = "MERHABA!!!";
    char client_message[256];
    
    // send message to client
    send(client_socket, server_message, sizeof(server_message), 0);
    int quit = 0;

    recv(client_socket, client_message, sizeof(client_message), 0);
        
    printf("client sent: %s\n", client_message);
    // while(!quit){

       

    //     if(client_message == "quit"){
    //         quit = 1;
    //         break;
    //     }
    // }


    close(server_socket);

    return 0;
}