#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML/Graphics.hpp>

#include "../SceneNode/SceneNode.hpp"

class BaseEntity : public SceneNode {
  public:
    void         setVelocity(sf::Vector2f velocity);
    void         setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;

  private:
    sf::Vector2f m_Velocity;
};

#endif // ENTITY_H_
