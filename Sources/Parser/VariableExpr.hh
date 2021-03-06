#pragma once

#include "ExprAST.hh"

class VariableExpr : public ExprAST
{
  public:
    VariableExpr(const std::string& Name);

    std::string GenerateCode() const;
    std::unique_ptr<ExprAST> Execute(DataTable& Table);
    void LookupVaribale(std::set<std::string>& Set) const;

    std::string GetValue() const;

  private:
    std::string m_Name;
};
