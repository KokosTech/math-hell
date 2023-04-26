#include <iostream>

#include "game/Game.hpp"

int main() {
    try {
        Game().run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}