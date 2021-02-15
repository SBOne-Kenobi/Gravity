#ifndef GRAVITY_OBJECT_HPP
#define GRAVITY_OBJECT_HPP

#include <vector>
#include <memory>
#include <type_traits>

namespace gravityEngine {

  class Object;

  class ObjectComponent {
  public:
    virtual void update(Object *) = 0;
  };

  class Object {
  private:
    std::vector<std::unique_ptr<ObjectComponent>> components;
  public:
    template<class T,
            std::enable_if_t<std::is_base_of<ObjectComponent, T>::value, bool> = true
    >
    T *addComponent(std::unique_ptr<T> component) {
      components.push_back(std::move(component));
      return dynamic_cast<T *>(components.back().get());
    }

    template<class T,
            std::enable_if_t<std::is_base_of<ObjectComponent, T>::value, bool> = true
    >
    T *addComponent(T &&component) {
      return addComponent(std::make_unique<T>(std::move(component)));
    }

    template<class T,
            std::enable_if_t<std::is_base_of<ObjectComponent, T>::value, bool> = true
    >
    T *getComponent() const {

      for (auto &component : components) {
        if (dynamic_cast<T *>(component.get()))
          return dynamic_cast<T *>(component.get());
      }

      return nullptr;
    }

    virtual void update();
  };

}

#endif //GRAVITY_OBJECT_HPP
