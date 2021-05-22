#pragma once

#include <algorithm>
#include <map>
#include <string>

class Token
{
  public:
    enum EToken : char
    {
      UNDEFINED,

      // Number & Identifer
      NUMBER,
      IDENTIFIER,

      // Special signs
      SEMI_COLON,
      OPENING_PARENTHESES,
      CLOSING_PARENTHESIS,

      // Built-in functions
      BUILTIN_FUNCTION = 0x10,
      INCR  ,
      DECR  ,
      CLEAR ,
      INVERT,
      ASSIGN,
      IMPORT,
      EXPORT,
      EXPORC,

      // Controller
      CONTROLLER = 0x20,
      IF   ,
      THEN ,
      ELSE ,
      WHILE,
      DO   ,
      END  ,

      // Comparison operators
      COMPARISON_OPERATOR = 0x30,
      EQUAL                ,
      NOT_EQUAL            ,
      LESS_THAN            ,
      LESS_THAN_OR_EQUAL   ,
      GREATER_THAN         ,
      GREATER_THAN_OR_EQUAL,

      // Mathematic operators
      MATHEMATIC_OPERATOR = 0x40,
      PLUS    ,
      MINUS   ,
      MULTIPLY,
      DIVIDE  ,

      // Sepecial characters
      END_OF_FILE = -1,
      END_OF_LINE = -2,
    };

    const static std::map<std::string, Token> StringToToken;

  public:
    Token() = default;
    ~Token() = default;

    Token(const EToken& T);

    operator EToken() const;
    explicit operator bool() = delete;

    bool IsBuiltinFunction() const;
    bool IsMathematicOperator() const;

    static Token FromString(const std::string& Name);
    static std::string ToString(const Token& T);

  private:
    EToken m_Value;
};
