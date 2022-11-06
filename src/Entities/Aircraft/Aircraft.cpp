#include "Aircraft.hpp"

Textures::ID toTextureID(Aircraft::Type type) {
    switch (type) {
    case Aircraft::Eagle:
        return Textures::Eagle;
    case Aircraft::Raptor:
        return Textures::Raptor;
    }
    return Textures::Eagle;
}

Aircraft::Aircraft(Type type, TextureHolder &textures)
    : m_Type(type), m_Sprite(textures.get(toTextureID(type))) {
    sf::FloatRect bound = m_Sprite.getLocalBounds();
    m_Sprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
}

void Aircraft::drawCurrent(
    sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_Sprite, states);
}
