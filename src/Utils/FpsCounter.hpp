#ifndef FPSCOUNTER_H_
#define FPSCOUNTER_H_

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../Resources/Fonts.hpp"
#include "../Resources/resource_holder.hpp"

class FpsCounter {
  public:
    FpsCounter();
    FpsCounter(const std::string &text);
    ~FpsCounter();

    void     setText(const std::string &text);
    sf::Text getFpsCounter() const;

  private:
    sf::Text                            m_FpsCounterText;
    ResourceHolder<sf::Font, Fonts::ID> m_Fonts;
};

#endif // FPSCOUNTER_H_
