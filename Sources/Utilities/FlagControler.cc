#include "FlagControler.hh"

FlagControler::FlagControler(const int ArgCounter, const char** ArgValues)
{
  for (size_t i = 1; i < ArgCounter; i += 2)
  {
    std::string Argument(ArgValues[i]);
    if (*Argument.begin() != '-')
      throw std::logic_error("invalid flag");
    if (i + 1 < ArgCounter)
      m_Map[std::string(Argument.begin() + 1, Argument.end())] = std::string(ArgValues[i + 1]);
  }
}

std::string FlagControler::GetFlag(const std::string& Key)
{
  return m_Map[Key];
}

std::string FlagControler::SetFlag(const std::string& Key, const std::string& Value)
{
  return m_Map[Key] = Value;
}
