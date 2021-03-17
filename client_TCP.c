#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#ifdef __WIN32__
# include <winsock2.h>
#else
# include <sys/socket.h>
#endif

void main(){

    int nsocket;
    nsocket = socket(AF_INET, SOCK_STREAM, 0);

    // socket setup
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9001);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // establish connection
    int connection_status = connect(nsocket, (struct sockaddr *) &server_address, sizeof(server_address));
    // connection status check
    if(connection_status == -1){
        printf("Sum Ting Wong");
    }

    // receive data from server
    char response[256];
    recv(nsocket, &response, sizeof(response),0);

    printf("Server: %s\n", response);

    close(nsocket);
}
