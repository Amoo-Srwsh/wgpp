#ifndef WG___HELSP_H
#define WG___HELSP_H

#include "err-report.h"
#include "token.h"

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

std::string get_name_variable (const std::string src, int from) {
    std::string namevar = "";
    do {
        namevar += src[from];
        from++;

        if ( from >= (int) src.size() )
            wrong_name_var();
    } while ( src[from] != '$' );

    namevar += '$';
    return namevar;
}

#endif
