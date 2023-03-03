#ifndef PAUSESTATE_H_
#define PAUSESTATE_H_

#include "../StateStack/StateStack.hpp"
#include <vector>

class PauseState : public State {

    enum OptionNames {
        Play,
        Exit,
    };

  public:
    PauseState(StateStack &, Context);
    virtual void draw();
    virtual bool update(sf::Time);
    virtual bool handleEvent(const sf::Event &);

  private:
    void updateOptionsText();

  private:
    sf::Sprite m_BackgroundSprite;
    sf::Text   m_PauseText;
    sf::Text   m_InstructionText;
};

#endif // PAUSESTATE_H_
