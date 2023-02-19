#include "Game/Game.hpp"
#include <exception>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    try {
        Game game;
        game.run();
    } catch (std::exception &e) {
        std::cout << "\nEXCEPTION" << e.what() << std::endl;
    }

    return 0;
}
