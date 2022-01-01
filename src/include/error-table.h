#ifndef WG___ERRROR_TABLE_H
#define WG___ERRROR_TABLE_H

#include <iostream>

std::string contents;
unsigned int currlne = 0;

void init_error () {
    printf("\nwgpp: error detected on %d line\n", currlne);
}

void _err_semicolon () {
    init_error();
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
