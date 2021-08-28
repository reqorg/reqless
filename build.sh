if [ "$1" == "" ]; then
    if [[ "$OSTYPE" == "win32" ]]; then
    g++ core.cpp -o core -lssl -lcrypto  -lws2_32 && ./core
    else 
        g++ core.cpp -o core -lssl -lcrypto && ./core
    fi
elif [ "$1" == "code" ]; then
    if [ "$2" == "original" ]; then
        git ls-files  | grep -v -E "package.json|package-lock.json|node/build|.gitignore"  | xargs wc -l
    else 
        git ls-files | xargs wc -l
    fi
fi