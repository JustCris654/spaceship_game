#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

#include "../../Resources/ResourceIdentifiers.hpp"
#include "../StateIdentifiers.hpp"

class StateStack;
class Player;

class State {
  public:
    typedef std::unique_ptr<State> Ptr;
    struct Context {
        Context(
            sf::RenderWindow &window, TextureHolder &textures,
            FontHolder &fonts, Player &player);
        sf::RenderWindow *window;
        TextureHolder    *textures;
        FontHolder       *fonts;
        Player           *player;
    };

  public:
    State(StateStack &, Context);
    virtual ~State();

    virtual void draw() = 0;
    virtual bool update(sf::Time dt) = 0;
    virtual bool handleEvent(const sf::Event &event) = 0;

  protected:
    void requestStackPush(States::ID stateId);
    void requestStackPop();
    void requestStateClear();

    Context getContext() const;

  private:
    StateStack *m_Stack;
    Context     m_Context;
};