#ifndef GRAVITY_RENDERCOMPONENT_HPP
#define GRAVITY_RENDERCOMPONENT_HPP

#include "engine/Scene.hpp"
#include <SFML/Graphics.hpp>

namespace gravityEngine {

  class RenderObjectComponent : public ObjectComponent,
                                virtual public sf::Drawable,
                                virtual public sf::Transformable {
  public:
    RenderObjectComponent();
  };

  class RenderComponent : public SceneComponent, public sf::Drawable {
  public:
    void update(Scene *) override;

    explicit RenderComponent(Scene *parent = nullptr);

  protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  private:
    Scene *parent = nullptr;
  };

}


#endif
