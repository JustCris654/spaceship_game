#ifndef RESOURCES_RESOURCEIDENTIFIER_HPP
#define RESOURCES_RESOURCEIDENTIFIER_HPP

namespace Textures {
enum ID { Landscape, Airplane, Missile, Eagle, Raptor };
} // namespace Textures

namespace  sf {
class Texture;
} // Forward declaration of SFML texture class

// copy template declaration of resource holder to define TextureHolder type
template<typename Resource, typename Identifier>
class ResourceHolder;
typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif // RESOURCES_RESOURCEIDENTIFIER_HPP
