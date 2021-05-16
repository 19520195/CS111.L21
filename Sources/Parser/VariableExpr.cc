#include "VariableExpr.hh"

VariableExpr::VariableExpr(const std::string& Name) : m_Name(Name)
{
  // VariableExpr::VariableExpr
}

std::unique_ptr<ExprAST> VariableExpr::Execute(DataTable& Table)
{
  return std::make_unique<NumberExpr>(Table[m_Name]);
}

std::string VariableExpr::GetValue() const
{
  return m_Name;
}
