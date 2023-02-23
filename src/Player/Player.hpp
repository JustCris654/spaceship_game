#ifndef PLAYER_H_
#define PLAYER_H_

#include <map>

#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"

struct Command;

class CommandQueue;

class Player {

  public:
    enum Action {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
        Shoot,
        ActionCount,
    };

  public:
    Player();
    ~Player();
    void handleEvent(const sf::Event &event, CommandQueue &commands);
    void handleRealTimeInput(CommandQueue &commands);

    void              assignKey(sf::Keyboard::Key key, Action action);
    sf::Keyboard::Key getAssignedKey(Action action);

  private:
    void        initializeActions();
    static bool isRealTimeAction(Action);

  private:
    std::map<sf::Keyboard::Key, Action> m_KeyBinding;
    std::map<Action, Command>           m_ActionBinding;
    float                               m_PlayerSpeed{10.f};
};

#endif // PLAYER_H_