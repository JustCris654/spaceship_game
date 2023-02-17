#include "Aircraft.hpp"

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
    }   

void Aircraft::drawCurrent(
    sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_Sprite, states);
}
