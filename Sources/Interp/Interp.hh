#pragma once

#include "../Config.hh"
#include "Lexer/Lexer.hh"
#include "Parser/Parser.hh"
#include "DataTable.hh"

#include <iostream>
#include <fstream>

class Interp
{
  public:
    Interp() = default;
    ~Interp() = default;

    void Run();
    void Live();

  private:
    static const char* WELCOME;
    static const char* PROMPT;

    Parser    m_Parser;
    DataTable m_Table;
};