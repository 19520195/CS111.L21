#include "Token.hh"

const std::map<std::string, Token> Token::ST_Table = std::map<std::string, Token>
{
  // Builtin functions
  {   "incr", Token::INCR   },
  {   "decr", Token::DECR   },
  {  "clear", Token::CLEAR  },
  { "invert", Token::INVERT },
  { "assign", Token::ASSIGN },
  { "import", Token::IMPORT },
  { "export", Token::EXPORT },

  // Condition
  {   "if", Token::IF   },
  { "then", Token::THEN },
  { "else", Token::ELSE },

  // While
  { "while", Token::WHILE },
  {    "do", Token::DO    },

  // End
  { "end", Token::END },

  // Binary operator
  { "equal", Token::EQUAL },
  {   "not", Token::NOT   },
  {  "=", Token::EQUAL             },
  { "!=", Token::NOT               },
  {  "<", Token::LESS_THAN         },
  { "<=", Token::LESS_THAN_EQUAL   },
  {  ">", Token::GREATER_THAN      },
  { ">=", Token::GREATER_THAN_EQUAL},

  // Math operators
  { "+", Token::PLUS     },
  { "-", Token::MINUS    },
  { "*", Token::MULTIPLY },
  { "/", Token::DIVIDE   },
};

Token::Token(const _Token& T = UNDEFINED) : m_value(T)
{
  // Token::Token
}

Token::operator _Token() const
{
  return m_value;
}

bool Token::IsBuiltin() const
{
  return m_value == Token::INCR
      || m_value == Token::DECR
      || m_value == Token::CLEAR
      || m_value == Token::ASSIGN
      || m_value == Token::INVERT
      || m_value == Token::IMPORT
      || m_value == Token::EXPORT;
}

Token Token::FromString(const std::string& Name)
{
  if (ST_Table.find(Name) == ST_Table.end())
    return Token::IDENTIFIER;
  return ST_Table.at(Name);
}

std::string Token::ToString(const Token& Value)
{
  std::map<std::string, Token>::const_iterator result = std::find_if(ST_Table.begin(), ST_Table.end(),
    [Value](const auto& Object) { return Object.second == Value; }
  );

  if (result == ST_Table.end())
    return "identifier";
  return result->first;
}
