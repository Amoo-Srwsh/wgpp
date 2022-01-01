#include "include/lexer.h"
#include "include/error-table.h"
#include "include/token-funcs.h"
#include <iostream>
#include <fstream>
using namespace std;

void _start (char *filename) {
    ifstream file (filename);
    if ( !file.good() ) {
        printf("%s doesn't exist\n", filename);
        exit (1);
    }

    while ( !file.eof() ) {
        getline(file, contents);
        if ( !contents.empty() ) {
            currlne++;
            clean(contents);
        }
    }

    parser();
    string final_ = "./asm-union.sh ";
    final_.append(filename);
    system(final_.c_str());
}

int main (int argc, char* argv[]) {
    if ( argc != 2 ) {
        printf("Not enough arguments\n");
        exit(1);
    }

    _start(argv[1]);
    return 0;
}
