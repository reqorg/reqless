#ifndef REQUEST_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define REQUEST_H

#if defined(_WIN32)
    #ifndef _WIN32_WINNT
    #define _WIN32_WINNT 0x0600
    #endif
    #include <conio.h>
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <unistd.h>
    #include <errno.h>
    #include <cstring>
#endif

#if defined(_WIN32)
    #define socket_error(s) ((s) != INVALID_SOCKET)
    #define close_socket(s) closesocket(s)
#else
    #define socket_error(s) ((s) >= 0)
    #define close_socket(s) close(s)
#endif

using namespace std;

//ssl
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/ssl.h>
#include <openssl/pem.h>
#include <openssl/err.h>

//colored output
#include "colors.h"

namespace xSSL{
    struct context_socket{
        SSL *ssl_object; SSL_CTX* context;
    };

    void init(){
        //init SSL and load algorithms/error strings
        SSL_library_init(); OpenSSL_add_all_algorithms();
            SSL_load_error_strings();
    }

    SSL_CTX* create_context(){
        SSL_CTX *context = SSL_CTX_new(TLS_client_method());

        if(!context) cout<<"SSL Context Error!";

        return context;
    }

    context_socket create_secure_socket(){
        context_socket Obj;

        SSL_CTX* ctx = create_context();
            SSL *ssl_obj = SSL_new(ctx);
        
        Obj.context = ctx; Obj.ssl_object = ssl_obj;

        return Obj;
    }
};

string sendRequest(string url, string method);

#endif