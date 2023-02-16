#include "TextureHolder.hpp"
#include <cassert>

void TextureHolder::load(Textures::ID id, const std::string &filename) {
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    if (!texture->loadFromFile(filename)) {
        throw std::runtime_error(
            "TextureHolder::load - Failed to load " + filename);
    }

    auto inserted = m_TextureMap.insert(std::make_pair(id, std::move(texture)));

    // if second parameter of inserted is false it means that the insertion
    // on the textureMap has gone wrong, possibly there was already the same id
    assert(inserted.second);
}

// find and return the texture given an id
sf::Texture &TextureHolder::get(Textures::ID id) {
    auto found = m_TextureMap.find(id);
    assert(found != m_TextureMap.end());

    return *found->second;
}