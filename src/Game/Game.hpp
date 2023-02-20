#ifndef GAME_H_
#define GAME_H_

#include "../Resources/resource_holder.hpp"
#include <SFML/Graphics.hpp>

#include "../Utils/FpsCounter.hpp"
#include "../World/World.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/System/NonCopyable.hpp"

class Game : private sf::NonCopyable {
  public:
    Game();
    void run();

  private:
    void processEvents();
    void update(sf::Time);
    void render();

    void updateStatistics(sf::Time);
    void handlePlayerInput(sf::Keyboard::Key, bool);

  private:
    sf::RenderWindow mWindow;
    World            m_World;
    // FpsCounter       m_FpsCounter; // move this on the world class

    // ResourceHolder<sf::Texture, Textures::ID> textures;

    FpsCounter m_FpsCounter;
    sf::Time   m_StatisticsUpdateTime;
    size_t     m_StatisticsNumberFrames;

    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingRight;
    bool mIsMovingLeft;

    // const float    PlayerSpeed{600.f};
    const sf::Time TimePerFrame{sf::seconds(1.f / 60.f)};
};

#endif // GAME_H_
