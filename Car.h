
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

 
private:
  sf::Texture carTexture;
  sf::Sprite carSprite;
  sf::Image trackMask;
  sf::Vector2f safePosition{};
  sf::Angle safeRotation{};
  float speed = 0.0f;
  const float acceleration = 150.0f;
  const float maxSpeed = 350.0f;
  const float braking = 300.0f;
  const float drag = 60.0f;
  const float turnSpeed = 120.0f;
};








