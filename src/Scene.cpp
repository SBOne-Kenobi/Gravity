#include "Scene.hpp"

void gravityEngine::Scene::addComponent(std::unique_ptr<SceneComponent> component) {
  components.push_back(std::move(component));
}

void gravityEngine::Scene::addObject(std::unique_ptr<Object> object) {
  objects.push_back(std::move(object));
}

void gravityEngine::Scene::update() {
  for (auto &component : components)
    component->update(this);
}

std::vector<std::unique_ptr<gravityEngine::Object>> &gravityEngine::Scene::getObjects() {
  return objects;
}
