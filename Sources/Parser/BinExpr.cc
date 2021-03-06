#include "BinExpr.hh"

BinExpr::BinExpr(const Token& Oper, std::unique_ptr<ExprAST> Left, std::unique_ptr<ExprAST> Right)
  : m_Oper(Oper), m_Left(std::move(Left)), m_Right(std::move(Right))
{

}

unsigned int BinExpr::GetLeftValue(DataTable& Table)
{
  return ((NumberExpr*)(m_Left->Execute(Table).get()))->GetValue();
}

unsigned int BinExpr::GetRightValue(DataTable& Table)
{
  return ((NumberExpr*)(m_Right->Execute(Table).get()))->GetValue();
}

std::string BinExpr::GenerateCode() const
{
  return
  "(" +
    m_Left->GenerateCode()  +
    Token::ToString(m_Oper) +
    m_Right->GenerateCode() +
  ")";
}

std::unique_ptr<ExprAST> BinExpr::Execute(DataTable& Table)
{
  switch (m_Oper)
  {
    // Compare operators
    case Token::NOT_EQUAL            : return std::make_unique<NumberExpr>(GetLeftValue(Table) != GetRightValue(Table));
    case Token::EQUAL                : return std::make_unique<NumberExpr>(GetLeftValue(Table) == GetRightValue(Table));
    case Token::LESS_THAN            : return std::make_unique<NumberExpr>(GetLeftValue(Table) <  GetRightValue(Table));
    case Token::LESS_THAN_OR_EQUAL   : return std::make_unique<NumberExpr>(GetLeftValue(Table) <= GetRightValue(Table));
    case Token::GREATER_THAN         : return std::make_unique<NumberExpr>(GetLeftValue(Table) >  GetRightValue(Table));
    case Token::GREATER_THAN_OR_EQUAL: return std::make_unique<NumberExpr>(GetLeftValue(Table) >= GetRightValue(Table));

    // Math operators
    case Token::PLUS    : return std::make_unique<NumberExpr>(GetLeftValue(Table) + GetRightValue(Table));
    case Token::MINUS   : return std::make_unique<NumberExpr>(GetLeftValue(Table) - GetRightValue(Table));
    case Token::MULTIPLY: return std::make_unique<NumberExpr>(GetLeftValue(Table) * GetRightValue(Table));
    case Token::DIVIDE  : return std::make_unique<NumberExpr>(GetLeftValue(Table) / GetRightValue(Table));

    default:
      return nullptr;
  }
}

void BinExpr::LookupVaribale(std::set<std::string>& Set) const
{
  m_Left->LookupVaribale(Set);
  m_Right->LookupVaribale(Set);
}