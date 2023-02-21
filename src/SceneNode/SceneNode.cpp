#include "SceneNode.hpp"

SceneNode::SceneNode() {
    m_Parent = nullptr;
}
SceneNode::~SceneNode() {}

void SceneNode::attachChild(Ptr child) {
    child->m_Parent = this;
    m_Children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode &node) {
    auto found =
        std::find_if(m_Children.begin(), m_Children.end(), [&](Ptr &p) -> bool {
            return p.get() == &node;
        });

    assert(found != m_Children.end());

    Ptr result = std::move(*found);
    result->m_Parent = nullptr;
    m_Children.erase(found);
    return result;
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();

    drawCurrent(target, states);

    for (const Ptr &child : m_Children) {
        child->draw(target, states);
    }
}

void SceneNode::drawCurrent(
    sf::RenderTarget &target, sf::RenderStates states) const {}

void SceneNode::update(sf::Time dt) {
    updateCurrent(dt);
    updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time) {}

void SceneNode::updateChildren(sf::Time dt) {
    for (const Ptr &child : m_Children) {
        child->update(dt);
    }
}

sf::Transform SceneNode::getWorldTransform() {
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode *node = this; node != nullptr; node = node->m_Parent) {
        transform = node->getTransform() * transform;
    }

    return transform;
}

sf::Vector2f SceneNode::getWorldPosition() {
    return getWorldTransform() * sf::Vector2f();
}

// by default return scene category
// this must be overrided in derived classes
unsigned int SceneNode::getCategory() const {
    return Category::Scene;
}

void SceneNode::onCommand(const Command &command, sf::Time dt) {

    // bitwise AND between command category and the current
    // scene node category
    if (command.category & getCategory()) {
        command.action(*this, dt);
    }

    for (Ptr &child : m_Children) {
        child->onCommand(command, dt);
    }
}