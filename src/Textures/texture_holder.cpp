#include "texture_holder.hpp"

TextureHolder::TextureHolder() {
    // do nothing
}

TextureHolder::~TextureHolder() {
    // do nothing
}

// insert a texture in the map object
void TextureHolder::load(Textures::ID id, const std::string& filename) {
    std::unique_ptr<sf::Texture> texture(new sf::Texture());

    if(!texture->loadFromFile(filename)) {
        throw std::runtime_error("TextureHolder::load - Failed to load " + filename);
    }

    // std::pair<std::map<Textures::ID, std::unique_ptr<sf::Texture>>::iterator, bool> inserted =
    // mTextureMap.insert(std::make_pair(id, std::move(texture)));
    auto inserted = mTextureMap.insert(std::make_pair(id, std::move(texture)));
    assert(inserted.second);
}

// given the id return the associated texture
sf::Texture& TextureHolder::get(Textures::ID id) {
    auto found = mTextureMap.find(id);
    assert(found != mTextureMap.end());
    return *found->second;      // return the texture found in the map
}
