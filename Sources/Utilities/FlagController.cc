#include "FlagController.hh"

const std::regex FlagController::REGEX_VARIABLE = std::regex("^([A-Za-z][\\w]*)=([\\d]*)$");
const std::regex FlagController::REGEX_FILENAME_INPUT = std::regex("-i(.*\\.bb)");
const std::regex FlagController::REGEX_FILENAME_OUTPUT = std::regex("-o(.*\\.bb)");

bool FlagController::ExistInput() const
{
  return GetInput().length();
}

bool FlagController::ExistOutput() const
{
  return GetOutput().length();
}

std::string FlagController::GetInput() const
{
  return m_InputFilename;
}

std::string FlagController::GetOutput() const
{
  return m_OutputFilename;
}

std::map<std::string, unsigned int> FlagController::GetDataTable() const
{
  return m_VariableTable;
}

void FlagController::Parse(const int ArgumentCounter, const char** ArgumentValues)
{
  std::vector<std::string> ArgumentList(ArgumentValues + 1, ArgumentValues + ArgumentCounter);
  for (const auto& Arg: ArgumentList)
  {
    std::smatch Results;
    if (std::regex_search(Arg, Results, REGEX_VARIABLE))
    {
      auto VarName = Results.str(1);
      auto VarValue = std::stoul(Results.str(2));
      m_VariableTable[VarName] = VarValue;
    }
    else if (std::regex_search(Arg, Results, REGEX_FILENAME_INPUT))
    {
      auto Filename = Results.str(1);
      m_InputFilename = Filename;
    }
    else if (std::regex_search(Arg, Results, REGEX_FILENAME_OUTPUT))
    {
      auto Filename = Results.str(1);
      m_OutputFilename = Filename;
    }
    else
    {
      std::stringstream ErrorStream;
      ErrorStream << "Invalid flag " << '"' << Arg << '"';
      throw std::logic_error(ErrorStream.str());
    }
  }
}
