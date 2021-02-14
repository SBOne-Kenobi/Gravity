#include <iostream>
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

  if (!fps_font.loadFromFile("arial.ttf")) {
    std::cerr << "Fail loading fps_font!" << std::endl;
  }

  fps_text.setFont(fps_font);
  fps_text.setCharacterSize(fps_size);
  fps_text.setFillColor(fps_color);
  fps_text.setStyle(fps_style);

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

    auto get_advance = [this](char c) {
      return fps_font.getGlyph(c, fps_size, true).advance;
    };

    int len = 0;
    for (auto c : fps)
      len += get_advance(c);

    fps_position = {WIDTH, HEIGHT};
    fps_position -= sf::Vector2f(len, fps_size);
    fps_position -= {10, 10};

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
