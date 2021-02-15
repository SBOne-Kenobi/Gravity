#ifndef GRAVITY_EVENTLISTENER_HPP
#define GRAVITY_EVENTLISTENER_HPP

#include <SFML/Window/Event.hpp>

namespace gravityEngine {

  class EventListener {
  private:
    std::function<void(const sf::Event& event)> on_event;

  public:
    EventListener(std::function<void(const sf::Event &)> on_event);

    void onEvent(const sf::Event& event);
  };

}


#endif
