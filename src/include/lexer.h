#ifndef WG___LEXER_H
#define WG___LEXER_H

#include "token-funcs.h"
#include "utils.h"
#include "error-table.h"

/* A comment could be in a several lines so we need to know if one comment has been 
 * opened and if will be closed */
bool comment = false;

void lexer (const std::string src, int idxhead) {
    std::string token = "";
    size_t idx = 0;

    while ( src[idx] != '\0' ) {
        token += src[idx];

        if ( token == ";" ) {
            push_token(idxhead, SEMI_COLON, ";");
            token = "";
        }
        if ( token == "exit" ) {
            push_token(idxhead, EXIT_FUNCTION, "exit");
            token = "";
        }
        else if ( std::isdigit(src[idx]) ) {
            std::string number = get_all_num(src, idx);
            push_token(idxhead, NUMBER, number);

            idx += number.size() - 1;
            token = "";
        }
        else if ( src[idx] == '-' && std::isdigit(src[idx + 1]) ) {
            std::string number = get_all_num(src, idx + 1);
            number.insert(0, "-");
            push_token(idxhead, NUMBER, number);

            idx += number.size() - 1;
            token = "";
        }

        idx++;
    }
}

void clean (const std::string src) {
    std::string cline = "";
    size_t idx = 0;

    while ( src[idx] != '\0' ) {
        while ( std::isspace(src[idx]) ) {
            idx++;
        }

        if ( src[idx] == '#' )
            comment = true;
        while ( comment ) {
            idx++;
            if ( src[idx] == '#' ) {
                comment = false;
            }
            // it means the comment is in several lines
            if ( idx > src.size() ) {
                return;
            }
        }

        cline += src[idx];
        idx++;
    }

    if ( cline != "#" ) {
        if ( cline.at(idx - 2) != ';' ) {
            _err_semicolon();
        }
        printf("hey\n");
        int idxhead = get_headidx();
        lexer(cline, idxhead);
    }
}


#endif
