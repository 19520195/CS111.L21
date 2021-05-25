#include "Interp/Interp.hh"
#include "Utilities/FlagController.hh"

int main(const int ArgumentCounter, const char** ArgumentValue)
{
  // Flag parsing
  try { Flags.ParseFlag(ArgumentCounter, ArgumentValue); }
  catch(const std::exception& Exception)
  {
    std::cout << Exception.what() << std::endl;
    return EXIT_FAILURE;
  }

  // Helping flag
  if (Flags.ExistFlag("help"))
    return std::cout << Flags.Help() << std::endl, EXIT_SUCCESS;

  DataTable Table;
  std::cout << Flags.GetFlag("set");

  // Create interpreter
  Interp Interpreter;
  if (!Flags.GetFlag("file").length()) Interpreter.Live();
  else
  {
    freopen(Flags.GetFlag("file").c_str(), "r", stdin);
    Interpreter.Run();
  }

  return EXIT_SUCCESS;
}
