#ifndef GRAVITY_OBJECT_HPP
#define GRAVITY_OBJECT_HPP

#include <vector>
#include <memory>
#include <type_traits>

namespace gravityEngine {

  class ObjectComponent {
  public:
    virtual void update() = 0;
  };

  class Object {
  private:
    std::vector<std::unique_ptr<ObjectComponent>> components;
  public:
    void addComponent(std::unique_ptr<ObjectComponent> component);

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

    void update();
  };

}

#endif //GRAVITY_OBJECT_HPP
