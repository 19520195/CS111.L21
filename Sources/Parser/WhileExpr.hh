#pragma once

#include "IfExpr.hh"

class WhileExpr : public ExprAST
{
  public:
    WhileExpr(std::unique_ptr<ExprAST> Condition, std::unique_ptr<ExprAST> CodeBlock);

    std::string GenerateCode() const;
    std::unique_ptr<ExprAST> Execute(DataTable& Table);
    void LookupVaribale(std::set<std::string>& Set) const;

  private:
    std::unique_ptr<ExprAST> m_Condition;
    std::unique_ptr<ExprAST> m_CodeBlock;
};
