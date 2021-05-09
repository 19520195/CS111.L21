#pragma once

enum token : char {
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,

    // Bultin function
    TOKEN_INCR  ,
    TOKEN_DECR  ,
    TOKEN_CLEAR ,
    TOKEN_INVERT,

    // Input / Output
    TOKEN_IMPORT,
    TOKEN_EXPORT,

    // Loop, If else condtion
    TOKEN_WHILE,
    TOKEN_DO   ,
    TOKEN_IF   ,
    TOKEN_THEN ,
    TOKEN_END  ,

    // Binary operator
    TOKEN_NOT,
    TOKEN_EQUAL,

    // Math operator
    TOKEN_PLUS    ,
    TOKEN_MINUS   ,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE  ,

    // VARAIBLE TYPE
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER    ,

    // SEPARATOR ;
    TOKEN_SEP,

    // SPECICAL CHARACTER
    TOKEN_END_OF_FILE = -1,
    TOKEN_END_OF_LINE = -2,
    TOKEN_UNKNOW_CHAR = -3,
};
