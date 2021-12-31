#ifndef WG___ERRROR_TABLE_H
#define WG___ERRROR_TABLE_H

#include <iostream>

std::string contents;
unsigned int currlne;

void init_error () {
    printf("wgpp: error detected on %d line\n", currlne);
    printf("%d | %s\n", currlne, contents.c_str());
}

void _err_semicolon () {
    init_error();
    for ( size_t i = 0; i <= contents.size() + std::to_string(currlne).size() + 2; ++i ) {
        printf(" ");
    }
    printf("^\n");;
    printf("Semicolon expected\n");

    exit(1);
}

void _err_many_arguments () {
    init_error();
    printf("There are so many args in this function!\n");
    exit(1);
}

void _err_different_type () {
    init_error();
    printf("Incorrect type in this function!\n");
    exit(1);;
}

#endif
