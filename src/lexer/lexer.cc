#include "lexer.hh"

lexer::lexer() : m_line(1), m_index(0), m_last_char(' ') {
    // lexer::lexer
}

char lexer::forward_char() {
    return std::cin.get();
}

token lexer::forward_token() {
    // Clear all whitespaces
    while (isspace(m_last_char)) {
        this->get_next_char();
    }

    // Identifier: [a-zA-Z][a-zA-Z0-9]*
    if (isalpha(m_last_char)) {
        m_identifier_value = m_last_char;
        while (isalnum(this->get_next_char())) {
            m_identifier_value += m_last_char;
        }

        // Bultin funcs
        if (m_identifier_value ==   "incr") return TOKEN_INCR  ;
        if (m_identifier_value ==   "decr") return TOKEN_DECR  ;
        if (m_identifier_value ==  "clear") return TOKEN_CLEAR ;
        if (m_identifier_value == "invert") return TOKEN_INVERT;

        // Loop and condition
        if (m_identifier_value ==    "if") return TOKEN_IF   ;
        if (m_identifier_value ==  "then") return TOKEN_THEN ;
        if (m_identifier_value == "while") return TOKEN_WHILE;
        if (m_identifier_value ==    "do") return TOKEN_DO   ;
        if (m_identifier_value ==   "end") return TOKEN_END  ;

        // Operator identifier
        if (m_identifier_value == "not") return TOKEN_NOT;

        // Input/Ouput
        if (m_identifier_value == "import") return TOKEN_IMPORT;
        if (m_identifier_value == "export") return TOKEN_EXPORT;

        // Identifier
        return TOKEN_IDENTIFIER;
    }

    // Number: [0-9]+
    if (isdigit(m_last_char)) {
        std::string number;
        do {
            number += m_last_char;
            this->get_next_char();
        } while (isdigit(m_last_char));

        m_number_value = std::strtoul(number.c_str(), NULL, 0);
        return TOKEN_NUMBER;
    }

    // Comment ingnore
    if (m_last_char == '#') {
        do if (this->get_next_char() == '\n') ++m_line;
        while (m_last_char != EOF && m_last_char != '\n');
        if (m_last_char != EOF) {
            return this->get_next_token();
        }
    }

    // End of file
    if (m_last_char == EOF) {
        this->get_next_char();
        return END_OF_FILE;
    }

    // Seperate character
    if (m_last_char == ';') {
        this->get_next_char();
        return TOKEN_SEPARATOR;
    }

    // Strange characeter
    return CHARACTER;
}

char lexer::get_next_char() {
    m_last_char = forward_char();
    if (m_last_char == '\n') {
        ++m_line;
        m_index = 0;
    }

    ++m_index;
    return m_last_char;
}

token lexer::get_next_token() {
    m_last_token = forward_token();
    return m_last_token;
}

char lexer::get_last_char() const {
    return m_last_char;
}

token lexer::get_last_token() const {
    return m_last_token;
}

unsigned int lexer::get_line() const {
    return m_line;
}

unsigned int lexer::get_index() const {
    return m_index - 1;
}

unsigned int lexer::get_number_value() const {
    return m_number_value;
}

std::string lexer::get_identifier_value() const {
    return m_identifier_value;
}
