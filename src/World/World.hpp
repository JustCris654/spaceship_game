#ifndef WORLD_H_
#define WORLD_H_

#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <algorithm>
#include <array>

#include "../Entities/Aircraft/Aircraft.hpp"
#include "../Player/Player.hpp"
#include "../SceneNode/SceneNode.hpp"
#include "../SceneNode/SpriteNode/SpriteNode.hpp"
#include "../Utils/Resources/ResourceIdentifiers.hpp"

class World : private sf::NonCopyable {

  public:
    explicit World(sf::RenderWindow &window);
    void update(sf::Time dt);
    void draw();

    CommandQueue &getCommandQueue();

  private:
    void loadTextures();
    void buildScene();
    void adaptPlayerVelocity();
    void adaptPlayerPosition();

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

    CommandQueue m_CommandQueue;
};

#endif // WORLD_H_