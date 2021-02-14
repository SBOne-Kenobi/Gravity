#include <iostream>
#include <Utils.hpp>
#include "Engine.hpp"

std::shared_ptr<gravityEngine::Engine> gravityEngine::Engine::engine = nullptr;
sf::Time gravityEngine::Engine::delta_time = sf::seconds(0);

std::shared_ptr<gravityEngine::Engine> gravityEngine::Engine::getEngine() {
  if (!engine) {
    engine = std::shared_ptr<Engine>(new Engine());
  }

  return engine;
}

gravityEngine::Engine::Engine() :
        window(sf::VideoMode(WIDTH, HEIGHT), NAME, STYLE),
        scene(nullptr) {

  if (!fps_font.loadFromFile(fps_font_file)) {
    std::cerr << "Fail loading fps_font!" << std::endl;
  }

  fps_text.setFont(fps_font);
  fps_text.setCharacterSize(fps_size);
  fps_text.setFillColor(fps_color);
  fps_text.setStyle(fps_bold ? sf::Text::Bold : sf::Text::Regular);

}

void gravityEngine::Engine::loadScene(std::unique_ptr<gravityEngine::Scene> sc) {
  this->scene = std::move(sc);
}


int gravityEngine::Engine::execute() {

  sf::Clock clock;

  while (window.isOpen()) {
    delta_time = clock.restart();
    if (getFPS() > MAX_FPS) {
      sf::sleep(sf::seconds(1. / MAX_FPS) - delta_time);
      delta_time += clock.restart();
    }

    input();
    update();
    draw();
  }

  return 0;
}

void gravityEngine::Engine::input() {
  sf::Event event{};
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window.close();
  }
}

void gravityEngine::Engine::update() {
  if (scene) {
    scene->update();
  }
}

void gravityEngine::Engine::draw() {
  window.clear(background_color);

  if (scene) {
    auto renderer = scene->getComponent<RenderComponent>();
    if (renderer) {
      window.draw(*renderer);
    }
  }

  if (show_FPS) {
    auto fps = std::to_string(getFPS());

    //left down position
    fps_position = {WIDTH, HEIGHT};
    fps_position -= getTextRect(fps, fps_font, fps_size, fps_bold);
    fps_position -= {7, 10}; //bound

    fps_text.setPosition(fps_position);
    fps_text.setString(fps);

    window.draw(fps_text);
  }

  window.display();
}

unsigned int gravityEngine::Engine::getFPS() const {
  if (delta_time.asMilliseconds() == 0)
    return MAX_FPS + 1;
  return 1000 / delta_time.asMilliseconds();
}

void gravityEngine::Engine::setShowFPS(bool show) {
  show_FPS = show;
}
