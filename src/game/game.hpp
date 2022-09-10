#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>

class Game {
    public:
        Game();
        void run();

    private:
        void processEvents();
        void update();
        void render();

    private:
        sf::RenderWindow mWindow;
        sf::CircleShape  mPlayer;
        bool mIsMovingUp;
        bool mIsMovingDown;
        bool mIsMovingRight;
        bool mIsMovingLeft;
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
};

#endif // GAME_H_
