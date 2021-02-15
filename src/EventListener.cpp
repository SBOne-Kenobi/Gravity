#include "EventListener.hpp"

gravityEngine::EventListener::EventListener(std::function<void(const sf::Event &)> on_event) :
        on_event(std::move(on_event)) {}

void gravityEngine::EventListener::onEvent(const sf::Event &event) {
  on_event(event);
}
