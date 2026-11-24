
#include "Car.h"
#include <algorithm>
#include <cmath>
#include <string>
namespace {
constexpr float trackWidth = 1280.0f;
constexpr float trackHeight = 720.0f;
bool isOnTrack(const sf::Image& trackMask, const sf::Sprite& car) {
  const sf::Vector2u maskSize = trackMask.getSize();
  if (maskSize.x == 0 || maskSize.y == 0) {
    return false;
  }
  const sf::FloatRect bounds = car.getLocalBounds();
  const sf::Transform transform = car.getTransform();
  // Check the corners, edge centers, and center of the whole car.
  for (int row = 0; row < 3; ++row) {
    for (int column = 0; column < 3; ++column) {
      const sf::Vector2f localPoint{
          bounds.position.x + bounds.size.x * column / 2.0f,
          bounds.position.y + bounds.size.y * row / 2.0f};
      const sf::Vector2f point = transform.transformPoint(localPoint);

      if (point.x < 0.0f || point.y < 0.0f || point.x >= trackWidth ||
          point.y >= trackHeight) {
        return false;
      }

      const unsigned int maskX = static_cast<unsigned int>(
          point.x * static_cast<float>(maskSize.x) / trackWidth);
      const unsigned int maskY = static_cast<unsigned int>(
          point.y * static_cast<float>(maskSize.y) / trackHeight);
      if (trackMask.getPixel({maskX, maskY}).r < 128) {
        return false;
      }
    }
  }

  return true;
}

sf::IntRect visibleBounds(const sf::Image& image) {
  const sf::Vector2u size = image.getSize();
  sf::Vector2u topLeft = size;
  sf::Vector2u bottomRight{};

  for (unsigned int y = 0; y < size.y; ++y) {
    for (unsigned int x = 0; x < size.x; ++x) {
      if (image.getPixel({x, y}).a > 16) {
        topLeft.x = std::min(topLeft.x, x);
        topLeft.y = std::min(topLeft.y, y);
        bottomRight.x = std::max(bottomRight.x, x + 1);
        bottomRight.y = std::max(bottomRight.y, y + 1);
      }
    }
  }

  if (bottomRight.x == 0) {
    return {};
  }

  return {sf::Vector2i(topLeft), sf::Vector2i(bottomRight - topLeft)};
}
}  // namespace

Car::Car() : carSprite(carTexture) {}
bool Car::load(int selectedCar) {
  const int carIndex = selectedCar >= 0 && selectedCar < 4 ? selectedCar : 0;
  const std::string texturePath =
      "assets/car" + std::to_string(carIndex + 1) + ".png";

  sf::Image image;
  if (!image.loadFromFile(texturePath)) {
    return false;
  }

  const sf::IntRect bounds = visibleBounds(image);
  if (bounds.size.y == 0 || !carTexture.loadFromImage(image, false, bounds)) {
    return false;
  }

  constexpr float redCarLength = 85.0f;
  constexpr float otherCarLength = 90.0f;
  const float targetLength = carIndex == 0 ? redCarLength : otherCarLength;
  const float scale = targetLength / static_cast<float>(bounds.size.y);
  carTexture.setSmooth(true);

  if (!trackMask.loadFromFile("assets/Track_Mask.png")) {
    return false;
  }

  carSprite.setTexture(carTexture, true);
  carSprite.setScale({scale, scale});

  const sf::FloatRect carBounds = carSprite.getLocalBounds();
  carSprite.setOrigin({carBounds.position.x + carBounds.size.x / 2.0f,
                       carBounds.position.y + carBounds.size.y / 2.0f});
  setPosition({500.0f, 530.0f});
  setRotation(sf::degrees(90.0f));

  return true;
}

void Car::update(float deltaTime, const CarControls& controls) {
  const bool accelerating = sf::Keyboard::isKeyPressed(controls.accelerate);
  const bool brakingNow = sf::Keyboard::isKeyPressed(controls.brake);

  if (accelerating && speed < 0.0f) {
    speed = std::min(0.0f, speed + braking * deltaTime);
  } else if (brakingNow && speed > 0.0f) {
    speed = std::max(0.0f, speed - braking * deltaTime);
  } else if (accelerating) {
    speed = std::min(maxSpeed, speed + acceleration * deltaTime);
  } else if (brakingNow) {
    speed = std::max(-maxSpeed * 0.5f, speed - acceleration * deltaTime);
  } else {
    if (speed > 0.0f) {
      speed = std::max(0.0f, speed - drag * deltaTime);
    } else {
      speed = std::min(0.0f, speed + drag * deltaTime);
    }
  }

  const sf::Angle previousRotation = carSprite.getRotation();
  if (sf::Keyboard::isKeyPressed(controls.left)) {
    carSprite.rotate(sf::degrees(-turnSpeed * deltaTime));
  }
  if (sf::Keyboard::isKeyPressed(controls.right)) {
    carSprite.rotate(sf::degrees(turnSpeed * deltaTime));
  }

  if (!isOnTrack(trackMask, carSprite)) {
    carSprite.setRotation(previousRotation);
  }
  safeRotation = carSprite.getRotation();

  const float angle = carSprite.getRotation().asRadians() - 1.57079633f;
  const sf::Vector2f movement{std::cos(angle) * speed * deltaTime,
                              std::sin(angle) * speed * deltaTime};
  carSprite.move(movement);

  if (!isOnTrack(trackMask, carSprite)) {
    carSprite.setPosition(safePosition);
    speed = 0.0f;
    return;
  }

  safePosition = carSprite.getPosition();
  safeRotation = carSprite.getRotation();
}

void Car::setPosition(sf::Vector2f position) {
  carSprite.setPosition(position);
  safePosition = position;
}

void Car::setRotation(sf::Angle rotation) {
  carSprite.setRotation(rotation);
  safeRotation = rotation;
}

sf::Vector2f Car::getPosition() const { return carSprite.getPosition(); }

const sf::Sprite& Car::getSprite() const { return carSprite; }

















































































































































































































































































































































































































































































































































































































































































































































































































































































