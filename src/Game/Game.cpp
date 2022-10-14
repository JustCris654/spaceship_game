#include "Game.hpp"

#include <iostream>

Game::Game()
    : mWindow(sf::VideoMode(1280, 960), "Spaceship game"),
      mTexture(),
      mPlayer(),
      mLandScape(),
      textures(),
      mIsMovingUp{false},
      mIsMovingDown{false},
      mIsMovingRight{false},
      mIsMovingLeft{false} {

    textures.load(Textures::Airplane, "src/Media/Textures/Eagle.png");
    textures.load(Textures::Missile, "src/Media/Textures/Missile.png");
    textures.load(Textures::Landscape, "src/Media/Textures/Desert.png");

    // set player texture
    mPlayer.setTexture(textures.get(Textures::Airplane));
    mPlayer.setPosition(100.f, 100.f);

    // set landscape texture
    mLandScape.setTexture(textures.get(Textures::Landscape));
    mLandScape.setPosition(0.f, 0.f);
    mLandScape.setScale(1.3, 1.3);
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        processEvents();

        // this while loop ensure that every frame has the same lenght
        // which is, in this case, 1/60 of a second (60fps)
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame) {
            std::cout << "FPS: " << 1 / timeSinceLastUpdate.asSeconds()
                      << std::endl;
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
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
    } else if (isPressed == false &&
               key ==
                   sf::Keyboard::Escape) {  // pressing ESC will close the game
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

void Game::update(sf::Time dt) {
    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp) {
        movement.y -= PlayerSpeed;
    } else if (mIsMovingDown) {
        movement.y += PlayerSpeed;
    } else if (mIsMovingLeft) {
        movement.x -= PlayerSpeed;
    } else if (mIsMovingRight) {
        movement.x += PlayerSpeed;
    }
    mPlayer.move(movement * dt.asSeconds());
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mLandScape);
    mWindow.draw(mPlayer);
    mWindow.display();
}
