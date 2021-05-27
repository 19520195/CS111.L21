#include "Compiler/Compiler.hh"
#include "Interpreter/Interpreter.hh"
#include "Utilities/FlagController.hh"

int RunCompiler();

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

  // Compiler detection
  if (Flags.ExistFlag("input") && Flags.ExistFlag("output"))
    return RunCompiler();

  DataTable Table;

  // Create interpreter
  try
  {
    if (!Flags.GetFlag("file").length())
      Interpreter().Live();
    else
      Interpreter(Flags.GetFlag("file"), Table).Run();
  }
  catch(const std::exception& Exception)
  {
    std::cout << Exception.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int RunCompiler()
{
  try
  {
    const std::string& InputFilename = Flags.GetFlag("input");
    const std::string& OutputFilename = Flags.GetFlag("output");

    std::unique_ptr<Parser> RealParser(std::make_unique<Parser>(InputFilename));
    Compiler RealCompiler(std::move(RealParser));
    RealCompiler.Compile(OutputFilename);
  }
  catch (const std::exception& Exception)
  {
    std::cerr << "error: " << Exception.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
