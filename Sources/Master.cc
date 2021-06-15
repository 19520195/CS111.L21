#include "Compiler/Compiler.hh"
#include "Interpreter/Interpreter.hh"
#include "Utilities/FlagController.hh"

int RunCompiler(const FlagController& Controller);
int RunInterpreter(const FlagController& Controller);

int main(const int ArgumentCounter, const char** ArgumentValue)
{
  FlagController Controller;
  try { Controller.Parse(ArgumentCounter, ArgumentValue); }
  catch (const std::exception& Exception)
  {
    std::cerr << Exception.what() << std::endl;
    return EXIT_FAILURE;
  }

  if (Controller.ExistInput() && Controller.ExistOutput())
    return RunCompiler(Controller);
  return RunInterpreter(Controller);
}

int RunCompiler(const FlagController& Controller)
{
  try
  {
    const std::string& InputFilename = Controller.GetInput();
    const std::string& OutputFilename = Controller.GetOutput();

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

int RunInterpreter(const FlagController& Controller)
{
  Interpreter Interp;
  if (Controller.ExistInput())
    Interp.SetInput(Controller.GetInput());
  Interp.SetDataTable(Controller.GetDataTable());

  // Create interpreter
  try { Interp.Start(); }
  catch(const std::exception& Exception)
  {
    std::cout << Exception.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
