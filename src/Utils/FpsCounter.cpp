#include "FpsCounter.hpp"

FpsCounter::FpsCounter() : m_FpsCounterText(), m_Fonts() {
    m_Fonts.load(Fonts::FiraCode, "src/Media/Fonts/FiraCode-Regular.ttf");
    m_FpsCounterText.setFont(m_Fonts.get(Fonts::FiraCode));
    m_FpsCounterText.setCharacterSize(30);
    m_FpsCounterText.setPosition(0.f,0.f);
}

FpsCounter::FpsCounter(const std::string& text) : m_FpsCounterText(), m_Fonts() {
    m_Fonts.load(Fonts::FiraCode, "src/Media/Fonts/FiraCode-Regular.ttf");
    m_FpsCounterText.setFont(m_Fonts.get(Fonts::FiraCode));
    m_FpsCounterText.setCharacterSize(30);
    m_FpsCounterText.setString(text);
    m_FpsCounterText.setPosition(0.f,0.f);
}

FpsCounter::~FpsCounter() {
    // do nothing
}

void FpsCounter::setText(const std::string &text) {
    m_FpsCounterText.setString(text);
}

sf::Text FpsCounter::getFpsCounter() const {
    return m_FpsCounterText;
}
