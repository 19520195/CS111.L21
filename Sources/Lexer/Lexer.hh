#pragma once

#include "Token.hh"
#include <iostream>
#include <memory>

class Lexer
{
  private:
    char ForwardChar();
    Token ForwardToken();

  public:
    Lexer(std::istream& Input = std::cin);
    ~Lexer();

    char GetNextChar();
    Token GetNextToken();
    std::string GetNextIdentifier();

    char GetLastChar() const;
    Token GetLastToken() const;

    unsigned int GetNumberValue() const;
    std::string GetIdentifierValue() const;

  public:
    static const char Seperator;
    static const std::string IgnoreCharter;
    static const std::string MathOperator;
    static const std::string CompareOperator;

  private:
    char  m_LastChar;
    Token m_LastToken;

    unsigned int m_Number;
    std::string  m_Identifier;

    std::unique_ptr<std::istream> m_Input;
};
