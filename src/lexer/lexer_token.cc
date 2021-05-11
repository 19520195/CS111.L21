#include "lexer_token.hh"

lexer_token::lexer_token(const token_value& value) : m_value(value) {
    // lexer_token::lexer_token
}

lexer_token::operator token_value() const {
    return m_value;
}

bool lexer_token::is_builtin() const {
    return m_value == INCR
        || m_value == DECR
        || m_value == CLEAR
        || m_value == INVERT
    ;
}

bin_op_prec lexer_token::get_prec() const {
    switch (m_value) {
        case NOT: return bin_op_prec::NOT_EQUAL;
        default : return bin_op_prec::NONE;
    }
}
