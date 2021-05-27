#pragma once

#include "Parser/Parser.hh"
#include <unistd.h>

class Compiler
{
  public:
    Compiler(std::unique_ptr<Parser> Parser);

    std::string GenerateCode();
    void Compile(const std::string& Output);

  private:
    static const std::string FileHeader;
    static const std::string LinkerExtension;

    std::unique_ptr<Parser>    m_Parser;
    std::unique_ptr<BlockExpr> m_MainBlock;
    std::set<std::string>      m_Variable;
};
