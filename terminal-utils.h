// https://chatgpt.com/share/687fddd7-a6e0-8013-83d9-ce0a6c35d1fa

#ifndef TERMINAL_UTILS_HPP
#define TERMINAL_UTILS_HPP

#include <iostream>

namespace Terminal {

    // ANSI escape code prefix
    const std::string ESC = "\033[";

    // Cursor movement
    void moveCursorUp(int n = 1)        { std::cout << ESC << n << "A"; }
    void moveCursorDown(int n = 1)      { std::cout << ESC << n << "B"; }
    void moveCursorRight(int n = 1)     { std::cout << ESC << n << "C"; }
    void moveCursorLeft(int n = 1)      { std::cout << ESC << n << "D"; }
    void moveCursorTo(int row, int col) { std::cout << ESC << row << ";" << col << "H"; }

    // Show/hide cursor
    void hideCursor() { std::cout << ESC << "?25l"; }
    void showCursor() { std::cout << ESC << "?25h"; }

    // Clear screen and lines
    void clearScreen() { std::cout << ESC << "2J" << ESC << "H"; }  // Clears and moves to top
    void clearLine()   { std::cout << ESC << "2K"; }

    // Reset formatting
    void reset()       { std::cout << ESC << "0m"; }

    // Text color (foreground)
    void setColor(int color) { std::cout << ESC << (30 + color) << "m"; }

    // Background color
    void setBackground(int color) { std::cout << ESC << (40 + color) << "m"; }

    enum Color {
        BLACK = 0,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
        DEFAULT = 9
    };
}

#endif // TERMINAL_UTILS_HPP
