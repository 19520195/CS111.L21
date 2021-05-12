#include "BuiltinExpr.hh"

BuiltinExpr::BuiltinExpr(const Token& T, const std::string& I, std::unique_ptr<ExprAST> E)
  : m_Token(T), m_Identifier(I), m_Expression(std::move(E))
{
  // BuiltinExpr::BuiltinExpr
}

std::unique_ptr<ExprAST> BuiltinExpr::Execute(DataTable& Table)
{
  switch (m_Token)
  {
    case Token::INCR:
      Table[m_Identifier] += 1;
      break;

    case Token::DECR:
      if (Table[m_Identifier] != 0)
        Table[m_Identifier] -= 1;
      break;

    case Token::CLEAR:
      Table[m_Identifier] = 0;
      break;

    case Token::INVERT:
      Table[m_Identifier] = !Table[m_Identifier];
      break;

    case Token::ASSIGN:
      Table[m_Identifier] = ((NumberExpr*)(m_Expression->Execute(Table).get()))->GetValue();
      break;

    case Token::IMPORT:
      std::cout << m_Identifier << " = ";
      std::cin >> Table[m_Identifier];
      break;

    case Token::EXPORT:
      if (m_Identifier.length()) std::cout << m_Identifier << " = " << Table[m_Identifier] << std::endl;
      else
        for (auto Variable : Table)
          std::cout << Variable.first << " = " << Variable.second << std::endl;
      return std::make_unique<NumberExpr>(0);
  }

  return std::make_unique<NumberExpr>(Table[m_Identifier]);;
}
