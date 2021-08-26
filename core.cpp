#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <iostream>

int main(int argc , char *argv[])
{
    /* prepare socket() with args */
    struct addrinfo hints,*res; 

    memset(&hints , 0 , sizeof(hints));

    hints.ai_family = AF_INET; hints.ai_socktype = SOCK_STREAM; 
        hints.ai_flags = AI_PASSIVE;
    
    getaddrinfo(argv[1] , argv[2] , &hints, &res);

    int socketx = socket(res -> ai_family , 
        res -> ai_socktype , res -> ai_protocol);
    
    /* connect and free res */
    if(connect(socketx , res -> ai_addr, res -> ai_addrlen) == 0)
        std::cout<<1<<"\n";
    else  std::cout<<"error \n";
    

    freeaddrinfo(res); char read[4096];

    std::string 
        toSend = "GET / HTTP/1.1 \r\n Host : github.com \r\n",
        websiteHTML;

        if(send(socketx, toSend.c_str(), strlen(toSend.c_str()), 0) < 1) 
            std::cout<<"connection closed";

        while(recv(socketx, read , strlen(read) , 0) > 0){
            int i = 0;
                while(read[i]) websiteHTML += read[i++]; 
        }

        std::cout<<websiteHTML;

    close(socketx);
}