#include "./textures.hpp"
#include <SFML/Graphics.hpp>
#include <map>

class TextureHolder {
  private:
    std::map<Textures::ID, std::unique_ptr<sf::Texture>> m_TextureMap;

  public:
    void               load(Textures::ID id, const std::string &filename);
    sf::Texture       &get(Textures::ID id);
    const sf::Texture &get(Textures::ID id) const;
};