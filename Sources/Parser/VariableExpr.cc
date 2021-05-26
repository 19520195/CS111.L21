#include "VariableExpr.hh"

VariableExpr::VariableExpr(const std::string& Name) : m_Name(Name)
{
}

std::string VariableExpr::GenerateCode() const
{
  return m_Name;
}

std::unique_ptr<ExprAST> VariableExpr::Execute(DataTable& Table)
{
  return std::make_unique<NumberExpr>(Table[m_Name]);
}

std::string VariableExpr::GetValue() const
{
  return m_Name;
}
