#include "Compiler.hh"

const std::string Compiler::FileHeader = "#include <iostream>";
const std::string Compiler::LinkerExtension = ".cc";

Compiler::Compiler(std::unique_ptr<Parser> Parser) :
  m_Parser(std::move(Parser)),
  m_MainBlock(new BlockExpr())
{
}

std::string Compiler::GenerateCode()
{
  while (true)
  {
    try
    {
      std::unique_ptr<ExprAST> Expression;
      if (!(Expression = m_Parser->ParseNextToken()))
        break;
      m_MainBlock->InsertExpr(std::move(Expression));
    }
    catch (const std::exception& Ex)
    {
      std::cerr << Ex.what() << std::endl;
      return Ex.what();
    }
  }

  m_MainBlock->LookupVaribale(m_Variable);
  std::string DeclareVaribale = "unsigned int ";
  for (const auto& Name: m_Variable)
    DeclareVaribale += Name + ",";
  DeclareVaribale += "_;\n";

  const std::string MainCode = m_MainBlock->GenerateCode();
  return DeclareVaribale + "int main(){" + MainCode + "}";
}

void Compiler::Compile(const std::string& Output)
{
  const std::string& LinkerFilename = Output + LinkerExtension;
  std::ofstream LinkerFile(LinkerFilename);

  LinkerFile << FileHeader << std::endl;
  LinkerFile << GenerateCode() << std::endl;
  LinkerFile.close();

  if (system(("g++ " + LinkerFilename + " -o " + Output).c_str()) != EXIT_SUCCESS)
    throw std::logic_error("unexpected error when run g++");
}
