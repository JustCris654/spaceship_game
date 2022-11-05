#include "Game.hpp"
#include <iostream>

const float WINDOW_SIZE_X = 1280;
const float WINDOW_SIZE_Y = 960;

Game::Game()
    : mWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Spaceship game"),
      mTexture(),
      mPlayer(),
      mLandScape(),
      m_FpsCounter(),
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
    mPlayer.setPosition(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2);

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
            double fps = 1 / timeSinceLastUpdate.asSeconds();
            m_FpsCounter.setText("FPS: " + std::to_string(fps));
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
    }
    if (mIsMovingDown) {
        movement.y += PlayerSpeed;
    }
    if (mIsMovingLeft) {
        movement.x -= PlayerSpeed;
    }
    if (mIsMovingRight) {
        movement.x += PlayerSpeed;
    }
    mPlayer.move(movement * dt.asSeconds());

    // get position relative to the center of the sprite
    float size_x = mPlayer.getTexture()->getSize().x;
    float size_y = mPlayer.getTexture()->getSize().y;

    float pos_x = mPlayer.getPosition().x + size_x / 2;
    float pos_y = mPlayer.getPosition().y + size_y / 2;

    // std::cout << "size_x: " << size_x << " - size_y: " << size_y << std::endl;
    // std::cout << "x: " << pos_x << " - y: " << pos_y << std::endl;
    // std::cout << "abs x: " << mPlayer.getPosition().x << " - abs y: " << mPlayer.getPosition().y << std::endl;

    if (pos_x <= 1) {
        mPlayer.setPosition(WINDOW_SIZE_X - size_x / 2 - 1, mPlayer.getPosition().y);
    } else if (pos_x >= WINDOW_SIZE_X) {
        mPlayer.setPosition(-size_x / 2 + 1, mPlayer.getPosition().y);
    }

    if (pos_y <= 32) {
        mPlayer.setPosition(mPlayer.getPosition().x, 0.01);
    } else if (pos_y >= WINDOW_SIZE_Y - size_y / 2) {
        mPlayer.setPosition(mPlayer.getPosition().x, WINDOW_SIZE_Y - size_y - 0.01);
    }

}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mLandScape);
    mWindow.draw(mPlayer);

    mWindow.draw(m_FpsCounter.getFpsCounter());
    mWindow.display();
}
