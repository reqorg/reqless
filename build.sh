if [ "$OSTYPE" == "msys" ] || [ "$OSTYPE" == "win32" ]; then
    g++ core.cpp -o core.exe -I C:/OpenSSL/include -L C:/OpenSSL/lib -lssl -lcrypto -lws2_32 -lgdi32 && ./core.exe
else 
    g++ core.cpp -o core -lssl -lcrypto && ./core
fi