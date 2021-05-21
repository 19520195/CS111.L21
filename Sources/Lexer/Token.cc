#include "Token.hh"

const std::map<std::string, Token> Token::StringToToken = std::map<std::string, Token>
{
  // Builtin functions
  { "incr", Token::INCR },
  { "decr", Token::DECR },
  { "clear", Token::CLEAR },
  { "invert", Token::INVERT },
  { "assign", Token::ASSIGN },
  { "import", Token::IMPORT },
  { "export", Token::EXPORT },

  // Condition
  { "if", Token::IF },
  { "then", Token::THEN },
  { "else", Token::ELSE },

  // While
  { "while", Token::WHILE },
  { "do", Token::DO },

  // End
  { "end", Token::END },

  // Binary operator
  { "equal", Token::EQUAL },
  { "not", Token::NOT },

  { "=", Token::EQUAL },
  { "!=", Token::NOT },
  { "<", Token::LESS_THAN },
  { "<=", Token::LESS_THAN_EQUAL },
  { ">", Token::GREATER_THAN },
  { ">=", Token::GREATER_THAN_EQUAL},

  // Math operators
  { "+", Token::PLUS },
  { "-", Token::MINUS },
  { "*", Token::MULTIPLY },
  { "/", Token::DIVIDE },
};

Token::Token(const _Token& T = UNDEFINED) : m_Value(T)
{
  // Token::Token
}

Token::operator _Token() const
{
  return m_Value;
}

bool Token::IsBuiltin() const
{
  return m_Value == Token::INCR
    || m_Value == Token::DECR
    || m_Value == Token::CLEAR
    || m_Value == Token::ASSIGN
    || m_Value == Token::INVERT
    || m_Value == Token::IMPORT
    || m_Value == Token::EXPORT;
}

bool Token::IsOperator() const
{
  return m_Value == Token::PLUS
    || m_Value == Token::MINUS
    || m_Value == Token::MULTIPLY
    || m_Value == Token::DIVIDE;
}

Token Token::FromString(const std::string& Name)
{
  const auto& Result = StringToToken.find(Name);
  if (Result == StringToToken.end())
    return Token::IDENTIFIER;
  return Result->second;
}

std::string Token::ToString(const Token& T)
{
  const auto& Result = std::find_if
  (
    StringToToken.begin(),
    StringToToken.end(),
    [T](const auto& I)
    {
      return I.second == T;
    }
  );

  if (Result == StringToToken.end())
    return "identifier";
  return Result->first;
}
