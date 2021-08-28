if [[ "$OSTYPE" == "win32" ]]; then
    g++ core.cpp -o core -lssl -lcrypto  -lws2_32 && ./core
else 
    g++ core.cpp -o core -lssl -lcrypto && ./core
fi