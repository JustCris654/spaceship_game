#include "World.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include <memory>

World::World(sf::RenderWindow &window)
    : m_Window(window), m_WorldView(window.getDefaultView()),
      m_WorldBounds(0.f, 0.f, m_WorldView.getSize().x, 900000.f),
      m_SpawnPosition(
          m_WorldView.getSize().x / 2.f,
          m_WorldBounds.height - m_WorldView.getSize().y),
      m_ScrollSpeed(-200.f), m_PlayerAircraft(nullptr) {

    loadTextures();
    buildScene();

    m_WorldView.setCenter(m_SpawnPosition);
}

void World::loadTextures() {
    m_Textures.load(Textures::Eagle, "src/Media/Textures/Eagle.png");
    m_Textures.load(Textures::Raptor, "src/Media/Textures/Raptor.png");
    m_Textures.load(Textures::Desert, "src/Media/Textures/Desert.png");
}

void World::buildScene() {

    // initialize all scene layers and attach them
    // to the scenes graph
    for (size_t i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        m_SceneLayers[i] = layer.get();

        m_SceneGraph.attachChild(std::move(layer));
    }

    // initialize texture with desert and generate the
    // texture rect thats the same as the world size
    sf::Texture &texture = m_Textures.get(Textures::Desert);
    sf::IntRect  textureRect(m_WorldBounds);
    texture.setRepeated(true);

    // attach the desert texture to the scene layers
    // as the backgorund texture (the first to be drawn)
    std::unique_ptr<SpriteNode> backgroundSprite(
        new SpriteNode(texture, textureRect));
    backgroundSprite->setScale({1.85f, 1.85f});
    backgroundSprite->setPosition(m_WorldBounds.left, m_WorldBounds.top);
    m_SceneLayers[Background]->attachChild(std::move(backgroundSprite));

    // player aircraft and add it to scene layers
    std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, m_Textures));
    m_PlayerAircraft = player.get();
    m_PlayerAircraft->setPosition(m_SpawnPosition);
    m_PlayerAircraft->setVelocity(0.f, m_ScrollSpeed);
    m_SceneLayers[Air]->attachChild(std::move(player));

    // escort of two airplanes relative to the player
    // left escort
    std::unique_ptr<Aircraft> leftEscort(
        new Aircraft(Aircraft::Raptor, m_Textures));
    leftEscort->setPosition(-80.f, 50.f);
    m_PlayerAircraft->attachChild(std::move(leftEscort));

    // right escort
    std::unique_ptr<Aircraft> rightEscort(
        new Aircraft(Aircraft::Raptor, m_Textures));
    rightEscort->setPosition(80.f, 50.f);
    m_PlayerAircraft->attachChild(std::move(rightEscort));
}

void World::draw() {
    m_Window.setView(m_WorldView);
    m_Window.draw(m_SceneGraph);
}

void World::update(sf::Time dt) {
    m_WorldView.move(0.f, m_ScrollSpeed * dt.asSeconds());

    // forward commands to the scene graph
    while (!m_CommandQueue.isEmpty()) {
        m_SceneGraph.onCommand(m_CommandQueue.pop(), dt);
    }

    m_SceneGraph.update(dt);
}

CommandQueue &World::getCommandQueue() {
    return m_CommandQueue;
}