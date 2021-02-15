#include <engine/Utils.hpp>
#include "components/PhysicsComponent.hpp"
#include "engine/Engine.hpp"
#include "algorithm"

void gravityEngine::PhysicsComponent::update(gravityEngine::Scene *scene) {
  auto &objects = scene->getObjects();
  std::vector<PhysicsObjectComponent *> p_objects;
  for (auto &obj : objects) {
    if (obj) {
      auto phys_comp = obj->getComponent<PhysicsObjectComponent>();
      if (phys_comp) {
        p_objects.push_back(phys_comp);
      }
    }
  }

  switch (model) {
    case NONE_GRAVITY:
      break;
    case CONST_GRAVITY:
      const_update(p_objects);
      break;
    case FIXED_POINT_GRAVITY:
      fixed_update(p_objects);
      break;
    case REAL_GRAVITY:
      real_update(p_objects);
      break;
  }

}

gravityEngine::Model gravityEngine::PhysicsComponent::getModel() const {
  return model;
}

void gravityEngine::PhysicsComponent::setModel(gravityEngine::Model mod) {
  this->model = mod;
}

void gravityEngine::PhysicsComponent::const_update(const std::vector<PhysicsObjectComponent *> &objects) {
  for (auto obj : objects) {
    if (obj) {
      obj->acceleration = {0, -CONST_G};
    }
  }
}

void gravityEngine::PhysicsComponent::fixed_update(const std::vector<PhysicsObjectComponent *> &objects) {
  std::vector<PhysicsObjectComponent *> fixed_objects;
  std::copy_if(objects.begin(), objects.end(), std::back_inserter(fixed_objects), [](PhysicsObjectComponent *obj) {
    return obj && obj->fixed;
  });

  for (auto obj : objects) {
    if (obj && !obj->fixed) {
      for (auto f_obj : fixed_objects) {
        sf::Vector2f r = obj->position - f_obj->position;
        float dist = norm(r);
        if (dist != 0) {
          sf::Vector2f acc = GLOBAL_G * f_obj->mass * r / dist / dist / dist;
          obj->acceleration += acc;
        }
      }
    }
  }
}

void gravityEngine::PhysicsComponent::real_update(const std::vector<PhysicsObjectComponent *> &objects) {
  for (auto obj : objects) {
    if (obj && !obj->fixed) {
      for (auto f_obj : objects) {
        if (f_obj) {
          sf::Vector2f r = obj->position - f_obj->position;
          float dist = norm(r);
          if (dist != 0) {
            sf::Vector2f acc = GLOBAL_G * f_obj->mass * r / dist / dist / dist;
            obj->acceleration += acc;
          }
        }
      }
    }
  }
}

void gravityEngine::PhysicsObjectComponent::update(gravityEngine::Object *object) {
  if (!fixed) {
    float dt = Engine::getDeltaTime().asSeconds();

    position += velocity * dt + acceleration * dt * dt * 0.5f;
    velocity += acceleration * dt;
  }
}

gravityEngine::PhysicsObjectComponent::PhysicsObjectComponent(float mass, const sf::Vector2f &position,
                                                              const sf::Vector2f &velocity,
                                                              const sf::Vector2f &acceleration, bool fixed) :
        position(position), velocity(velocity),
        acceleration(acceleration), mass(mass), fixed(fixed) {}
