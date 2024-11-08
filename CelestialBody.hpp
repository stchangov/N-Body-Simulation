// Copyright 2024 Stephan Tchangov
#pragma once
#include <string>
#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

namespace NB {
class CelestialBody: public sf::Drawable {
 public:
  explicit CelestialBody();

  sf::Vector2f position() const { return _position; }
  sf::Vector2f velocity() const { return _velocity; }
  float mass() const { return _mass; }

  void setVelocity(sf::Vector2f velocity);
  void setPosition(sf::Vector2f position);

  void setWindowDimensions(float width, float height);

  friend std::istream& operator>>(std::istream& is, CelestialBody& uni);
  friend std::ostream& operator<<(std::ostream& os, const CelestialBody& uni);

 protected:
  void draw(sf::RenderTarget& window, sf::RenderStates states) const override;

 private:
  sf::Vector2f _position;
  sf::Vector2f _velocity;
  float _mass;
  std::string _imageName;

  // Window dimensions
  float _windowWidth;
  float _windowHeight;
};



}  // namespace NB
