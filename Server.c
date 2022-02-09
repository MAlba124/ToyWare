#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 1337

int main(int argc, char const *argv[]) {
    
    int sockfd, new_socket, valread;
    
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char buffer[10] = {0};
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
       
       
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        exit(1);
       
    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
        exit(1);

    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address))<0) 
        exit(1);
    
    if (listen(sockfd, 3) < 0) 
        exit(1);
    
    if ((new_socket = accept(sockfd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        exit(1);

    // Waiting for message from target
    valread = read( new_socket , buffer, 1024);
 
    printf("%s\n",buffer );
    
    close(sockfd);

    return 0;
}