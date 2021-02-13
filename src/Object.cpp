#include "Object.hpp"

void gravityEngine::Object::addComponent(std::unique_ptr<ObjectComponent> component) {
  components.push_back(std::move(component));
}

void gravityEngine::Object::update() {
  for (auto &component : components)
    component->update(this);
}