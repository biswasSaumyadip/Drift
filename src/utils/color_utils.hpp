#pragma once
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>

inline void enableANSIColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#else
inline void enableANSIColors() {} // no-op on non-Windows
#endif

enum class Color {
    RED,
    GREEN,
    YELLOW,
    CYAN,
    RESET
};

inline std::string color(Color c) {
    switch (c) {
        case Color::RED: return "\033[1;31m";
        case Color::GREEN: return "\033[1;32m";
        case Color::YELLOW: return "\033[1;33m";
        case Color::CYAN: return "\033[1;36m";
        case Color::RESET: return "\033[0m";
        default: return "\033[0m";
    }
}

inline void log(Color c, const std::string &message) {
    std::cout << color(c) << message << color(Color::RESET) << std::endl;
    std::cout << std::endl;
}


namespace LOG {
    inline void error(const std::string &message) {
        log(Color::RED, message);
    }

    inline void info(const std::string &message) {
        log(Color::CYAN, message);
    }

    inline void warning(const std::string &message) {
        log(Color::YELLOW, message);
    }

    inline void success(const std::string &message) {
        log(Color::GREEN, message);
    }
}
