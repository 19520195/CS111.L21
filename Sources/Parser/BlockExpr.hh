#pragma once

#include "ExprAST.hh"
#include <vector>

class BlockExpr : public ExprAST
{
  public:
    BlockExpr() = default;
    void InsertExpr(std::unique_ptr<ExprAST> Expr);

    std::string GenerateCode() const;
    std::unique_ptr<ExprAST> Execute(DataTable& Table);
    void LookupVaribale(std::set<std::string>& Set) const;

  private:
    std::vector<std::unique_ptr<ExprAST>> m_Exprs;
};
