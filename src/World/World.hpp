#ifndef WORLD_H_
#define WORLD_H_

#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <array>

#include "../Entities/Aircraft/Aircraft.hpp"
#include "../Resources/ResourceIdentifiers.hpp"
#include "../SceneNode/SceneNode.hpp"
#include "../SceneNode/SpriteNode/SpriteNode.hpp"

class World : private sf::NonCopyable {

  public:
    explicit World(sf::RenderWindow &window);
    void update(sf::Time dt);
    void draw();

  private:
    void loadTextures();
    void buildScene();

  private:
    enum Layer {
        Background,
        Air,
        LayerCount,
    };

  private:
    sf::RenderWindow                   &m_Window;
    sf::View                            m_WorldView;
    TextureHolder                       m_Textures;
    SceneNode                           m_SceneGraph;
    std::array<SceneNode *, LayerCount> m_SceneLayers;

    sf::FloatRect m_WorldBounds;
    sf::Vector2f  m_SpawnPosition;
    float         m_ScrollSpeed;
    Aircraft     *m_PlayerAircraft;
};

#endif // WORLD_H_