#ifndef GRAVITY_UTILS_HPP
#define GRAVITY_UTILS_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics/Font.hpp>
#include <cmath>
#include <SFML/Window/Keyboard.hpp>

namespace gravityEngine {

  sf::Vector2f getTextRect(const std::string &text, const sf::Font &font, unsigned int size, bool bold);

  float sq_norm(sf::Vector2f vector);

  float norm(sf::Vector2f vector);

  sf::Vector2f normalize(sf::Vector2f vector);

  class KeyClicked {
  private:
    std::map<sf::Keyboard::Key, bool> pressed_before;
  public:
    bool operator()(const sf::Keyboard::Key &key);
  };

  inline KeyClicked isKeyClicked;

}

#endif //GRAVITY_UTILS_HPP
