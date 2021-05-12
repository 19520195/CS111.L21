#include "Interp.hh"

const char* Interp::WELCOME = "Welcome Barebone Interpreter v0.0.1";
const char* Interp::PROMPT  = ">>> ";

void Interp::Run()
{
  while (true)
  {
    try
    {
      std::unique_ptr<ExprAST> Expression;
      Expression = m_Parser.ParseNextToken();
      if (Expression == nullptr)
        throw std::logic_error("Invalid expression");
      Expression->Execute(m_Table);
    }
    catch (const std::exception& Ex)
    {
      std::cerr << Ex.what() << std::endl;
      m_Parser.IgnoreCharacter();
      break;
    }
  }
}

void Interp::Live()
{
  std::cout << WELCOME << std::endl;
  while (true)
  {
    (std::cout << PROMPT).flush();
    try
    {
      std::unique_ptr<ExprAST> Expression;
      Expression = m_Parser.ParseNextToken();
      if (Expression != nullptr)
        Expression->Execute(m_Table);
    }
    catch (const std::exception& Ex)
    {
      std::cerr << Ex.what() << std::endl;
      m_Parser.IgnoreCharacter();
    }
  }
}
