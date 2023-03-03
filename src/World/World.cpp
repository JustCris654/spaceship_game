#include "World.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include <algorithm>
#include <cmath>
#include <memory>

World::World(sf::RenderWindow &window)
    : m_Window(window), m_WorldView(window.getDefaultView()),
      m_WorldBounds(0.f, 0.f, m_WorldView.getSize().x, 900000.f),
      m_SpawnPosition(
          m_WorldView.getSize().x / 2.f,
          m_WorldBounds.height - m_WorldView.getSize().y),
      m_ScrollSpeed(-200.f), m_PlayerAircraft(nullptr), m_CommandQueue() {

    loadTextures();
    buildScene();

    m_WorldView.setCenter(m_SpawnPosition);
}

void World::loadTextures() {
    m_Textures.load(Textures::Eagle, "src/Media/Textures/Eagle.png");
    m_Textures.load(Textures::Raptor, "src/Media/Textures/Raptor.png");
    m_Textures.load(Textures::Desert, "src/Media/Textures/Desert.png");
    m_Textures.load(Textures::TitleScreen, "src/Media/Textures/MenuBg.jpg");
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

    m_PlayerAircraft->setVelocity(0.f, 0.f);

    // forward commands to the scene graph
    while (!m_CommandQueue.isEmpty()) {
        m_SceneGraph.onCommand(m_CommandQueue.pop(), dt);
    }

    this->adaptPlayerVelocity();

    m_SceneGraph.update(dt);
    this->adaptPlayerPosition();
}

CommandQueue &World::getCommandQueue() {
    return m_CommandQueue;
}

void World::adaptPlayerVelocity() {
    sf::Vector2f velocity = m_PlayerAircraft->getVelocity();

    if (velocity.x != 0 && velocity.y != 0) {
        m_PlayerAircraft->setVelocity(velocity / std::sqrt(2.f));
    }

    m_PlayerAircraft->accellerate(0.f, m_ScrollSpeed);
}

void World::adaptPlayerPosition() {
    sf::FloatRect viewBounds(
        m_WorldView.getCenter() - m_WorldView.getSize() / 2.f,
        m_WorldView.getSize());
    const float borderDistance{40.f};

    sf::Vector2f pos = m_PlayerAircraft->getPosition();
    pos.x = std::max(pos.x, viewBounds.left + borderDistance);
    pos.x =
        std::min(pos.x, viewBounds.left + viewBounds.width - borderDistance);

    pos.y = std::max(pos.y, viewBounds.top + borderDistance);
    pos.y =
        std::min(pos.y, viewBounds.top + viewBounds.height - borderDistance);

    m_PlayerAircraft->setPosition(pos);
}
