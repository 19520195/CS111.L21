#include "Token.hh"

const std::map<std::string, Token> Token::StringToToken = std::map<std::string, Token>
{
  // Builtin functions
  { "incr"  , Token::INCR   },
  { "decr"  , Token::DECR   },
  { "clear" , Token::CLEAR  },
  { "invert", Token::INVERT },
  { "assign", Token::ASSIGN },
  { "import", Token::IMPORT },
  { "export", Token::EXPORT },
  { "exporc", Token::EXPORC },

  // Controllers
  { "if"   , Token::IF    },
  { "then" , Token::THEN  },
  { "else" , Token::ELSE  },
  { "while", Token::WHILE },
  { "do"   , Token::DO    },
  { "end"  , Token::END   },

  // Comparision operators
  { "equal", Token::EQUAL                },
  { "not"  , Token::NOT_EQUAL            },
  { "="    , Token::EQUAL                },
  { "!="   , Token::NOT_EQUAL            },
  { "<"    , Token::LESS_THAN            },
  { "<="   , Token::LESS_THAN_OR_EQUAL   },
  { ">"    , Token::GREATER_THAN         },
  { ">="   , Token::GREATER_THAN_OR_EQUAL},

  // Mathematic operators
  { "+", Token::PLUS     },
  { "-", Token::MINUS    },
  { "*", Token::MULTIPLY },
  { "/", Token::DIVIDE   },
};

Token::Token(const _Token& T = UNDEFINED) : m_Value(T)
{

}

Token::operator _Token() const
{
  return m_Value;
}

bool Token::IsBuiltinFunction() const
{
  return m_Value & Token::BUILTIN_FUNCTION;
}

bool Token::IsMathematicOperator() const
{
  return m_Value & Token::MATHEMATIC_OPERATOR;
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
