#pragma once

#include <map>
#include <string>
#include <vector>
#include <regex>
#include <sstream>

class FlagController
{
  public:
    FlagController() = default;
    // ~FlagController() = default;

    bool ExistInput() const;
    bool ExistOutput() const;

    std::string GetInput() const;
    std::string GetOutput() const;
    std::map<std::string, unsigned int> GetDataTable() const;

    void Parse(const int ArgumentCounter, const char** ArgumentValues);

  private:
    static const std::regex REGEX_VARIABLE;
    static const std::regex REGEX_FILENAME_INPUT;
    static const std::regex REGEX_FILENAME_OUTPUT;

    std::string                         m_InputFilename;
    std::string                         m_OutputFilename;
    std::map<std::string, unsigned int> m_VariableTable;
};
