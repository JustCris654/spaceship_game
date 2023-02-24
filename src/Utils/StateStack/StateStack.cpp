#include "StateStack.hpp"
#include <cassert>

StateStack::StateStack(State::Context context)
    : m_Stack(), m_PendingList(), m_Context(context), m_Factories() {}

template <typename T> void StateStack::registerState(States::ID stateID) {
    m_Factories[stateID] = [this]() {
        return State::Ptr(new T(*this, m_Context));
    };
}

State::Ptr StateStack::createState(States::ID stateID) {
    auto found = m_Factories.find(stateID);
    assert(found != m_Factories.end());

    return found->second();
}

void StateStack::handleEvent(const sf::Event &event) {
    // iterate through states and handle their event bottom to top until one
    // returns false
    for (auto itr = m_Stack.begin(); itr != m_Stack.end(); ++itr) {
        if (!(*itr)->handleEvent(event)) {
            return;
        }
    }

    applyPendingChanges();
}

void StateStack::update(sf::Time dt) {
    // iterate through states and update them bottom to top until one returns
    // false
    for (auto itr = m_Stack.begin(); itr != m_Stack.end(); ++itr) {
        if (!(*itr)->update(dt)) {
            return;
        }
    }

    applyPendingChanges();
}

void StateStack::draw() {
    // draw all active states from bottom to top
    for (auto &el : m_Stack) {
        el->draw();
    }
}

void StateStack::applyPendingChanges() {
    for (auto change : m_PendingList) {
        switch (change.action) {
        case Push:
            m_Stack.push_back(createState(change.stateID));
            break;
        case Pop:
            m_Stack.pop_back();
            break;
        case Clear:
            m_Stack.clear();
            break;
        }
    }

    m_PendingList.clear();
}

void StateStack::pushState(States::ID stateID) {
    m_PendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState() {
    m_PendingList.pop_back();
}

void StateStack::clearStates() {
    m_PendingList.clear();
}

bool StateStack::isEmpty() const {
    return m_Stack.empty();
}