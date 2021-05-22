#pragma once

#include <algorithm>
#include <map>
#include <string>

class Token
{
  public:
    enum _Token : char
    {
      UNDEFINED,

      // Builtin functions //
      INCR,
      DECR,
      CLEAR,
      INVERT,
      ASSIGN,
      IMPORT,
      EXPORT,
      EXPORC,

      // Seperator
      SEPERATOR,

      // Loop & condition
      IF,
      THEN,
      ELSE,
      WHILE,
      DO,
      END,

      // Binary operators
      EQUAL             ,
      NOT               ,
      LESS_THAN         ,
      LESS_THAN_OR_EQUAL   ,
      GREATER_THAN      ,
      GREATER_THAN_OR_EQUAL,

      //
      OPENING_PARENTHESES,
      CLOSING_PARENTHESIS,

      // Math operators
      PLUS    ,
      MINUS   ,
      MULTIPLY,
      DIVIDE  ,

      NUMBER,
      IDENTIFIER,

      END_OF_FILE = -1,
      END_OF_LINE = -2,
    };

    const static std::map<std::string, Token> StringToToken;

  public:
    Token() = default;
    ~Token() = default;

    Token(const _Token& T);

    operator _Token() const;
    explicit operator bool() = delete;

    bool IsBuiltin() const;
    bool IsOperator() const;

    static Token FromString(const std::string& Name);
    static std::string ToString(const Token& T);

  private:
    _Token m_Value;
};
