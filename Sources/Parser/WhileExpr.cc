#include "WhileExpr.hh"

WhileExpr::WhileExpr(std::unique_ptr<ExprAST> Condition, std::unique_ptr<ExprAST> CodeBlock)
  : m_Condition(std::move(Condition)), m_CodeBlock(std::move(CodeBlock))
{

}

std::unique_ptr<ExprAST> WhileExpr::Execute(DataTable& Table)
{
  std::unique_ptr<ExprAST> LastExpr;
  while (((NumberExpr*)(m_Condition->Execute(Table).get()))->GetValue())
    LastExpr = std::move(m_CodeBlock->Execute(Table));
  return LastExpr;
}
