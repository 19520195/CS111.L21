#include "Interp/Interp.hh"

int main(const int argc, const char** argv)
{
  Interp Itp;
  if (argc > 1)
  {
    freopen(argv[1], "r", stdin);
    Itp.Run();
  }
  else
  {
    Itp.Live();
  }

  return EXIT_SUCCESS;
}
