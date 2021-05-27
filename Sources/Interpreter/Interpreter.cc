#include "Interpreter.hh"

const char* Interpreter::WELCOME = "Welcome Barebone Interpreter version " BAREBONE_VERSION;
const char* Interpreter::PROMPT  = ">>> ";

Interpreter::Interpreter(const DataTable& Table) : m_Table(Table)
{
}

Interpreter::Interpreter(const std::string& Filename, const DataTable& Table) : m_Parser(Filename), m_Table(Table)
{
}

void Interpreter::Run()
{
  std::unique_ptr<ExprAST> Expression;
  try
  {
    while (true)
    {
      Expression = m_Parser.ParseNextToken();
      if (Expression == nullptr)
        break;
      Expression->Execute(m_Table);
    }
  }
  catch (const std::exception& Ex)
  {
    std::cerr << Ex.what() << std::endl;
    m_Parser.Ignore();
  }
}

void Interpreter::Live()
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
