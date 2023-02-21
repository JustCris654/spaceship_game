#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#include "../../Utils/Resources/resource_holder.hpp"
#include "../BaseEntity.hpp"

class Aircraft : public BaseEntity {
  public:
    enum Type { Eagle, Raptor };

  public:
    explicit Aircraft(Type type, TextureHolder &textures);
    virtual void
    drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual unsigned int getCategory() const;

  private:
    Type       m_Type;
    sf::Sprite m_Sprite;
};

#endif // AIRCRAFT_H_
