#include<stdio.h>
#include<stdlib.h>
#include<winsock2.h>


void main(){
    // socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // connect
    struct sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(9000);
    sock_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (const struct sockaddr *) &sock_addr, sizeof(sock_addr));
    if(connect(sock, (SOCKADDR *)&sock_addr, sizeof(sock_addr)) == SOCKET_ERROR)
    exit(1);
    // dup2 stdin
    dup2(sock, STDIN_FILENO);
    // dup2 stdout
    dup2()
    // dup2 stderr
    // execv()
}