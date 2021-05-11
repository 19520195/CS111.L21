#pragma once

#include "lexer_token.hh"
#include "bin_op_prec.hh"
#include <iostream>

class lexer {
public:
    lexer();

private:
    char forward_char();
    lexer_token forward_token();

public:
    // Tokens and characters //
    char get_next_char();
    lexer_token get_next_token();

    char get_last_char() const;
    lexer_token get_last_token() const;

    // Lexer cursor informations //
    unsigned int get_line() const;
    unsigned int get_index() const;
    unsigned int get_number_value() const;
    std::string  get_identifier_value() const;
    std::string  get_cursor_info() const;

private:
    char  m_last_char;
    lexer_token m_last_token;

    unsigned int m_line;
    unsigned int m_index;

    unsigned int m_number_value;
    std::string  m_identifier_value;
};
