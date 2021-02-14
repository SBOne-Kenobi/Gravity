#ifndef GRAVITY_UTILS_HPP
#define GRAVITY_UTILS_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics/Font.hpp>

namespace gravityEngine {

  inline sf::Vector2f getTextRect(const std::string &text, const sf::Font &font, unsigned int size, bool bold) {
    auto get_advance = [&](char c) {
      return font.getGlyph(c, size, bold).advance;
    };

    float len = 0;
    for (auto c : text)
      len += get_advance(c);

    return sf::Vector2f(len, size);
  }

}

#endif //GRAVITY_UTILS_HPP
