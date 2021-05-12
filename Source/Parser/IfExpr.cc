#include "IfExpr.hh"

IfExpr::IfExpr(std::unique_ptr<ExprAST> Condition, std::unique_ptr<ExprAST> CodeBlock, std::unique_ptr<ExprAST> ElseBlock)
  : m_Condition(std::move(Condition)), m_CodeBlock(std::move(CodeBlock)), m_ElseBlock(std::move(ElseBlock))
{
  if (m_ElseBlock == nullptr)
    m_ElseBlock = std::make_unique<NumberExpr>(0);
}

std::unique_ptr<ExprAST> IfExpr::Execute(DataTable& Table)
{
  if (((NumberExpr*)(m_Condition->Execute(Table).get()))->GetValue())
    return m_CodeBlock->Execute(Table);
  return m_ElseBlock->Execute(Table);
}
