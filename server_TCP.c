// https://www.youtube.com/watch?v=0Zr_0Jy8mWE&ab_channel=SloanKelly : tcp client
#include<stdio.h>
#include<winsock2.h>

void main(){
    // init Winsock
    WSADATA wsData;
    WORD ver = MAKEWORD(2,2);

    int wsock = WSAStartup(ver, &wsData);
    if(wsock != 0){
        printf("Error init winsock... Quitting");
        exit(1);
    }

    // create socket
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if(listening == INVALID_SOCKET){
        printf("Error creating a socket... Quitting");
        exit(1);
    }

    // bind sock
    struct sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(9000);
    hint.sin_addr.s_addr = INADDR_ANY;

    bind(listening, (struct sockaddr *) &hint, sizeof(hint));

    // listen
    listen(listening, SOMAXCONN);

    // wait for connection
    struct sockaddr_in client;
    int clientSize = sizeof(client);

    SOCKET clientsocket = accept(listening, (struct sockaddr *) &client, &clientSize);

    if((struct sockaddr * ) &client == 0){
        printf("Connection established");
    }else{
        inet_ntoa(client.sin_addr);
        printf("dayuhm\n");
    }
    // close
    closesocket(listening);

    // while loop for constant connection
    char buffer[2048];

    while(1){
        ZeroMemory(buffer, 2048);
        // wait for client to send data
        int bytesRec = recv(clientsocket, buffer, 2048, 0);
        if(bytesRec == SOCKET_ERROR){
            printf("ERROR receiving msg... Quitting");
            break;
        }else if (bytesRec == 0){
            printf("Client disconnected\n");
            break;
        }else if(buffer == "exit"){
            send(clientsocket, "exit", 2049, 0);
            exit(1);
        }
        // Echo msg back to client
        else{
            send(clientsocket, buffer, 2049 ,0);
        }
    }
    
    closesocket(clientsocket);
    WSACleanup();
}