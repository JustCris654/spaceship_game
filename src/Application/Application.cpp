#include "Application.hpp"

const float WINDOW_SIZE_X = 1920;
const float WINDOW_SIZE_Y = 1440;

Application::Application()
    : m_Window(
          sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Spaceship game",
          sf::Style::Close),
      m_Textures(), m_Fonts(),
      m_StateStack(State::Context(m_Window, m_Textures, m_Fonts, m_Player)),
      m_Player() {
    m_Window.setKeyRepeatEnabled(false);

    m_Fonts.load(Fonts::FiraCode, "src/Media/Fonts/FiraCode-Regular.ttf");

    m_StateStack.pushState(States::Title);
}

void Application::registerStates() {
    m_StateStack.registerState<TitleState>(States::Title);
    m_StateStack.registerState<MenuState>(States::Menu);
    m_StateStack.registerState<LoadingState>(States::Loading);
    m_StateStack.registerState<GameState>(States::Game);
    m_StateStack.registerState<PauseState>(States::Pause);
}

void Application::processInput() {
    sf::Event event;

    while (m_Window.pollEvent(event)) {
        m_StateStack.handleEvent(event);

        if (event.type == sf::Event::Closed) {
            m_Window.close();
        }
    }
}

void Application::update(sf::Time dt) {
    m_StateStack.update(dt);
}

void Application::render() {
    m_Window.clear();
    m_StateStack.draw();
    m_Window.setView(m_Window.getDefaultView());
    m_Window.display();
}

void Application::run() {
    sf::Clock clock;
    sf::Time  timeSinceLastUpdate = sf::Time::Zero;

    while (m_Window.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);

            if (m_StateStack.isEmpty()) {
                m_Window.close();
            }
        }

        render();
    }
}
