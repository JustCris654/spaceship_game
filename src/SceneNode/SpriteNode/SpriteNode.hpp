#ifndef SCENENODE_SPRITENODE_H_
#define SCENENODE_SPRITENODE_H_

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../SceneNode.hpp"

class SpriteNode : public SceneNode {
  public:
    explicit SpriteNode(const sf::Texture &texture);
    SpriteNode(const sf::Texture &texture, const sf::IntRect &rect);

  private:
    virtual void
    drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

  private:
    sf::Sprite m_Sprite;
};

#endif // SCENENODE_SPRITENODE_H_