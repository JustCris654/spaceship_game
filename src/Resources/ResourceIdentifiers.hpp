#ifndef RESOURCES_RESOURCEIDENTIFIER_HPP
#define RESOURCES_RESOURCEIDENTIFIER_HPP

// Forward declaration of SFML classes
namespace sf {
class Texture;
}

namespace Textures {
enum ID {
    Eagle,
    Raptor,
    Desert,
    Missile,
};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier> class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif // RESOURCES_RESOURCEIDENTIFIER_HPP
