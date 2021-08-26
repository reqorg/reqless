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

int main(int argc , char *argv[]) {
    struct addrinfo hints,*res; 

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = AI_PASSIVE;

    const string domain = "info.cern.ch";
    const string protocol = "http";
    
    getaddrinfo(domain.c_str(), protocol.c_str(), &hints, &res);
    int socketx = socket(AF_INET, SOCK_STREAM, 0);

    int conn = connect(socketx , res -> ai_addr, res -> ai_addrlen);
    if (conn == 0) cout << "Connection successful!" << endl;
    else cout << "Error connecting to socket!\n";

    freeaddrinfo(res);

    string toSend = "GET / HTTP/1.1\nHost: " + domain + "\nUser-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/92.0.4515.159 Safari/537.36\nUpgrade-Insecure-Requests: 1\n";
    cout << toSend << endl;
    string websiteHTML;
    send(socketx, toSend.c_str(), strlen(toSend.c_str()), 0);

    void *read[4096];

    cout << "Sent request!" << endl;

    int bytesReceived;
    do {
        bytesReceived = recv(socketx, read, 4096, 0);
        if (bytesReceived > 0)
            cout << "Bytes received: " << bytesReceived << endl;
        else if (bytesReceived == 0)
            cout << "Connection closed" << endl;
        else {
            cout << "Error while receiving" << endl;
            fprintf(stderr, "recv: %s (%d)\n", strerror(errno), errno);
        }
    } while (bytesReceived > 0);

    cout << "RESPONSE" << endl;

    char *array;
    array = (char*)read;
    cout << array << endl;

    close(socketx);
    return 0;
}