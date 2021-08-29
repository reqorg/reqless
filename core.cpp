#include "request.h"

template <class T>
void msg(T message , std::string color){
    Color::CPRINT(color , message);
}

void prepare_hints(addrinfo &hints){
    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_INET; hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = AI_PASSIVE;
}

void init_winsock(){
    #if defined(_WIN32)    
        WSADATA d;    
        if (WSAStartup(MAKEWORD(2, 2), &d)) {        
            cout<<"Winsock failed to initialize";       
        }
    #endif
}
unordered_map<string, string> sendRequest(string url, string method) {

    const bool logging = false;
    // Init windows
    #if defined(_WIN32)    
        init_winsock();
    #endif

    struct addrinfo hints,*res; prepare_hints(hints);

    //parse URI
    size_t start = url.find("://", 0);
    start += 3; //"://"
    size_t end = url.find("/", start + 1);
    string protocol = url.substr(0, start - 3);
    string domain = url.substr(start, end - start);
    string path = url.substr(end);
    
    getaddrinfo(domain.c_str(), protocol.c_str(), &hints, &res);
        int socketx = socket(AF_INET, SOCK_STREAM, 0);

    if(!socket_error(socketx)){
        msg("Error creating socket!\n" , "red");
    }

    if(connect(socketx , res -> ai_addr, res -> ai_addrlen) == 0){
        if (logging) msg("Connection successful!\n", "green");
    } else msg("Error connecting to socket!\n" , "red");

    string toSend = method + " " + path + " HTTP/1.1\r\nHost:" + domain + "\r\nConnection: close\r\nUpgrade-Insecure-Requests: 0\r\n\r\n";
    if (logging) cout << toSend << endl; 
    
    if (logging) msg("Sent Request!\n", "green");

    xSSL::init();  
    xSSL::context_socket Builder  = xSSL::create_secure_socket();
    SSL* ssl_obj = Builder.ssl_object; SSL_CTX* ctx = Builder.context;

    //secure socket
    if(protocol == "https"){

        if(!SSL_set_tlsext_host_name(ssl_obj,(void *) domain.c_str()))
            msg("Cant get site's certificate!\n" , "red");
        
        //set file descriptor
        SSL_set_fd(ssl_obj,socketx); if(SSL_connect(ssl_obj) == -1){
            msg("SSL connect failed!\n" , "red");
        }

        SSL_write(ssl_obj, toSend.c_str(), strlen(toSend.c_str()));
    }else{
        send(socketx, toSend.c_str(), strlen(toSend.c_str()) , 0);
    }

    int bytesReceived;
    int readIncrement = 1024;
    string response;
    #if defined(_WIN32)
        char read[readIncrement];
        shutdown(socketx, SD_SEND);
    #else
        char read[1024];
    #endif

    do {
        if (protocol == "https") bytesReceived = SSL_read(ssl_obj, read, readIncrement);
        else bytesReceived = recv(socketx, read, 1024, 0);
        #if defined(_WIN32)
            string tmpBuffer(read);
            response += tmpBuffer;
            memset(read, 0, sizeof(read));
        #else
            string tmpBuffer((char *)read);
                response += tmpBuffer;
            memset(read, 0, sizeof(read));
        #endif

        if (bytesReceived > 0) {
            if (logging) cout << "Bytes received: " << bytesReceived << endl;
        }
        else if (bytesReceived == 0) {
            if (logging) cout << "Connection closed" << endl; 
        }
        else {
            msg("Error while receiving!\n" , "red");
                fprintf(stderr, "recv: %s (%d)\n", strerror(errno), errno);
        }
    } while (bytesReceived > 0);

    if (protocol == "https") {
        SSL_shutdown(ssl_obj); SSL_free(ssl_obj);
            SSL_CTX_free(ctx);
    }

    freeaddrinfo(res);
    close_socket(socketx);

    #if defined(_WIN32) 
        WSACleanup();
    #endif

    unordered_map<string, string> responseObj;

    string headers = response.substr(0, response.find("\n\r")); // token is "scott"
    headers = headers.erase(0, headers.find("\n") + 1);

    string body = response.substr(response.find("\n\r") + 1); 

    responseObj["body"] = body;
    responseObj["headers"] = headers;

    return responseObj;
}

int main() {
    string url = "http://info.cern.ch/";
    unordered_map<string, string> response = sendRequest(url, "GET");

    unordered_map<string, string>::const_iterator body = response.find("body");
    msg("RESPONSE BODY\n", "green");
    cout << body->second << endl;
    
    unordered_map<string, string>::const_iterator headers = response.find("headers");
    msg("RESPONSE HEADERS\n", "green");
    cout << headers->second << endl;
}