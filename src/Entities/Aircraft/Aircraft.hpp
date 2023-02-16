#ifndef AIRCRAFT_H_
#define AIRCRAFT_H_

#import "../../Resources/ResourceIdentifiers.hpp"
#include "../BaseEntity.hpp"

class Aircraft : public BaseEntity {
  public:
    explicit Aircraft(Textures::ID type, const TextureHolder &textures);
    virtual void
    drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

  private:
    Textures::ID m_Type;
    sf::Sprite   m_Sprite;
};

#endif // AIRCRAFT_H_
