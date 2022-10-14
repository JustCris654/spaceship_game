#ifndef GAME_H_
#define GAME_H_

#include <SFML/Graphics.hpp>
#include "../Resources/resource_holder.hpp"

class Game {
   public:
    Game();
    void run();

   private:
    void processEvents();
    void update(sf::Time);
    void render();

    void handlePlayerInput(sf::Keyboard::Key, bool);

   private:
    sf::RenderWindow mWindow;
    sf::Texture mTexture;
    sf::Sprite mPlayer;
    sf::Sprite mLandScape;

    ResourceHolder<sf::Texture, Textures::ID> textures;

    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingRight;
    bool mIsMovingLeft;

    const float PlayerSpeed{600.f};
    const sf::Time TimePerFrame{sf::seconds(1.f / 60.f)};


};

#endif  // GAME_H_
