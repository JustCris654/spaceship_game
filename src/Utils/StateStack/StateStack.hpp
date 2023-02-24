#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window.hpp>
#include <map>
#include <vector>

#include "State/State.hpp"
#include "StateIdentifiers.hpp"

class StateStack : private sf::NonCopyable {

  public:
    enum Action {
        Push,
        Pop,
        Clear,
    };

  public:
    explicit StateStack(State::Context context);
    template <typename T> void registerState(States::ID stateID);

    void update(sf::Time dt);
    void draw();
    void handleEvent(const sf::Event &event);

    void pushState(States::ID stateID);
    void popState();
    void clearStates();

    bool isEmpty() const;

  private:
    State::Ptr createState(States::ID stateID);
    void       applyPendingChanges();

  private:
    struct PendingChange {
        PendingChange(Action action, States::ID stateID = States::None) {
            this->action = action;
            this->stateID = stateID;
        }

        Action     action;
        States::ID stateID;
    };

  private:
    std::vector<State::Ptr>                           m_Stack;
    std::vector<PendingChange>                        m_PendingList;
    State::Context                                    m_Context;
    std::map<States::ID, std::function<State::Ptr()>> m_Factories;
};