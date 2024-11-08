// Copyright 2024 Stephan Tchangov
#pragma once

#include <vector>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>


#include "CelestialBody.hpp"

namespace NB {
class Universe: public sf::Drawable {
 public:
  Universe();  // Required
  explicit Universe(const std::string& filename);
  size_t size() const { return _numBodies; }
  double radius() const { return _radius; }

  void setWindowDimensions(float width, float height);

  const CelestialBody& operator[](size_t i) const;
  friend std::istream& operator>>(std::istream& is, Universe& uni);
  friend std::ostream& operator<<(std::ostream& os, const Universe& uni);
  void step(double dt);
 protected:
  void draw(sf::RenderTarget& window,
            sf::RenderStates states) const override;  // From sf::Drawable
 private:
  std::vector<std::unique_ptr<CelestialBody>> _celestialBodies;
  size_t _numBodies;
  double _radius;
  float _windowWidth;
  float _windowHeight;
};


}  // namespace NB
