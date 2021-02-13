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
        window(sf::VideoMode(WIDTH, HEIGHT), NAME, sf::Style::Close),
        scene(nullptr) {}

void gravityEngine::Engine::update() {
  if (scene) {
    scene->update();
  }
}

void gravityEngine::Engine::draw() {
  window.clear(sf::Color::Black);

  if (scene) {
    auto renderer = scene->getComponent<RenderComponent>();
    if (renderer) {
      window.draw(*renderer);
    }
  }

  window.display();
}

void gravityEngine::Engine::loadScene(std::unique_ptr<gravityEngine::Scene> sc) {
  this->scene = std::move(sc);
}

int gravityEngine::Engine::execute() {

  sf::Clock clock;

  while (window.isOpen()) {
    delta_time = clock.restart();

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
