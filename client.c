
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>  // close için
#include <string.h>

#include <sys/socket.h> //for socket APIs
#include <sys/types.h>
#include <netinet/in.h>

/*client socket için:
create socket with socket()
connect to some remote address: connect()
recieve data with recv()
*/ 

int main() {
    // create a 
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    // specify an adress for the soscket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(44082);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(client_socket, (struct sockaddr *) 
    &server_address, sizeof(server_address));

    if(connection_status == -1 ){
        fprintf(stderr, "connect error");
        return 1;
    }
    
    // recieve data from the server
    char server_response[256];
    recv(client_socket, &server_response, sizeof(server_response), 0);
    // print the servers response
    printf("the server sent the data: %s", server_response);

    // send data to server
    char clientMessage[256];
    int quit = 0;
    while(!quit){
        // read input
        scanf("%s", clientMessage);
        // send to server
        send(client_socket, clientMessage, sizeof(clientMessage), 0);

        if(clientMessage == "quit"){
            quit = 1;
            break;
        }
    }
    

    // finally close the socket
    close(client_socket);
    
    return 0;
}   