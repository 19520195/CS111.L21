#include "BuiltinExpr.hh"

BuiltinExpr::BuiltinExpr(const Token& T, const std::string& I, std::unique_ptr<ExprAST> E)
  : m_Token(T), m_Identifier(I), m_Expression(std::move(E))
{
  // BuiltinExpr::BuiltinExpr
}

std::string BuiltinExpr::GenerateCode() const
{
  switch (m_Token)
  {
    case Token::INCR  : return "++" + m_Identifier;
    case Token::DECR  : return "--" + m_Identifier;
    case Token::CLEAR : return m_Identifier + "=0";
    case Token::INVERT: return m_Identifier + "=!" + m_Identifier;
    case Token::ASSIGN: return m_Identifier + "=" + m_Expression->GenerateCode();

    case Token::IMPORT: return "std::cout<<\"" + m_Identifier + " = \";std::cin>>" + m_Identifier;
    case Token::EXPORT: return "std::cout<<\"" + m_Identifier + " = \"<<" + m_Identifier + "<<std::endl";
    default:            return "__unknow_statement__";
  }
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
      if (!(m_Identifier == "all"))
      {
        std::cout << m_Identifier << " = ";
        std::cout << Table[m_Identifier] << std::endl;
      }
      else
      {
        for (auto Variable : Table)
        {
          std::cout << Variable.first << " = ";
          std::cout << Variable.second << std::endl;
        }
      }
      return std::make_unique<NumberExpr>(0);

    case Token::EXPORC:
      std::cout << (char)Table[m_Identifier] << std::endl;
      return std::make_unique<NumberExpr>(0);
  }

  return std::make_unique<NumberExpr>(Table[m_Identifier]);;
}

void BuiltinExpr::LookupVaribale(std::set<std::string>& Set) const
{
  Set.insert(m_Identifier);
}
