#include "SpriteNode.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

SpriteNode::SpriteNode(const sf::Texture &texture) : m_Sprite(texture) {}

SpriteNode::SpriteNode(const sf::Texture &texture, const sf::IntRect &rect)
    : m_Sprite(texture, rect) {}

void SpriteNode::drawCurrent(
    sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_Sprite, states);
}