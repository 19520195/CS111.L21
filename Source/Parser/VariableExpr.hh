#pragma once

#include "ExprAST.hh"

class VariableExpr : public ExprAST
{
  public:
    VariableExpr(const std::string& Name);
    std::unique_ptr<ExprAST> Execute(DataTable& Table);
    std::string GetValue() const;

  private:
    std::string m_Name;
};
