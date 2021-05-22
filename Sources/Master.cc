#include "Interp/Interp.hh"
#include "Utilities/FlagControler.hh"

int main(const int argc, const char** argv)
{
  Interp Itp;
  FlagControler F(argc, argv);

  std::cout << F.GetFlag("File") << std::endl;
  if (!F.GetFlag("File").length()) Itp.Live();
  else
  {
    freopen(F.GetFlag("File").c_str(), "r", stdin);
    Itp.Run();
  }

  return EXIT_SUCCESS;
}
