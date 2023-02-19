#ifndef SPRITENODE_H_
#define SPRITENODE_H_

#include "../SceneNode.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class SpriteNode : public SceneNode {
  public:
    explicit SpriteNode(const sf::Texture &texture);
    SpriteNode(const sf::Texture &texture, const sf::IntRect &textureRect);

  private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

  private:
    sf::Sprite m_Sprite;
};

#endif