#include "Aircraft.hpp"

Aircraft::Aircraft(Type type, const TextureHolder &textures) : m_Type(type) {}

void Aircraft::drawCurrent(
    sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_Sprite, states);
}
