#include "FlagController.hh"

FlagController::FlagController(const std::map<std::string, std::string>& FlagDescriptions) : m_Description(FlagDescriptions)
{
}

#include <sstream>
#include <iomanip>

std::string FlagController::Help() const
{
  std::stringstream Stream;
  Stream << std::left;

  for (const auto& Description: m_Description)
  {
    Stream << "--" << std::setw(8)  << Description.first;
    Stream << ": " << Description.second << "\n";
  }

  return Stream.str();
}

bool FlagController::ExistFlag(const std::string& Flag) const
{
  const auto& Found = m_Value.find(Flag);
  return Found != m_Value.end();
}

std::string FlagController::GetFlag(const std::string& Flag) const
{
  const auto& Found = m_Value.find(Flag);
  if (Found != m_Value.end())
    return Found->second;
  return "";
}

std::string FlagController::SetFlag(const std::string& Flag, const std::string& Value)
{
  return m_Value[Flag] = Value;
}

void FlagController::ParseFlag(const int ArgumentCounter, const char** ArgumentValue)
{
  for (size_t i = 1; i < ArgumentCounter; i += 2)
  {
    std::string Argument(ArgumentValue[i]);
    if (Argument.length() < 2 || Argument.substr(0, 2) != "--")
      throw std::logic_error("invalid flag");

    std::string& ValueRef = m_Value[Argument.substr(2)];
    if (i + 1 < ArgumentCounter)
      ValueRef += (ValueRef.length() ? "; " : "") + std::string(ArgumentValue[i + 1]);
  }
}
