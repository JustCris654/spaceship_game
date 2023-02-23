#include "Player.hpp"
#include "../Entities/Aircraft/Aircraft.hpp"
#include "../SceneNode/SceneNode.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <SFML/System/Vector2.hpp>

struct AircraftMover {
    AircraftMover(float vx, float vy) : velocity(vx, vy){};

    void operator()(Aircraft &aircraft, sf::Time) const {
        std::cout << "Accellerate -> X: " << velocity.x
                  << " - Y: " << velocity.y << std::endl;
        aircraft.accellerate(velocity);
    }

    sf::Vector2f velocity;
};

Player::Player() {
    m_KeyBinding[sf::Keyboard::W] = MoveUp;
    m_KeyBinding[sf::Keyboard::D] = MoveRight;
    m_KeyBinding[sf::Keyboard::S] = MoveDown;
    m_KeyBinding[sf::Keyboard::A] = MoveLeft;
    m_KeyBinding[sf::Keyboard::Space] = Shoot;

    initializeActions();

    for (auto &pair : m_ActionBinding)
        pair.second.category = Category::PlayerAircraft;
}

Player::~Player() {
    // do nothing
}

void Player::handleRealTimeInput(CommandQueue &commands) {
    for (auto pair : m_KeyBinding) {
        if (sf::Keyboard::isKeyPressed(pair.first) &&
            isRealTimeAction(pair.second))
            commands.push(m_ActionBinding[pair.second]);
    }
}

void Player::handleEvent(const sf::Event &event, CommandQueue &commands) {
    if (event.type == sf::Event::KeyPressed) {
        auto found = m_KeyBinding.find(event.key.code);
        if (found != m_KeyBinding.end() && !isRealTimeAction(found->second))
            commands.push(m_ActionBinding[found->second]);
    }
}

void Player::assignKey(sf::Keyboard::Key key, Action action) {

    // remove all keys mapped to the action
    for (auto itr = m_KeyBinding.begin(); itr != m_KeyBinding.end();) {
        if (itr->second == action)
            m_KeyBinding.erase(itr++);
        else
            itr++;
    }

    // add new key binding to action
    m_KeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) {
    for (auto pair : m_KeyBinding) {
        if (pair.second == action)
            return pair.first;
    }

    return sf::Keyboard::Unknown;
}

void Player::initializeActions() {
    m_ActionBinding[MoveUp].action =
        derivedAction<Aircraft>(AircraftMover(0.f, -m_PlayerSpeed));
    m_ActionBinding[MoveDown].action =
        derivedAction<Aircraft>(AircraftMover(0.f, +m_PlayerSpeed));
    m_ActionBinding[MoveLeft].action =
        derivedAction<Aircraft>(AircraftMover(-m_PlayerSpeed, 0.f));
    m_ActionBinding[MoveRight].action =
        derivedAction<Aircraft>(AircraftMover(+m_PlayerSpeed, 0.f));
    m_ActionBinding[Shoot].action =
        derivedAction<Aircraft>(AircraftMover(0.f, 0.f));
}

bool Player::isRealTimeAction(Action action) {
    switch (action) {
    case MoveUp:
    case MoveRight:
    case MoveDown:
    case MoveLeft:
        return true;
    default:
        return false;
    }
}