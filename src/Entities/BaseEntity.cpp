#include "BaseEntity.hpp"
#include "SFML/System/Vector2.hpp"

void BaseEntity::setVelocity(sf::Vector2f velocity) {
    m_Velocity = velocity;
}

void BaseEntity::setVelocity(float vx, float vy) {
    m_Velocity.x = vx;
    m_Velocity.y = vy;
}

sf::Vector2f BaseEntity::getVelocity() const {
    return m_Velocity;
}

void BaseEntity::updateCurrent(sf::Time dt) {
    move(m_Velocity * dt.asSeconds());
}

void BaseEntity::accellerate(sf::Vector2f v) {
    this->setVelocity(this->getVelocity() + v);
}

void BaseEntity::accellerate(float vx, float vy) {
    this->setVelocity(this->getVelocity().x + vx, this->getVelocity().y + vy);
}