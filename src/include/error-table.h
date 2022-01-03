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

void _err_arguments () {
    init_error();
    printf("There are not the rigth number of arguements\n");
    exit(1);
}

void _err_different_type () {
    init_error();
    printf("Incorrect type in this function!\n");
    exit(1);;
}

#endif
