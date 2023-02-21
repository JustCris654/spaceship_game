#ifndef PLAYER_H_
#define PLAYER_H_

#include "SFML/Window/Event.hpp"

class CommandQueue;

class Player {
  public:
    Player();
    ~Player();
    void handleEvent(const sf::Event &event, CommandQueue &commands);
    void handleRealTimeInput(CommandQueue &commands);

  private:
    float m_PlayerSpeed{.5f};
};

#endif // PLAYER_H_