// https://chatgpt.com/share/687fddd7-a6e0-8013-83d9-ce0a6c35d1fa

#include "terminal-utils.h"
#include <thread>
#include <chrono>

int main() {
    using namespace Terminal;

    clearScreen();
    hideCursor();

    moveCursorTo(5, 10);
    setColor(GREEN);
    std::cout << "Hello, green world!";
    reset();

    moveCursorTo(7, 10);
    setColor(RED);
    setBackground(YELLOW);
    std::cout << "Red text on yellow background";
    reset();

    std::this_thread::sleep_for(std::chrono::seconds(3));
    showCursor();
    clearScreen();

    return 0;
}

