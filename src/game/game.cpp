#include "game.hpp"

#include <iostream>

Game::Game()
    : mWindow(sf::VideoMode(1280, 960), "SFML Application"),
      mPlayer(),
      mIsMovingUp{false},
      mIsMovingDown{false},
      mIsMovingRight{false},
      mIsMovingLeft{false} {
    mPlayer.setRadius(40.f);
    mPlayer.setPosition(100.f, 100.f);
    mPlayer.setFillColor(sf::Color::Cyan);
}

void Game::run() {
    while (mWindow.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W) {
        mIsMovingUp = isPressed;
    } else if (key == sf::Keyboard::D) {
        mIsMovingRight = isPressed;
    } else if (key == sf::Keyboard::S) {
        mIsMovingDown = isPressed;
    } else if (key == sf::Keyboard::A) {
        mIsMovingLeft = isPressed;
    } else if (isPressed == false && key == sf::Keyboard::Escape) {      // pressing ESC will close the game
        mWindow.close();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
     
            default:
                break;
        }
    }
}

void Game::update() {
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp) {
        movement.y -= .5f;
    } else if (mIsMovingDown) {
        movement.y += .5f;
    } else if (mIsMovingLeft) {
        movement.x -= .5f;
    } else if (mIsMovingRight) {
        movement.x += .5f;
    }

    mPlayer.move(movement);
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mPlayer);
    mWindow.display();
}