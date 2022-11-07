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

void SceneNode::updateCurrent(sf::Time dt) {}

void SceneNode::updateChildren(sf::Time dt) {
    for (Ptr &child : m_Children) {
        child->update(dt);
    }
}

sf::Transform SceneNode::getWorldTransform() const {
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode *node = this; node != nullptr; node = node->m_Parent) {
        transform = node->getTransform() * transform;
    }
    return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const {
    return getWorldTransform() * sf::Vector2f();
}
