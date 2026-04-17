#ifdef __unix__
#include "Controls.h"
#include <cstdio>    // getchar, EOF
#include <fcntl.h>   // fcntl
#include <termios.h> // termios, tcgetattr
#include <unistd.h>  // tcsetattr flags

namespace {
static termios oldt{}; // old terminal settings
static termios newt{}; // new terminal settings
static int oldf{};     // old terminal flags
} // namespace

void Controls::Init() {
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
}

void Controls::Restore() {
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
}

char Controls::GetInput() {
  char c = getchar();
  if (c == EOF)
    return 0;
  return c;
}

#endif // __unix__
