#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML/Graphics.hpp>

#include "../SceneNode/SceneNode.hpp"
#include "SFML/System/Vector2.hpp"

class BaseEntity : public SceneNode {
  public:
    void         setVelocity(sf::Vector2f velocity);
    void         setVelocity(float vx, float vy);
    sf::Vector2f getVelocity() const;
    void         accellerate(sf::Vector2f);
    void         accellerate(float, float);

  private:
    sf::Vector2f m_Velocity;
    virtual void updateCurrent(sf::Time dt);
};

#endif // ENTITY_H_
