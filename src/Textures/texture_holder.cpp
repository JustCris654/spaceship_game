#include "texture_holder.hpp"

// insert a texture in the map object
void TextureHolder::load(Textures::ID id, const std::string& filename) {
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    texture->loadFromFile(filename);

    mTextureMap.insert(std::make_pair(id, std::move(texture)));
}

// given the id return the associated texture
sf::Texture& TextureHolder::get(Textures::ID id) {
    auto found = mTextureMap.find(id);
    return *found->second;      // return the texture found in the map
}