#pragma once

#include "bin_op_prec.hh"

class lexer_token {
public:
    enum token_value : char {
        // Parentheses expression //
        OPEN_PAREN,
        CLOSE_PAREN,

        // Bultin function
        INCR  ,
        DECR  ,
        CLEAR ,
        INVERT,

        // Input / Output
        IMPORT,
        EXPORT,

        // Loop / If / Else conditions
        WHILE,
        DO   ,
        IF   ,
        THEN ,
        ELSE ,
        END  ,

        // Binary operators
        NOT,
        EQUAL,

        // Math operators
        PLUS    ,
        MINUS   ,
        MULTIPLY,
        DIVIDE  ,

        // Varibale types //
        IDENTIFIER,
        NUMBER    ,

        // Separator //
        SEP,

        // Special characters //
        END_OF_FILE = -1,
        END_OF_LINE = -2,
        UNKNOW_CHAR = -3,
    };

public:
    lexer_token() = default;
    ~lexer_token() = default;
    lexer_token(const token_value& value);

    operator token_value() const;
    explicit operator bool() = delete;

    bool is_builtin() const;
    bin_op_prec get_prec() const;

private:
    token_value m_value;
};
