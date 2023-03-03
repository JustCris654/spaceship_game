#ifndef TITLESTATE_H_
#define TITLESTATE_H_

#include "../StateStack/StateStack.hpp"

class TitleState: public State {
  public:
    TitleState(StateStack &, Context);
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event &);

  private:
    sf::Sprite m_BackgroundSprite;
    sf::Text   m_Text;

    bool     m_ShowText;
    sf::Time m_TextEffectTime;
};

#endif // TITLESTATE_H_
