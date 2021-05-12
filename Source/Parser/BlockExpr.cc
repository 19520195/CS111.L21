#include "BlockExpr.hh"

void BlockExpr::InsertExpr(std::unique_ptr<ExprAST> Expr)
{
  m_Exprs.emplace_back(std::move(Expr));
}

std::unique_ptr<ExprAST> BlockExpr::Execute(DataTable& Table)
{
  std::unique_ptr<ExprAST> ReturnedExpr;
  for (auto& Expr : m_Exprs)
    ReturnedExpr = Expr->Execute(Table);
  return ReturnedExpr;
}
