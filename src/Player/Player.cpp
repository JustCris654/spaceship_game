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
        aircraft.accellerate(velocity);
    }

    sf::Vector2f velocity;
};

struct AircraftBreak {
    void operator()(Aircraft &aircraft, sf::Time) const {
        aircraft.setVelocity(0.f, -200.f);
    }
};

Player::Player() {
    // do nothing
}

Player::~Player() {
    // do nothing
}

void Player::handleRealTimeInput(CommandQueue &commands) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        Command moveUp;
        moveUp.category = Category::PlayerAircraft;
        moveUp.action =
            derivedAction<Aircraft>(AircraftMover(0.f, -m_PlayerSpeed));

        commands.push(moveUp);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        Command moveDown;
        moveDown.category = Category::PlayerAircraft;
        moveDown.action =
            derivedAction<Aircraft>(AircraftMover(0.f, +m_PlayerSpeed));

        commands.push(moveDown);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        Command moveLeft;
        moveLeft.category = Category::PlayerAircraft;
        moveLeft.action =
            derivedAction<Aircraft>(AircraftMover(-m_PlayerSpeed, 0.f));

        commands.push(moveLeft);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        Command moveRight;
        moveRight.category = Category::PlayerAircraft;
        moveRight.action =
            derivedAction<Aircraft>(AircraftMover(+m_PlayerSpeed, 0.f));

        commands.push(moveRight);
    }
}

void Player::handleEvent(const sf::Event &event, CommandQueue &commands) {
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::P) {
        Command output;
        output.category = Category::PlayerAircraft;
        output.action = [](SceneNode &s, sf::Time) {
            std::cout << "X: " << s.getPosition().x
                      << " - Y: " << s.getPosition().y << std::endl;
        };

        commands.push(output);
    }
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Space) {
        Command breakPlayer;
        breakPlayer.category = Category::PlayerAircraft;
        breakPlayer.action =
            derivedAction<Aircraft>([](Aircraft &aircraft, sf::Time) {
                aircraft.setVelocity(0.f, -200.f);
            });

        commands.push(breakPlayer);
    }
}