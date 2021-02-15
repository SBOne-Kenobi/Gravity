#include "engine/Scene.hpp"

gravityEngine::Object *gravityEngine::Scene::addObject(std::unique_ptr<Object> object) {
  objects.push_back(std::move(object));
  return objects.back().get();
}

void gravityEngine::Scene::update() {
  for (auto &component : components) {
    if (component) {
      component->update(this);
    }
  }

  for (auto &obj : objects) {
    if (obj) {
      obj->update();
    }
  }
}

std::vector<std::unique_ptr<gravityEngine::Object>> &gravityEngine::Scene::getObjects() {
  return objects;
}
