#pragma once

#include "ExprAST.hh"

class IfExpr : public ExprAST
{
  public:
    IfExpr(std::unique_ptr<ExprAST> Condition, std::unique_ptr<ExprAST> CodeBlock, std::unique_ptr<ExprAST> ElseBlock);

    std::string GenerateCode() const;
    std::unique_ptr<ExprAST> Execute(DataTable& Table);
    void LookupVaribale(std::set<std::string>& Set) const;

  protected:
    std::unique_ptr<ExprAST> m_Condition;
    std::unique_ptr<ExprAST> m_CodeBlock;
    std::unique_ptr<ExprAST> m_ElseBlock;
};
