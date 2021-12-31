#ifndef WG___UTILS_H
#define WG___UTILS_H

#include <iostream>

std::string get_all_num (const std::string src, int from) {
    std::string numb = "";
    do {
        numb += src[from];
        from++;
    } while ( std::isdigit(src[from]) );

    return numb;
}


#endif
