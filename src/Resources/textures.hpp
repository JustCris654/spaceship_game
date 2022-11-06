#ifndef TEXTURES_H_
#define TEXTURES_H_

#include "ResourceHolder.hpp"

namespace sf {
class Texture;
} // namespace sf

namespace Textures {
enum ID { Landscape, Eagle, Missile, Raptor };
} // namespace Textures

template <typename Resource, typename Identifier> class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif
