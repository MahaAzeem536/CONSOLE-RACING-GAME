
#pragma once

#include <SFML/Graphics.hpp>

struct CarControls {
  sf::Keyboard::Key accelerate;
  sf::Keyboard::Key brake;
  sf::Keyboard::Key left;
  sf::Keyboard::Key right;
};

class Car {
 public:
  Car();
  bool load(int selectedCar = -1);
  void update(float deltaTime, const CarControls& controls);
  void setPosition(sf::Vector2f position);
  void setRotation(sf::Angle rotation);
  const sf::Sprite& getSprite() const;
  sf::Vector2f getPosition() const;

 









