#include "NumberExpr.hh"

NumberExpr::NumberExpr(const unsigned int& Value) : m_Value(Value)
{
}

std::string NumberExpr::GenerateCode() const
{
  return std::to_string(m_Value);
}

std::unique_ptr<ExprAST> NumberExpr::Execute(DataTable& Table)
{
  return std::make_unique<NumberExpr>(m_Value);
}

void NumberExpr::LookupVaribale(std::set<std::string>& Set) const
{
}

unsigned int NumberExpr::GetValue() const
{
  return m_Value;
}
