
#pragma once

#include <ostream>
#include <iostream>
#include <unordered_map>
#include <sstream>

namespace Color 
{
    std::unordered_map<std::string, int> ColorMapLinux
    ({
        {"red"     , 31},
        {"blue"    , 34},
        {"green"   , 32},
        {"original", 39}
    });
    std::unordered_map<std::string, int> ColorMapWin
    ({
        {"red"     , 12},
        {"blue"    , 9},
        {"green"   , 10},
        {"original", 14}
    });

    #if defined(_WIN32)
    void CPRINT(std::string color , std::string print)
    {
        int color_code;

        std::unordered_map<std::string,int>::iterator itr = ColorMapWin.find(color);

        if(itr == ColorMapWin.end()) color_code = 14;
        else color_code = itr->second;

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color_code);
        cout << print << endl;
        SetConsoleTextAttribute(hConsole, 7);
    }
    #else
    std::string reset = "\033[0;39m\033[0m\n\n";

    template <class T>
    void PREPSTREAMS
    (   
        std::stringstream &s, std::stringstream &b , std::stringstream &e,
            int color_code , T print
    )
    {
        b << s.rdbuf() << ";" << color_code << "m" << print;
            e << s.rdbuf()  << "m"; b << e.rdbuf();
    }

    template <class T>
    void CPRINT(std::string color , T print)
    {
        int color_code;

        std::unordered_map<std::string,int>::iterator itr = ColorMapLinux.find(color);

        if(itr == ColorMapLinux.end()) color_code = 39;
            else color_code = itr->second;

        std::stringstream ss("\033[0") , begin , end; 
            PREPSTREAMS(ss , begin , end , color_code , print);

        std::cout << begin.rdbuf() << reset; 
    }
    #endif
}