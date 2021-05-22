#pragma once

#include <map>
#include <string>

class FlagControler
{
  public:
    FlagControler(const int ArgCounter, const char** ArgValues);
    std::string GetFlag(const std::string& Key);
    std::string SetFlag(const std::string& Key, const std::string& Value);

  private:
    std::map<std::string, std::string> m_Map;
};
