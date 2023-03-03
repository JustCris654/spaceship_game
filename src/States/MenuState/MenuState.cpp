#include "MenuState.hpp"

#include "../../Utils/Utility.hpp"

MenuState::MenuState(StateStack &stateStack, Context ctx)
    : State(stateStack, ctx), m_Options(), m_OptionIndex(0) {

    auto &texture = ctx.textures->get(Textures::TitleScreen);
    auto &font = ctx.fonts->get(Fonts::FiraCode);

    m_BackgroundSprite.setTexture(texture);

    // play option
    sf::Text playOption;
    playOption.setFont(font);
    playOption.setString("Play");
    centerOrigin(playOption);
    playOption.setPosition(ctx.window->getView().getSize() / 2.f);
    m_Options.push_back(playOption);

    // exito option
    sf::Text exitOption;
    playOption.setFont(font);
    playOption.setString("Exit");
    centerOrigin(exitOption);
    playOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
    m_Options.push_back(exitOption);

    updateOptionsText();
}

void MenuState::updateOptionsText() {
    if (m_Options.empty())
        return;

    // apply color white to all options
    for (auto &text : m_Options) {
        text.setFillColor(sf::Color::White);
        text.setOutlineColor(sf::Color::White);
    }

    // apply red to selected option
    m_Options[m_OptionIndex].setFillColor(sf::Color::Red);
    m_Options[m_OptionIndex].setOutlineColor(sf::Color::Red);
}

bool MenuState::handleEvent(const sf::Event &event) {

    if (event.type != sf::Event::KeyPressed)
        return false;

    if (event.key.code == sf::Keyboard::Up) {
        if (m_OptionIndex > 0)
            m_OptionIndex--;
        else
            m_OptionIndex = m_Options.size() - 1;

        updateOptionsText();
    } else if (event.key.code == sf::Keyboard::Down) {
        if (m_OptionIndex < m_Options.size() - 1)
            m_OptionIndex++;
        else
            m_OptionIndex = 0;

        updateOptionsText();
    }

    if (event.key.code == sf::Keyboard::Enter) {
        if (m_OptionIndex == Play) {
            requestStackPop();
            requestStackPush(States::Game);
        } else if (m_OptionIndex == Exit) {
            requestStackPop();
        }
    }

    return true;
}

void MenuState::draw() {
    sf::RenderWindow &window = *getContext().window;

    window.setView(window.getDefaultView());
    window.draw(m_BackgroundSprite);

    for (const auto &text : m_Options)
        window.draw(text);
}

bool MenuState::update(sf::Time dt) {
    return true;
}
