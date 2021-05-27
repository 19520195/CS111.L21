#include "BlockExpr.hh"

void BlockExpr::InsertExpr(std::unique_ptr<ExprAST> Expr)
{
  m_Exprs.emplace_back(std::move(Expr));
}

std::string BlockExpr::GenerateCode() const
{
  std::string Codes;
  for (auto& Expr : m_Exprs)
    Codes += Expr->GenerateCode() + ";\n";
  return Codes;
}

std::unique_ptr<ExprAST> BlockExpr::Execute(DataTable& Table)
{
  std::unique_ptr<ExprAST> ReturnedExpr;
  for (auto& Expr : m_Exprs)
    ReturnedExpr = Expr->Execute(Table);
  return ReturnedExpr;
}

void BlockExpr::LookupVaribale(std::set<std::string>& Set) const
{
  for (const auto& Expr : m_Exprs)
    Expr->LookupVaribale(Set);
}
