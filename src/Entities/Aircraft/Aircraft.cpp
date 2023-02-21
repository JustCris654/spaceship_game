#include "Aircraft.hpp"
#include "SFML/Graphics/Rect.hpp"

#include <SFML/Graphics.hpp>

Textures::ID toTextureId(Aircraft::Type type) {
    switch (type) {
    case Aircraft::Eagle:
        return Textures::Eagle;
    case Aircraft::Raptor:
        return Textures::Raptor;
    }

    // default return if no type is specified
    return Textures::Eagle;
}

Aircraft::Aircraft(Type type, TextureHolder &textures)
    : m_Type(type), m_Sprite(textures.get(toTextureId(type))) {

    sf::FloatRect bounds = m_Sprite.getLocalBounds();
    m_Sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::drawCurrent(
    sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_Sprite, states);
}

unsigned int Aircraft::getCategory() const {
    switch (m_Type) {
    case Aircraft::Eagle:
        return Category::PlayerAircraft;
    default:
        return Category::EnemyAircraft;
    }
}

void Aircraft::accellerate(sf::Vector2f v) {
    this->setVelocity(this->getVelocity() + v);
}