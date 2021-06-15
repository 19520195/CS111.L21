#pragma once

#include <map>
#include <string>
#include <vector>

class FlagController
{
  public:
    FlagController() = default;
    FlagController(const std::map<std::string, std::string>& FlagDescriptions);

    std::string Help() const;
    bool ExistFlag(const std::string& Flag) const;

    std::string GetFlag(const std::string& Flag) const;
    std::string SetFlag(const std::string& Flag, const std::string& Value);

    std::string AddDescription(const std::string& Flag, const std::string Description);
    void ParseFlag(const int ArgumentCounter, const char** ArgumentValue);

  private:
    std::map<std::string, std::string> m_Value;
    std::map<std::string, std::string> m_Description;
};

static FlagController Flags({
  {"file"  , "Input file path\n\tEg: '... --file ../11_Example.bb'" },
  {"input" , "Input file path\n\tEg: '... --input ../11_Example.bb'" },
  {"output", "Output file path\n\tEg: '... --output ../11_Example.bb'"},
  {"set"   , "Set value for a varibale.\n\tEg: '... --set T=11', '... --set \"N=7; T=11\"'"},
});
