#include "Game.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include <iostream>
#include <sstream>
#include <string>

const float WINDOW_SIZE_X = 1920;
const float WINDOW_SIZE_Y = 1440;

Game::Game()
    : mWindow(
          sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Spaceship game",
          sf::Style::Close),
      m_World(mWindow), m_FpsCounter("Initializing statistics..."),
      m_StatisticsNumberFrames(), m_Player() {}

void Game::run() {
    sf::Clock clock;
    sf::Time  timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()) {
        processEvents();

        // this while loop ensure that every frame has the same lenght
        // which is, in this case, 1/60 of a second (60fps)
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame) {
            updateStatistics(timeSinceLastUpdate);
            timeSinceLastUpdate -= TimePerFrame;

            processEvents();
            update(TimePerFrame);
        }

        render();
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W || key == sf::Keyboard::Up) {
        mIsMovingUp = isPressed;
    } else if (key == sf::Keyboard::D || key == sf::Keyboard::Right) {
        mIsMovingRight = isPressed;
    } else if (key == sf::Keyboard::S || key == sf::Keyboard::Down) {
        mIsMovingDown = isPressed;
    } else if (key == sf::Keyboard::A || key == sf::Keyboard::Left) {
        mIsMovingLeft = isPressed;
    } else if (isPressed == false && key == sf::Keyboard::Escape) {
        // pressing
        // ESC will
        // close the
        // game
        mWindow.close();
    }
}

void Game::processEvents() {
    CommandQueue &commands = m_World.getCommandQueue();

    sf::Event event;
    while (mWindow.pollEvent(event)) {
        m_Player.handleEvent(event, commands);

        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Escape) {
            mWindow.close();
        }
        if (event.type == sf::Event::Closed) {
            mWindow.close();
        }
    }

    m_Player.handleRealTimeInput(commands);
}

void Game::update(sf::Time dt) {
    m_World.update(dt);
}

void Game::render() {
    mWindow.clear();
    m_World.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(m_FpsCounter.getFpsCounter());
    mWindow.display();
}

void Game::updateStatistics(sf::Time dt) {
    m_StatisticsUpdateTime += dt;
    m_StatisticsNumberFrames += 1;

    if (m_StatisticsUpdateTime >= sf::seconds(1.f)) {
        m_FpsCounter.setText(
            "FPS: " + std::to_string(m_StatisticsNumberFrames) + "\n" +
            "Time / Update: " +
            std::to_string(
                m_StatisticsUpdateTime.asMicroseconds() /
                m_StatisticsNumberFrames) +
            "us");

        m_StatisticsUpdateTime -= sf::seconds(1.f);
        m_StatisticsNumberFrames = 0;
    }
}