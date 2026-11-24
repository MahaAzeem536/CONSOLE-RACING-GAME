#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class Game {
 public:
  int run(sf::RenderWindow& window, int selectedCar = -1);
};
