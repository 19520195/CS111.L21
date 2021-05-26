#pragma once

#include "Lexer/Token.hh"
#include "ExprAST.hh"
#include <iostream>

class BuiltinExpr : public ExprAST
{
  public:
    BuiltinExpr(const Token& T, const std::string& I, std::unique_ptr<ExprAST> E = nullptr);

    std::string GenerateCode() const;
    std::unique_ptr<ExprAST> Execute(DataTable& Table);

  private:
    Token                    m_Token;
    std::string              m_Identifier;
    std::unique_ptr<ExprAST> m_Expression;
};
