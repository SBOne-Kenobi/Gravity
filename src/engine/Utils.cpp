#include "engine/Utils.hpp"

namespace gravityEngine {

  sf::Vector2f getTextRect(const std::string &text, const sf::Font &font, unsigned int size, bool bold) {
    auto get_advance = [&](char c) {
      return font.getGlyph(c, size, bold).advance;
    };

    float len = 0;
    for (auto c : text)
      len += get_advance(c);

    return sf::Vector2f(len, size);
  }

  float sq_norm(sf::Vector2f vector) {
    return vector.x * vector.x + vector.y * vector.y;
  }

  float norm(sf::Vector2f vector) {
    return sqrtf(sq_norm(vector));
  }

  sf::Vector2f normalize(sf::Vector2f vector) {
    return vector / norm(vector);
  }

  bool gravityEngine::KeyClicked::operator()(const sf::Keyboard::Key &key) {
    bool res = pressed_before[key] && !sf::Keyboard::isKeyPressed(key);
    pressed_before[key] = sf::Keyboard::isKeyPressed(key);
    return res;
  }
}