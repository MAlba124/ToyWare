#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 1337
#define IP "127.0.0.1"

void suicide(const char *fileN, int sockfd) {
	close(sockfd); // Closes the socket before self destructing
	remove(fileN); // Deletes the binary
}

int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in server_addr;
        
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    	suicide(argv[0], sockfd);
    	exit(1);
    }
   
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, IP, &server_addr.sin_addr)<=0) {
        suicide(argv[0], sockfd);
   		exit(1);
   	}
    
    if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        suicide(argv[0], sockfd);
	    exit(1);
	}

    send(sockfd , "I'm alive", 9, 0);

    suicide(argv[0], sockfd);

    return 0;
}