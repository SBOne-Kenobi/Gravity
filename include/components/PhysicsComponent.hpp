#ifndef GRAVITY_PHYSICSCOMPONENT_HPP
#define GRAVITY_PHYSICSCOMPONENT_HPP

#include <SFML/System.hpp>
#include "engine/Scene.hpp"

namespace gravityEngine {

  class PhysicsObjectComponent : public ObjectComponent {
  public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass;
    bool fixed;

    PhysicsObjectComponent(float mass = 1, const sf::Vector2f &position = {0, 0},
                           const sf::Vector2f &velocity = {0, 0},
                           const sf::Vector2f &acceleration = {0, 0}, bool fixed = false);

    void update(Object *object) override;
  };

  enum Model {
    NONE_GRAVITY, //without gravitation
    CONST_GRAVITY, //constant gravitation
    FIXED_POINT_GRAVITY, //fixed points create gravitation
    REAL_GRAVITY //all points create gravitation
  };

  class PhysicsComponent : public SceneComponent {
  private:
    Model model = NONE_GRAVITY;

    static void const_update(const std::vector<PhysicsObjectComponent *> &);  //O(n)

    static void fixed_update(const std::vector<PhysicsObjectComponent *> &);  //O(n * #fixed)

    static void real_update(const std::vector<PhysicsObjectComponent *> &);   //O(n^2)

  public:

    Model getModel() const;

    void setModel(Model mod);

    void update(Scene *scene) override;
  };

}


#endif
