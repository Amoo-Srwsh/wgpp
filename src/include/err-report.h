#ifndef WG___ERR_REPORT_H
#define WG___ERR_REPORT_H

#include <iostream>

/* Variables imported from ../wgpp.cpp, these variables are useful
 * to give more information about any error that can happen while the 
 * compilation proccess */
extern std::string content;
extern int line_code;

void init_error (int lint = line_code) {
    printf("wgpp: error detected on %d line\n", lint);
    printf("%d | %s\n", lint, content.c_str());
}

void semi_colon_expected () {
    printf("Semicolon expected\n");
    exit(1);
}

void no_right_number_arguments () {
    printf("No right number of arguments in this line\n");
    exit(1);
}

void wrong_name_var () {
    printf("$ expected, any variable name must start with a '$' and end with a '$'\n");
    exit(1);
}

void var_doesnt_exist (const std::string name) {
    printf("%s does not exist as variable\n", name.c_str());
    exit(1);
}

void wrong_type_argument () {
    printf("Wrong argument\n");
    exit(1);
}

void token_expected (std::string token) {
    printf("TOKEN EXPECTED: %s\n", token.c_str());
    exit(1);
}

#endif
