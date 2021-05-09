#pragma once

#include "token.hh"
#include "precedence.hh"
#include <iostream>

class lexer {
public:
    lexer();

    char forward_char();
    token forward_token();

    char get_next_char();
    token get_next_token();

    char get_last_char() const;
    token get_last_token() const;

    unsigned int get_line() const;
    unsigned int get_index() const;
    unsigned int get_number_value() const;
    std::string  get_identifier_value() const;

private:
    char  m_last_char;
    token m_last_token;

    unsigned int m_line;
    unsigned int m_index;

    unsigned int m_number_value;
    std::string  m_identifier_value;
};
