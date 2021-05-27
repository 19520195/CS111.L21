#include "IfExpr.hh"

IfExpr::IfExpr(std::unique_ptr<ExprAST> Condition, std::unique_ptr<ExprAST> CodeBlock, std::unique_ptr<ExprAST> ElseBlock)
  : m_Condition(std::move(Condition)), m_CodeBlock(std::move(CodeBlock)), m_ElseBlock(std::move(ElseBlock))
{
}

std::string IfExpr::GenerateCode() const
{
  std::string Codes = "if " + m_Condition->GenerateCode() + "\n";
  Codes += "{\n" + m_CodeBlock->GenerateCode() + "}\n";
  if (m_ElseBlock != nullptr)
    Codes += "else\n{\n" + m_ElseBlock->GenerateCode() + "}\n";
  return Codes;
}

std::unique_ptr<ExprAST> IfExpr::Execute(DataTable& Table)
{
  if (((NumberExpr*)(m_Condition->Execute(Table).get()))->GetValue())
    return m_CodeBlock->Execute(Table);
  if (!m_ElseBlock)
    return std::make_unique<NumberExpr>(0);
  return m_ElseBlock->Execute(Table);
}

void IfExpr::LookupVaribale(std::set<std::string>& Set) const
{
  m_Condition->LookupVaribale(Set);
  m_CodeBlock->LookupVaribale(Set);
  if (m_ElseBlock != nullptr)
    m_ElseBlock->LookupVaribale(Set);
}
