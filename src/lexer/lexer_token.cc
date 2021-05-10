#include "lexer_token.hh"

lexer_token::lexer_token(const token_value& value) : m_value(value) {
    // lexer_token::lexer_token
}

lexer_token::operator token_value() const {
    return m_value;
}
