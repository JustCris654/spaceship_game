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