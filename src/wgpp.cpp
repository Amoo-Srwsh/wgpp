#include "include/lexer.h"
#include "include/token-func.h"
#include <iostream>
#include <fstream>

std::string content;
int line_code = 1;

void read (std::ifstream *file, char* filename) {
    while ( !file->eof() ) {
        std::string aux;
        std::getline(*file, aux);
        if ( !aux.empty() ) {
            content = aux;
            clean_line(aux);
            line_code++;
        }
    }

    parser();
    std::string final_step = "./union.sh ";
    final_step += filename;
    system(final_step.c_str());
}

int main (int argc, char* argv[]) {
    if ( argc != 2 ) {
        printf("wgpp: No enough arguments\n");
        printf("Must be: wgpp filename.wgpp\n");
        exit(1);
    }

    std::ifstream file (argv[1]);
    if ( !file.good() ) {
        printf("%s does not exist\n", argv[1]);
        exit(1);
    }

    read(&file, argv[1]);
    return 0;
}
