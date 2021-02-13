#include "RenderComponent.hpp"

gravityEngine::RenderObjectComponent::RenderObjectComponent() : Transformable() {}

void gravityEngine::RenderComponent::update(Scene *scene) {
  parent = scene;
}

void gravityEngine::RenderComponent::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  if (parent) {
    auto &objects = parent->getObjects();
    for (auto &obj : objects) {
      auto renderer = obj->getComponent<RenderObjectComponent>();
      if (renderer) {
        target.draw(*renderer, states);
      }
    }
  }
}

gravityEngine::RenderComponent::RenderComponent(gravityEngine::Scene *parent) : parent(parent) {}
