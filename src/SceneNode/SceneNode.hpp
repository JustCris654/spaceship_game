#ifndef SCENENODE_H_
#define SCENENODE_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Vector2.hpp>

#include <assert.h>
#include <memory>
#include <vector>

#include "../Utils/CommandQueue/CommandQueue.hpp"
#include "SFML/System/Time.hpp"

class SceneNode : public sf::Transformable,
                  public sf::Drawable,
                  private sf::NonCopyable {
  public:
    typedef std::unique_ptr<SceneNode> Ptr;

  public:
    SceneNode();
    ~SceneNode();
    void         attachChild(Ptr child);
    Ptr          detachChild(const SceneNode &node);
    void         update(sf::Time dt);
    sf::Vector2f getWorldPosition();

    sf::Vector2f         getWorldPosition() const;
    sf::Transform        getWorldTransform() const;
    virtual unsigned int getCategory() const;
    void                 onCommand(const Command &, sf::Time);

  private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void
    drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    virtual void  updateCurrent(sf::Time dt);
    void          updateChildren(sf::Time dt);
    sf::Transform getWorldTransform();

  private:
    std::vector<Ptr> m_Children;
    SceneNode       *m_Parent;
};

#endif // SCENENODE_H_
