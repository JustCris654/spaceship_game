#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "../StateStack/StateStack.hpp"
#include "../../World/World.hpp"

class GameState : public State {
  public:
    GameState(StateStack &, Context);
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event &);

  private:
    World   m_World;
    Player &m_Player;
};

#endif // GAMESTATE_H_
