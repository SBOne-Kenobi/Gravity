#ifndef GRAVITY_ENGINE_HPP
#define GRAVITY_ENGINE_HPP


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "Environment.hpp"
#include "components/RenderComponent.hpp"
#include "EventListener.hpp"

namespace gravityEngine {

  enum ReturnState {
    OK = 0,
    LOAD_FAIL
  };

  class Engine {
  private:

    static std::shared_ptr<Engine> engine;
    static sf::Time delta_time;

    ReturnState return_status = OK;

    sf::RenderWindow window;
    sf::Color background_color = sf::Color::Black;

    std::unique_ptr<Scene> scene;
    std::vector<EventListener> event_listeners;

    bool limit_fps = true;
    bool show_fps = false;
    sf::Text fps_text;
    sf::Font fps_font;
    std::string fps_font_file = "arial.ttf";
    size_t fps_size = 15;
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

    int getFPS() const;

    static sf::Time getDeltaTime();

    void setShowFPS(bool show);

    bool isLimitFps() const;

    bool isShowFps() const;

    void setLimitFPS(bool set);

    void addEventListener(EventListener listener);

    void addEventListener(std::function<void(const sf::Event&)> on_event);
  };

}

#endif
