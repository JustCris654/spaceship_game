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
        std::cout << "Cannot load texture" << std::endl;
        exit(1);
    }

    mTextureMap.insert(std::make_pair(id, std::move(texture)));
    std::cout << "Done!" << std::endl;
}

// given the id return the associated texture
sf::Texture& TextureHolder::get(Textures::ID id) {
    auto found = mTextureMap.find(id);
    std::cout << "Found texture" << found->first << std::endl;
    return *found->second;      // return the texture found in the map
}
