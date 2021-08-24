#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc , char *argv[]){

    //prepare , getaddrinfo and socket()
    struct addrinfo hints, *res; 
        memset(&hints , 0 , sizeof(hints));
    
    hints.ai_family = AF_INET; 
        hints.ai_socktype = SOCK_STREAM; 
            hints.ai_flags = AI_PASSIVE;
    
    getaddrinfo(argv[1] , argv[2] , &hints, &res);

    int socketx = socket(res -> ai_family , 
                    res -> ai_socktype , res -> ai_protocol);
    
    //connect and free res
    connect(socketx , res -> ai_addr, res -> ai_addrlen);
        freeaddrinfo(res);

    while(1){
        fd_set r; FD_ZERO(&r); FD_SET(socketx, &r);
            FD_SET(0 , &r);

        struct timeval timeout;


        //seconds and microseconds
        timeout.tv_sec = 0; timeout.tv_usec = 100000;

        if(select(socketx+1 , &r, 0 , 0 , &timeout) < 0){
            printf("error");
        }

        if (FD_ISSET(socketx, &r)) {            
            char read[4096];           
            int bytes_received = recv(socketx, read, 4096, 0);            
            if (bytes_received < 1) {               
                printf("Connection closed by peer.\n");    
                    break;            
            }            
            printf("Received (%d bytes): %.*s",
                    bytes_received, bytes_received, read);        
        }

        //GET / HTTP/1.1
        //Host : site
        // 

        if(FD_ISSET(0, &r)) {
            char read[4096];
            if (!fgets(read, 4096, stdin)) break;            
                printf("Sending: %s", read);

            int bytes_sent = send(socketx, read, strlen(read), 0);          
                printf("Sent %d bytes.\n", bytes_sent);
        }
    }
    close(socketx);
}