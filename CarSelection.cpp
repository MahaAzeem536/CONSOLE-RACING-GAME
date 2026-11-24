#include "projectmenu.h"

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <array>
#include <string>
namespace {
constexpr sf::Vector2f screenSize{1920.f, 1080.f};

struct CarChoice {
  sf::Texture previewTexture;
  sf::Texture thumbnailTexture;
  sf::Sprite preview{previewTexture};
  sf::Sprite thumbnail{thumbnailTexture};
  sf::RectangleShape card{{180.f, 145.f}};
};

void fitCar(sf::Sprite& sprite, sf::Vector2f center,
            sf::Vector2f availableSize) {
  const sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(bounds.position + bounds.size / 2.f);

  const sf::Vector2f rotatedSize = sprite.getGlobalBounds().size;
  const float scale = std::min(availableSize.x / rotatedSize.x,
                               availableSize.y / rotatedSize.y);
  sprite.setScale({scale, scale});
  sprite.setPosition(center);
}

void centerText(sf::Text& text, sf::Vector2f center) {
  const sf::FloatRect bounds = text.getLocalBounds();
  text.setOrigin(bounds.position + bounds.size / 2.f);
  text.setPosition(center);
}

void setSelectionView(sf::RenderWindow& window) {
  sf::View view(sf::FloatRect({0.f, 0.f}, screenSize));
  const float windowAspect = static_cast<float>(window.getSize().x) /
                            static_cast<float>(window.getSize().y);
  const float screenAspect = screenSize.x / screenSize.y;
  sf::Vector2f viewportSize{1.f, 1.f};
  if (windowAspect > screenAspect) {
    viewportSize.x = screenAspect / windowAspect;
  } else {
    viewportSize.y = windowAspect / screenAspect;
  }
  view.setViewport(
      {(sf::Vector2f{1.f, 1.f} - viewportSize) / 2.f, viewportSize});
  window.setView(view);
}
}  // namespace

int selectCar(sf::RenderWindow& window, int selectedCar) {
  setSelectionView(window);

  sf::Texture backgroundTexture;
  if (!backgroundTexture.loadFromFile("car-selection-garage.jpg")) {
    return -1;
  }
  backgroundTexture.setSmooth(true);
  sf::Sprite background(backgroundTexture);
  background.setScale({screenSize.x / backgroundTexture.getSize().x,
                       screenSize.y / backgroundTexture.getSize().y});

  sf::Font font;
  if (!font.openFromFile("arial.ttf")) {
    return -1;
  }

  sf::Text title(font, "SELECT YOUR CAR", 58);
  title.setStyle(sf::Text::Bold | sf::Text::Italic);
  centerText(title, {960.f, 90.f});

  sf::RectangleShape leftLine({120.f, 4.f});
  leftLine.setPosition({580.f, 92.f});
  leftLine.setFillColor(sf::Color(210, 20, 30));
  sf::RectangleShape rightLine({120.f, 4.f});
  rightLine.setPosition({1220.f, 92.f});
  rightLine.setFillColor(sf::Color(210, 20, 30));

  std::array<CarChoice, 4> cars;
  std::array<sf::Text, 4> labels{
      sf::Text(font, "CAR 1", 21), sf::Text(font, "CAR 2", 21),
      sf::Text(font, "CAR 3", 21), sf::Text(font, "CAR 4", 21)};

  for (int i = 0; i < static_cast<int>(cars.size()); ++i) {
    const std::string number = std::to_string(i + 1);
    CarChoice& car = cars[i];
    if (!car.previewTexture.loadFromFile("assets/maincar" + number + ".png") ||
        !car.thumbnailTexture.loadFromFile("assets/car" + number + ".png")) {
      return -1;
    }

    car.previewTexture.setSmooth(true);
    car.thumbnailTexture.setSmooth(true);
    car.preview.setTexture(car.previewTexture, true);
    car.thumbnail.setTexture(car.thumbnailTexture, true);
    fitCar(car.preview, {960.f, 455.f}, {1050.f, 480.f});

    const float cardX = 530.f + 215.f * i;
    car.card.setPosition({cardX, 700.f});
    car.card.setFillColor(sf::Color(15, 17, 21, 220));
    car.card.setOutlineColor(sf::Color::White);
    car.card.setOutlineThickness(2.f);

    car.thumbnail.setRotation(sf::degrees(-90.f));
    fitCar(car.thumbnail, {cardX + 90.f, 755.f}, {120.f, 86.f});
    labels[i].setStyle(sf::Text::Bold);
    centerText(labels[i], {cardX + 90.f, 815.f});
  }

  sf::RectangleShape previousButton({220.f, 70.f});
  previousButton.setPosition({400.f, 910.f});
  sf::RectangleShape nextButton({220.f, 70.f});
  nextButton.setPosition({1300.f, 910.f});
  sf::RectangleShape selectButton({300.f, 80.f});
  selectButton.setPosition({810.f, 905.f});
  sf::RectangleShape backButton({160.f, 60.f});
  backButton.setPosition({60.f, 35.f});

  previousButton.setFillColor(sf::Color(15, 17, 21, 180));
  previousButton.setOutlineColor(sf::Color::White);
  previousButton.setOutlineThickness(2.f);
  nextButton.setFillColor(sf::Color(15, 17, 21, 180));
  nextButton.setOutlineColor(sf::Color::White);
  nextButton.setOutlineThickness(2.f);
  backButton.setFillColor(sf::Color(15, 17, 21, 180));
  backButton.setOutlineColor(sf::Color::White);
  backButton.setOutlineThickness(2.f);
  selectButton.setFillColor(sf::Color(210, 15, 25));
  selectButton.setOutlineColor(sf::Color::White);
  selectButton.setOutlineThickness(3.f);

  sf::Text previousText(font, "PREVIOUS", 23);
  sf::Text nextText(font, "NEXT", 23);
  sf::Text selectText(font, "SELECT", 30);
  sf::Text backText(font, "BACK", 22);
  previousText.setStyle(sf::Text::Bold);
  nextText.setStyle(sf::Text::Bold);
  selectText.setStyle(sf::Text::Bold);
  backText.setStyle(sf::Text::Bold);
  centerText(previousText, {510.f, 945.f});
  centerText(nextText, {1410.f, 945.f});
  centerText(selectText, {960.f, 945.f});
  centerText(backText, {140.f, 65.f});

  int carIndex = selectedCar;
  if (carIndex < 0 || carIndex > 3) {
    carIndex = 0;
  }
  while (window.isOpen()) {
    while (const auto event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
        return -1;
      }

      if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
        if (key->code == sf::Keyboard::Key::Escape) {
          return -1;
        }
        if (key->code == sf::Keyboard::Key::Left && carIndex > 0) {
          --carIndex;
        } else if (key->code == sf::Keyboard::Key::Right && carIndex < 3) {
          ++carIndex;
        } else if (key->code == sf::Keyboard::Key::Enter) {
          return carIndex;
        }
      }

      if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>();
          click && click->button == sf::Mouse::Button::Left) {
        const sf::Vector2f mousePosition =
            window.mapPixelToCoords(click->position);
        if (backButton.getGlobalBounds().contains(mousePosition)) {
          return -1;
        }
        if (selectButton.getGlobalBounds().contains(mousePosition)) {
          return carIndex;
        }
        if (previousButton.getGlobalBounds().contains(mousePosition) &&
            carIndex > 0) {
          --carIndex;
        }
        if (nextButton.getGlobalBounds().contains(mousePosition) &&
            carIndex < 3) {
          ++carIndex;
        }
        for (int i = 0; i < static_cast<int>(cars.size()); ++i) {
          if (cars[i].card.getGlobalBounds().contains(mousePosition)) {
            carIndex = i;
          }
        }
      }
    }

    window.clear();
    window.draw(background);
    window.draw(title);
    window.draw(leftLine);
    window.draw(rightLine);
    window.draw(cars[carIndex].preview);

    for (int i = 0; i < static_cast<int>(cars.size()); ++i) {
      cars[i].card.setOutlineColor(i == carIndex ? sf::Color::Green
                                                 : sf::Color::White);
      cars[i].card.setOutlineThickness(i == carIndex ? 5.f : 2.f);
      window.draw(cars[i].card);
      window.draw(cars[i].thumbnail);
      window.draw(labels[i]);
    }

    window.draw(previousButton);
    window.draw(nextButton);
    window.draw(selectButton);
    window.draw(backButton);
    window.draw(previousText);
    window.draw(nextText);
    window.draw(selectText);
    window.draw(backText);
    window.display();
  }

  return -1;
}
