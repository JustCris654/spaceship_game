#ifndef RESOURCES_RESOURCEIDENTIFIER_HPP
#define RESOURCES_RESOURCEIDENTIFIER_HPP

// Forward declaration of SFML classes
namespace sf {
class Texture;
class Font;
} // namespace sf

namespace Textures {
enum ID {
    Eagle,
    Raptor,
    Desert,
    Missile,
    TitleScreen,
};
}

namespace Fonts {
enum ID {
    FiraCode,
};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier> class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>       FontHolder;

#endif // RESOURCES_RESOURCEIDENTIFIER_HPP
