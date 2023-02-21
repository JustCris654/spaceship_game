#include <cassert>
class SceneNode;
#include "Categories.hpp"
#include <SFML/System/Time.hpp>
#include <functional>

struct Command {
    Command() {
        category = Category::None;
    };
    std::function<void(SceneNode &, sf::Time)> action;
    unsigned int                               category;
};

template <typename GameObj, typename Function>
std::function<void(SceneNode &node, sf::Time dt)> derivedAction(Function fn) {
    return [=](SceneNode &node, sf::Time dt) {
        // check if cast is safe
        assert(dynamic_cast<GameObj *>(&node) != nullptr);

        // downcast node and invoke function
        fn(static_cast<GameObj &>(node), dt);
    };
}