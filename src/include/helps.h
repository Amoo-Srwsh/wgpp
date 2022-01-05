#ifndef WG___HELSP_H
#define WG___HELSP_H

#include <iostream>

std::string get_whole_num (const std::string src, int from) {
    std::string num = "";
    do {
        num += src[from];
        from++;
    } while ( std::isdigit(src[from]) );

    return num;
}

std::string get_whole_str (const std::string src, int from) {
    std::string str = "";
    do {
        str += src[from];
        from++;
    } while ( src[from] != '"' );

    return str;
}


#endif
