#include "engine/Object.hpp"

void gravityEngine::Object::update() {
  for (auto &component : components) {
    if (component)
      component->update(this);
  }
}