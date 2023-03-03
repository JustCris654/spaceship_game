#ifndef MENUSTATE_H_
#define MENUSTATE_H_

#include "../StateStack/StateStack.hpp"
#include <vector>

class MenuState : public State {

    enum OptionNames {
        Play,
        Exit,
    };

  public:
    MenuState(StateStack &, Context);
    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event &);

  private:
    void updateOptionsText();

  private:
    sf::Sprite            m_BackgroundSprite;
    std::vector<sf::Text> m_Options;
    std::size_t           m_OptionIndex;
};

#endif // MENUSTATE_H_
