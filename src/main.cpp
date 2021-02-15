#include <components/PhysicsComponent.hpp>
#include <iostream>
#include "engine/Engine.hpp"
#include "engine/Utils.hpp"

using namespace gravityEngine;

class RendCircleShape : public RenderObjectComponent {
public:
  RendCircleShape(float r, sf::Color color, sf::Vector2f pos) : RenderObjectComponent(), shape(r) {
    shape.setFillColor(color);
    shape.setPosition(pos);
    shape.setOrigin(r, r);
  }

  void update(Object *object) override {}

  void setPosition(sf::Vector2f pos) {
    shape.setPosition(pos);
  }

protected:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
    target.draw(shape, states);
  }

private:
  sf::CircleShape shape;
};

class Circle : public Object {
private:
  RendCircleShape *shape;

public:

  Circle(float r, sf::Color color, sf::Vector2f pos = {0, 0}) {
    shape = addComponent(RendCircleShape(r, color, pos));
  }

  void update() override {
    Object::update();
    auto p_comp = getComponent<PhysicsObjectComponent>();
    if (p_comp) {
      sf::Vector2f pos = p_comp->position;
      pos.y = HEIGHT - pos.y;
      shape->setPosition(pos);
    }
  }
};

Scene createScene() {
  Scene scene;

  scene.addComponent(RenderComponent());
  auto p_comp = scene.addComponent(PhysicsComponent());
  p_comp->setModel(Model::CONST_GRAVITY);

  auto circle = scene.addObject(Circle(20, sf::Color::Green))->
          addComponent(PhysicsObjectComponent());

  circle->position = {WIDTH / 2.f, HEIGHT};

  return scene;
}

void setSettings(std::shared_ptr<Engine> engine) {
  engine->loadScene(
          std::make_unique<Scene>(createScene())
  );
  engine->setShowFPS(true);
  engine->setLimitFPS(false);

  engine->addEventListener([engine](const sf::Event &event) {
    if (isKeyClicked(sf::Keyboard::Space))
      engine->setShowFPS(!engine->isShowFps());
  });
}

int main() {

  auto engine = Engine::getEngine();

  setSettings(engine);

  return engine->execute();
}
