#include "NumberExpr.hh"

NumberExpr::NumberExpr(const unsigned int& Value) : m_Value(Value)
{
  // NumberExpr::NumberExpr
}

std::unique_ptr<ExprAST> NumberExpr::Execute(DataTable& Table)
{
  return std::make_unique<NumberExpr>(m_Value);
}

unsigned int NumberExpr::GetValue() const
{
  return m_Value;
}
