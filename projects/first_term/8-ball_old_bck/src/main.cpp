#include <iostream>

#include "game/Game.hh"

int main() {
    try {
        Game().run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}