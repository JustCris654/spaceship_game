#include "TitleState.hpp"

bool TitleState::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
        requestStackPop();
        requestStackPush(States::Menu);
    }

    return true;
}

bool TitleState::update(sf::Time dt) {
    m_TextEffectTime += dt;

    if (m_TextEffectTime >= sf::seconds(0.5f)) {
        m_ShowText = !m_ShowText;
        m_TextEffectTime = sf::Time::Zero;
    }

    return true;
}
