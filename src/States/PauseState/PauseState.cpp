#include "PauseState.hpp"

#include "../../Utils/Utility.hpp"

PauseState::PauseState(StateStack &stack, Context ctx)
    : State(stack, ctx), m_BackgroundSprite(), m_PauseText(),
      m_InstructionText() {

    sf::Font    &font = ctx.fonts->get(Fonts::FiraCode);
    sf::Vector2f viewSize = ctx.window->getView().getSize();

    // paused text
    m_PauseText.setFont(font);
    m_PauseText.setString("Game paused");
    m_PauseText.setCharacterSize(70);
    centerOrigin(m_PauseText);
    m_PauseText.setPosition(viewSize / 2.f);

    // instruction text
    m_InstructionText.setFont(font);
    m_InstructionText.setString("Game paused");
    m_InstructionText.setCharacterSize(70);
    centerOrigin(m_InstructionText);
    m_PauseText.setPosition(viewSize / 2.f);
}

void PauseState::draw() {
    sf::RenderWindow &window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));

    window.draw(backgroundShape);
    window.draw(m_PauseText);
    window.draw(m_InstructionText);
}

bool PauseState::handleEvent(const sf::Event &event) {

    if (event.type != sf::Event::KeyPressed)
        return false;

    if (event.key.code == sf::Keyboard::BackSpace) {
        requestStateClear();
        requestStackPush(States::Menu);
    } else if (event.key.code == sf::Keyboard::Escape) {
        // return to the game
        requestStackPop();
    }

    return false;
}

bool PauseState::update(sf::Time dt) {
    return false;
}
