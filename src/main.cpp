#include "Engine.hpp"

using namespace gravityEngine;

Scene createScene() {
  Scene scene;

  scene.addComponent(std::make_unique<RenderComponent>());

  return scene;
}

int main() {

  auto engine = Engine::getEngine();
  engine->loadScene(
          std::make_unique<Scene>(createScene())
  );

  return engine->execute();
}
