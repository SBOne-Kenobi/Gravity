#ifndef GRAVITY_ENGINE_HPP
#define GRAVITY_ENGINE_HPP


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "Environment.hpp"
#include "RenderComponent.hpp"

namespace gravityEngine {

  class Engine {
  private:

    static std::shared_ptr<Engine> engine;
    static sf::Time delta_time;

    sf::RenderWindow window;
    sf::Color background_color = sf::Color::Black;

    std::unique_ptr<Scene> scene;

    bool show_FPS = false;
    sf::Text fps_text;
    sf::Font fps_font;
    std::string fps_font_file = "arial.ttf";
    size_t fps_size = 20;
    sf::Color fps_color = sf::Color::White;
    bool fps_bold = false;
    sf::Vector2f fps_position;

    void update();

    void draw();

    void input();

    Engine();

  public:

    static std::shared_ptr<Engine> getEngine();

    int execute();

    void loadScene(std::unique_ptr<Scene> sc);

    unsigned int getFPS() const;

    void setShowFPS(bool show);

  };

}

#endif
