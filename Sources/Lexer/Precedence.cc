#include "Precedence.hh"

const std::map<Token, Precedence> Precedence::TokenToPrecedence = std::map<Token, Precedence>
{
  { Token::PLUS    , Precedence::PLUS     },
  { Token::MINUS   , Precedence::MINUS    },
  { Token::MULTIPLY, Precedence::MULTIPLY },
  { Token::DIVIDE  , Precedence::DIVIDE   },

  { Token::EQUAL                , Precedence::COMPARISION },
  { Token::NOT_EQUAL            , Precedence::COMPARISION },
  { Token::GREATER_THAN         , Precedence::COMPARISION },
  { Token::GREATER_THAN_OR_EQUAL, Precedence::COMPARISION },
  { Token::LESS_THAN            , Precedence::COMPARISION },
  { Token::LESS_THAN_OR_EQUAL   , Precedence::COMPARISION },

  { Token::OPENING_PARENTHESES, Precedence::NONE_HIGH },
  { Token::CLOSING_PARENTHESIS, Precedence::NONE_HIGH },
};

const std::map<std::string, Precedence> Precedence::StringToPrecedence = std::map<std::string, Precedence>
{
  { "+", Precedence::PLUS     },
  { "-", Precedence::MINUS    },
  { "*", Precedence::MULTIPLY },
  { "/", Precedence::DIVIDE   },

  { "equal", Precedence::COMPARISION },
  { "not"  , Precedence::COMPARISION },
  { "="    , Precedence::COMPARISION },
  { "!="   , Precedence::COMPARISION },
  { ">"    , Precedence::COMPARISION },
  { ">="   , Precedence::COMPARISION },
  { "<"    , Precedence::COMPARISION },
  { "<="   , Precedence::COMPARISION },
};

Precedence::Precedence(const EPrecedence& P) : m_Value(P)
{

}

Precedence::Precedence(const unsigned int& U) : m_Value(U)
{

}

Precedence::operator EPrecedence() const
{
  return (EPrecedence)(m_Value % 1000);
}

bool Precedence::operator<(const Precedence& ShiftRight)
{
  return m_Value < ShiftRight.m_Value;
}

Precedence Precedence::FromToken(const Token& T)
{
  const auto& Result = TokenToPrecedence.find(T);
  if (Result == TokenToPrecedence.end())
    return Precedence::NONE_LOW;
  return Result->second;
}

Precedence Precedence::FromString(const std::string& Name)
{
  const auto& Result = StringToPrecedence.find(Name);
  if (Result == StringToPrecedence.end())
    return Precedence::NONE_LOW;
  return Result->second;
}

std::string Precedence::ToString(const Precedence& P)
{
  const auto& Result = std::find_if
  (
    StringToPrecedence.begin(),
    StringToPrecedence.end(),
    [P](const auto& I)
    {
      return I.second == (EPrecedence)(P.m_Value / 1000 * 1000);
    }
  );

  if (Result == StringToPrecedence.end())
    return "undefined";
  return Result->first;
}
