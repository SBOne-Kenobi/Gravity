#ifndef GRAVITY_ENGINE_HPP
#define GRAVITY_ENGINE_HPP


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "Environment.hpp"

namespace gravityEngine {

  class Engine {
  private:

    static std::shared_ptr<Engine> engine;

    sf::RenderWindow window;
    std::unique_ptr<Scene> scene;

    void update();
    void draw();
    void loadScene(std::unique_ptr<Scene> sc);
    void input();

    Engine();

  public:

    static std::shared_ptr<Engine> getEngine();

    int execute();

  };

}

#endif
