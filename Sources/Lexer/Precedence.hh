#pragma once

#include "Token.hh"

class Precedence
{
  public:
    enum EPrecedence : unsigned int
    {
      NONE_LOW = 0,
      NONE_HIGH = 1,

      PLUS     = 2000,
      MINUS    = 2000,

      MULTIPLY = 3000,
      DIVIDE   = 3000,
    };

    static const std::map<Token, Precedence> TokenToPrecedence;
    static const std::map<std::string, Precedence> StringToPrecedence;

  public:
    Precedence() = default;
    ~Precedence() = default;

    Precedence(const EPrecedence& P);
    Precedence(const unsigned int& U);

    operator EPrecedence() const;
    explicit operator bool() = delete;

    bool operator<(const Precedence& ShiftRight);

    static Precedence FromToken(const Token& T);
    static Precedence FromString(const std::string& Name);
    static std::string ToString(const Precedence& P);

  private:
    unsigned int m_Value;
};

