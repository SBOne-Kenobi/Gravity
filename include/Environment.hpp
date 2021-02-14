#ifndef GRAVITY_ENVIRONMENT_HPP
#define GRAVITY_ENVIRONMENT_HPP

#include <cstddef>
#include <SFML/Graphics.hpp>

namespace gravityEngine {

  //Window constants
  inline const size_t WIDTH = 700;
  inline const size_t HEIGHT = 400;
  inline const char* NAME = "Gravity";
  inline const auto STYLE = sf::Style::Close;

  inline const unsigned int MAX_FPS = 1000;

  //Gravity constants
  inline const float LOCAL_G = 9.8;
  inline const float GLOBAL_G = 6.67e-11;

}

#endif
