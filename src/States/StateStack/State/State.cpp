#include "../StateStack.hpp"

State::Context::Context(
    sf::RenderWindow &window, TextureHolder &textures, FontHolder &fonts,
    Player &player)
    : window(&window), textures(&textures), fonts(&fonts), player(&player) {}

State::State(StateStack &stack, Context ctx)
    : m_Stack(&stack), m_Context(ctx) {}

State::~State() {}

void State::requestStackPush(States::ID stateID) {
    m_Stack->pushState(stateID);
}

void State::requestStackPop() {
    m_Stack->popState();
}

void State::requestStateClear() {
    m_Stack->clearStates();
}

State::Context State::getContext() const {
    return m_Context;
}