#include "Interp.hh"

const char* Interp::WELCOME = "Welcome Barebone Interpreter version " BAREBONE_VERSION;
const char* Interp::PROMPT  = ">>> ";

void Interp::Run()
{
  try
  {
    while (true)
    {
      std::unique_ptr<ExprAST> Expression;
      Expression = m_Parser.ParseNextToken();
      if (Expression == nullptr)
        throw std::logic_error("Invalid expression");
      Expression->Execute(m_Table);
    }
  }
  catch (const std::exception& Ex)
  {
    std::cerr << Ex.what() << std::endl;
    m_Parser.Ignore();
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
      {
        unsigned int ReturnValue = ((NumberExpr*)(Expression->Execute(m_Table)).get())->GetValue();
        std::cout << "Return: " << ReturnValue << std::endl;
      }
    }
    catch (const std::exception& Ex)
    {
      std::cerr << Ex.what() << std::endl;
      m_Parser.Ignore();
    }
  }
}
