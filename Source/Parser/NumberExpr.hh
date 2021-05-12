#pragma once

#include "ExprAST.hh"

class NumberExpr : public ExprAST
{
  public:
    NumberExpr(const unsigned int& Value);
    std::unique_ptr<ExprAST> Execute(DataTable& Table);
    unsigned int GetValue() const;

  private:
    unsigned int m_Value;
};
