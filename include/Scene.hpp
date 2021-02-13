#ifndef GRAVITY_SCENE_HPP
#define GRAVITY_SCENE_HPP

#include <vector>
#include <memory>
#include <type_traits>
#include "Object.hpp"

namespace gravityEngine {

  class Scene;

  class SceneComponent {
  public:
    virtual void update(Scene *) = 0;

    virtual ~SceneComponent() = default;
  };

  class Scene {
  private:

    std::vector<std::unique_ptr<SceneComponent>> components;
    std::vector<std::unique_ptr<Object>> objects;

  public:
    template<class T,
            std::enable_if_t<std::is_base_of<SceneComponent, T>::value, bool> = true
    >
    T *addComponent(std::unique_ptr<T> component) {
      components.push_back(std::move(component));
      return dynamic_cast<T *>(components.back().get());
    }

    template<class T,
            std::enable_if_t<std::is_base_of<SceneComponent, T>::value, bool> = true
    >
    T *getComponent() const {

      for (auto &component : components) {
        if (dynamic_cast<T *>(component.get()))
          return dynamic_cast<T *>(component.get());
      }

      return nullptr;
    }

    Object *addObject(std::unique_ptr<Object> object);

    void update();

    std::vector<std::unique_ptr<Object>> &getObjects();
  };

}

#endif //GRAVITY_SCENE_HPP
