#ifndef TEXTURE_HOLDER_H_
#define TEXTURE_HOLDER_H_

#include <SFML/Graphics.hpp>
#include <map>
#include "textures.hpp"

class TextureHolder {
    public:
        TextureHolder();
        ~TextureHolder();

        void load(Textures::ID id, const std::string& filename);
        sf::Texture& get(Textures::ID id);
        const sf::Texture& get(Textures::ID id) const;

    private:
        std::map<Textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
};

#endif
