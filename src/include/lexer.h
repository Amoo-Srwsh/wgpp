#ifndef WG___LEXER_H
#define WG___LEXER_H

#include "token-func.h"
#include "helps.h"

/* A comment could be in a several lines, so we need to know
 * if a comment was opened on 1 line and will be closed on N line */
bool comment = false;

void lexer (const std::string _final, int idxTKN) {
    size_t idx = 0;
    std::string token = "";

    while ( _final[idx] != '\0' ) {
        token += _final[idx];

        if ( token == ";" ) {
            push_token(idxTKN, SEMI_COLON, token);
            token = "";
        }
        else if ( token == "print" ) {
            push_token(idxTKN, KEYWORD, token);
            token = "";
        }
        else if ( token == "exit" ) {
            push_token(idxTKN, KEYWORD, token);
            token = "";
        }
        else if ( std::isdigit(token[0]) ) {
            std::string number = get_whole_num(_final, idx);
            push_token(idxTKN, NUMBER, number);
            token = "";
            idx += number.size() - 1;
        }
        else if ( token[0] == '-' && std::isdigit(_final[idx + 1]) ) {
            std::string number = get_whole_num(_final, idx);
            push_token(idxTKN, NUMBER, number);
            token = "";
            idx += number.size() - 1;
        }
        else if ( token[0] == '"' ) {
            std::string str = get_whole_str(_final, idx);
            str += '"';
            push_token(idxTKN, STRING, str);
            idx += str.size() - 1;
            token = "";
        }

        idx++;
    }
}

void clean_line (const std::string oline) {
    size_t idx = 0;
    std::string cline = "";

    while ( oline[idx] != '\0' ) {
        while ( std::isspace(oline[idx]) ) idx++;
        if ( oline[idx] == '#' ) comment = true;

        while ( comment ) {
            idx++;
            if ( oline[idx] == '#' ) comment = false;
            if ( idx >= oline.size() ) return;
        }

        if ( oline[idx] == '"' ) {
            std::string str = get_whole_str(oline, idx);
            cline.append(str);
            idx += str.size();
        }

        cline += oline[idx];
        idx++;
    }

    if ( cline != "#" ) {
        if ( cline[cline.size() - 1] != ';' ) {
            semi_colon_expected();
        }

        int idxhead = insert_head();
        lexer(cline, idxhead);
    }
}




#endif
