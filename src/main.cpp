#include "Engine.hpp"

using namespace gravityEngine;

Scene createScene() {
  Scene scene;

  scene.addComponent(std::make_unique<RenderComponent>());

  return scene;
}

class KeyClicked {
private:
  std::map<sf::Keyboard::Key, bool> pressed_before;
public:
  bool operator()(const sf::Keyboard::Key &key) {
    bool res = pressed_before[key] && !sf::Keyboard::isKeyPressed(key);
    pressed_before[key] = sf::Keyboard::isKeyPressed(key);
    return res;
  }
} isKeyClicked;

void settings(std::shared_ptr<Engine> engine) {
  engine->loadScene(
          std::make_unique<Scene>(createScene())
  );
  engine->setShowFPS(true);
  engine->setLimitFPS(false);

  engine->addEventListener(EventListener([engine](const sf::Event &event) {
    if (isKeyClicked(sf::Keyboard::Space))
      engine->setShowFPS(!engine->isShowFps());
  }));
}

int main() {

  auto engine = Engine::getEngine();

  settings(engine);

  return engine->execute();
}
