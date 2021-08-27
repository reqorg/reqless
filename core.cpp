#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <iostream>
#include <errno.h>

using namespace std;

void prepare_hints(addrinfo &hints){
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET; hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = AI_PASSIVE;
}

int main(int argc , char *argv[]) {
    struct addrinfo hints,*res; prepare_hints(hints);
    const string domain = "info.cern.ch", protocol = "http";
    
    getaddrinfo(domain.c_str(), protocol.c_str(), &hints, &res);
    int socketx = socket(AF_INET, SOCK_STREAM, 0);

    if(connect(socketx , res -> ai_addr, res -> ai_addrlen) == 0){
        cout << "Connection successful!\n";
    } else cout << "Error connecting to socket!\n";

    freeaddrinfo(res);

    string toSend = "GET / HTTP/1.1\r\nHost:" + domain + "\r\nUpgrade-Insecure-Requests: 0\r\n\r\n";
    cout << toSend << endl; 
    
    send(socketx, toSend.c_str(), strlen(toSend.c_str()), 0);

    void *read[4096];
    
    cout << "Sent request!" << endl;

    int bytesReceived ;
    
    do {
        int bytesReceived = recv(socketx, read, 4096, 0);
        if (bytesReceived > 0)
            cout << "Bytes received: " << bytesReceived << endl;
        else if (bytesReceived == 0){
            cout << "Connection closed" << endl; 
        }
        else {
            cout << "Error while receiving" << endl;
            fprintf(stderr, "recv: %s (%d)\n", strerror(errno), errno);
        }
    } while (bytesReceived > 0);

    cout << "RESPONSE" << endl << (char*)read << endl;

    close(socketx);
}