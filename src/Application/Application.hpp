#include <SFML/System/NonCopyable.hpp>

#include "../Player/Player.hpp"
#include "../States/StateStack/StateStack.hpp"
#include "../Utils/Resources/resource_holder.hpp"

class Application : sf::NonCopyable {

  public:
    Application();
    ~Application();

    void run();

  private:
    void registerStates();
    void processInput();
    void update(sf::Time dt);
    void render();

  private:
    const sf::Time TimePerFrame{sf::seconds(1.f / 60.f)};

    StateStack       m_StateStack;
    sf::RenderWindow m_Window;

    TextureHolder m_Textures;
    FontHolder    m_Fonts;
    Player        m_Player;
};
