#include "Lexer.hh"

const char        Lexer::Seperator      = ';';
const std::string Lexer::IgnoreCharter  = " \t\r\n";
const std::string Lexer::MathOpSigns    = "+-*/";
const std::string Lexer::CompareOpSigns = "=><!";

Lexer::Lexer() :
  m_LastChar(' '),
  m_LastToken(Token::UNDEFINED),
  m_Number(0)
{
}

char Lexer::ForwardChar()
{
  return std::cin.get();
}

Token Lexer::ForwardToken()
{
  // Ignore charater
  while (IgnoreCharter.find(GetLastChar()) != std::string::npos)
    GetNextChar();

  // Identifier: [a-zA-Z][a-zA-Z0-9]*
  if (isalpha(GetLastChar()))
  {
    // Get remain identifier
    m_Identifier = GetLastChar();
    while (isalnum(GetNextChar()))
      m_Identifier += GetLastChar();
    return Token::FromString(m_Identifier);
  }

  // Number [0-9]*
  if (isdigit(GetLastChar()))
  {
    // Get remain digit
    m_Identifier = GetLastChar();
    while (isdigit(GetNextChar()))
      m_Identifier += GetLastChar();
    m_Number = std::stoul(m_Identifier);
    return Token::NUMBER;
  }

  // Seperator
  if (GetLastChar() == Seperator)
  {
    GetNextChar();
    m_Identifier.clear();
    return Token::SEPERATOR;
  }

  // Binary operator
  if (MathOpSigns.find(GetLastChar()) != std::string::npos || CompareOpSigns.find(GetLastChar()) != std::string::npos)
  {
    m_Identifier = GetLastChar();
    while (IgnoreCharter.find(GetNextChar()) == std::string::npos && !isalnum(GetLastChar()))
      m_Identifier += GetLastChar();
    return Token::FromString(m_Identifier);
  }

  // Comments
  if (GetLastChar() == '#')
  {
    while (GetNextChar() != '\n');
    GetNextChar();
    return GetNextToken();
  }

  // End of file
  if (GetLastChar() == EOF)
    return Token::END_OF_FILE;

  // Undefined token
  return Token::UNDEFINED;
}

char Lexer::GetNextChar()
{
  m_LastChar = ForwardChar();
  return m_LastChar;
}

Token Lexer::GetNextToken()
{
  m_LastToken = ForwardToken();
  return m_LastToken;
}

std::string Lexer::GetNextIdentifier()
{
  GetNextToken();
  return GetIdentifierValue();
}

char Lexer::GetLastChar() const
{
  return m_LastChar;
}

Token Lexer::GetLastToken() const
{
  return m_LastToken;
}

unsigned int Lexer::GetNumberValue() const
{
  return m_Number;
}

std::string Lexer::GetIdentifierValue() const
{
  return m_Identifier;
}
