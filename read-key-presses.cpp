// https://chatgpt.com/share/687fddd7-a6e0-8013-83d9-ce0a6c35d1fa


#include <iostream>
#include <unistd.h>
#include <termios.h>

using namespace std;

// Save original terminal settings
struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);            // get current terminal settings
    atexit(disableRawMode);                            // restore settings at exit

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);                   // turn off echo and canonical mode
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);          // set new mode
}

int main() {
    enableRawMode();

    cout << "Press keys (press 'q' to quit):\n";

    char c;
    while (true) {
        ssize_t n = read(STDIN_FILENO, &c, 1);
        if (n == 1) {
            if (c == 'q') break;

            cout << "You pressed: '" << c << "' (ASCII " << static_cast<int>(c) << ")\n";
        }
    }

    return 0;
}
