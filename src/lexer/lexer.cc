#include "lexer.hh"

lexer::lexer() : m_line(1), m_index(0), m_last_char(' ') {
    // lexer::lexer
}

char lexer::forward_char() {
    return std::cin.get();
}

lexer_token lexer::forward_token() {
    // Clear all whitespaces
    while (isspace(get_next_char()));

    // Identifier: [a-zA-Z][a-zA-Z0-9]*
    if (isalpha(get_last_char())) {
        m_identifier_value = get_last_char();
        while (isalnum(get_next_char()))
            m_identifier_value += get_last_char();

        // Bultin functions
        if (m_identifier_value ==   "incr") return lexer_token::INCR  ;
        if (m_identifier_value ==   "decr") return lexer_token::DECR  ;
        if (m_identifier_value ==  "clear") return lexer_token::CLEAR ;
        if (m_identifier_value == "invert") return lexer_token::INVERT;

        // Loop and condition keywords
        if (m_identifier_value ==    "if") return lexer_token::IF   ;
        if (m_identifier_value ==  "then") return lexer_token::THEN ;
        if (m_identifier_value ==  "else") return lexer_token::ELSE ;
        if (m_identifier_value == "while") return lexer_token::WHILE;
        if (m_identifier_value ==    "do") return lexer_token::DO   ;
        if (m_identifier_value ==   "end") return lexer_token::END  ;

        // Binary operators
        if (m_identifier_value ==  "eq") return lexer_token::EQUAL;
        if (m_identifier_value == "not") return lexer_token::NOT  ;

        // Input and Output
        if (m_identifier_value == "import") return lexer_token::IMPORT;
        if (m_identifier_value == "export") return lexer_token::EXPORT;

        // Identifier
        return lexer_token::IDENTIFIER;
    }

    // Number: [0-9]+
    if (isdigit(get_last_char())) {
        std::string number;
        do number += get_last_char();
        while (isdigit(get_next_char()));

        m_number_value = std::strtoul(number.c_str(), NULL, 0);
        return lexer_token::NUMBER;
    }

    // Comment ignore
    if (get_last_char() == '#') {
        do m_line += (get_next_char() == '\n');
        while (get_last_char() != EOF && get_last_char() != '\n');

        if (get_last_char() != EOF)
            return get_next_token();
    }

    switch (get_last_char()) {
        case ';': return lexer_token::SEP;

        case '(': return lexer_token::OPEN_PAREN;
        case ')': return lexer_token::CLOSE_PAREN;

        case EOF: return lexer_token::END_OF_FILE;
        default : return lexer_token::UNKNOW_CHAR;
    }
}

char lexer::get_next_char() {
    m_last_char = forward_char();
    if (m_last_char == '\n')
        ++m_line, m_index = 0;
    return ++m_index, m_last_char;
}

lexer_token lexer::get_next_token() {
    m_last_token = forward_token();
    return m_last_token;
}

char lexer::get_last_char() const {
    return m_last_char;
}

lexer_token lexer::get_last_token() const {
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
