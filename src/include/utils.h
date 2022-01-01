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

std::string get_all_string (const std::string src, int from) {
    std::string str = "";
    do {
        str += src[from];
        from++;

        if ( src[from] == '"' ) {
            break;
        }

    } while ( true );

    return str;
}

std::string parse_str_to_strASM (const std::string src, int *rdx_regsiter) {
    std::string asmSTR = "";
    size_t idx = 0;
    int special_chars = 0;

    while ( idx < src.size() ) {
        std::string current = std::to_string( int(src[idx]) );
        if ( src[idx] == '\\' && src[idx + 1] == 'n' ) {
            special_chars++;
            current = "10";
            idx++;
        }
        if ( src[idx] == '\\' && src[idx + 1] == 't' ) {
            special_chars++;
            current = "9";
            idx++;
        }

        if ( idx + 1 != src.size() ) {
            current += ",";
        }

        asmSTR += current;
        idx++;
    }
    *rdx_regsiter = idx - special_chars;

    return asmSTR;
}


#endif
