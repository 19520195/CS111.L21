#pragma once

#include "../Config.hh"
#include "Lexer/Lexer.hh"
#include "Parser/Parser.hh"
#include "DataTable.hh"

#include <iostream>
#include <fstream>

class Interpreter
{
  public:
    Interpreter() = default;
    ~Interpreter() = default;

    Interpreter(const DataTable& Table);
    Interpreter(const std::string& Filename, const DataTable& Table);

    void SetInput(const std::string& Filename);
    void SetDataTable(const DataTable& Table);

    void Run();
    void Live();
    void Start();

  private:
    static const char* WELCOME;
    static const char* PROMPT;

    Parser      m_Parser;
    DataTable   m_Table;
    std::string m_Input;
};
