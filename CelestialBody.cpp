// Copyright 2024 Stephan Tchangov
#include "CelestialBody.hpp"
namespace NB {
CelestialBody::CelestialBody() {}

void CelestialBody::setVelocity(sf::Vector2f velocity) {
    _velocity = velocity;
}

void CelestialBody::setPosition(sf::Vector2f position) {
    _position = position;
}

void CelestialBody::setWindowDimensions(float width, float height) {
    _windowWidth = width;
    _windowHeight = height;
}

std::istream& operator>>(std::istream& is, CelestialBody &uni) {
    float x, y, vx, vy, mass;
    std::string imageName;

    is >> x >> y >> vx >> vy >> mass >> imageName;

    uni._position = sf::Vector2f(x, y);
    uni._velocity = sf::Vector2f(vx, vy);
    uni._mass = mass;
    uni._imageName = imageName;

    return is;
}

std::ostream& operator<<(std::ostream& os, const CelestialBody& uni) {
    os << uni._position.x << " " << uni._position.y << " "
       << uni._velocity.x << " " << uni._velocity.y << " "
       << uni._mass << " " << uni._imageName;

    return os;
}

void CelestialBody::draw(sf::RenderTarget& window,
sf::RenderStates states) const {
    sf::Texture texture;
    if (!texture.loadFromFile(_imageName)) {
        throw std::runtime_error("Failed to load texture for celestial body: " + _imageName);
    }

    float scaleFactor = 1.0e-9;

    float xOffset = _windowWidth / 2.0f;
    float yOffset = _windowHeight / 2.0f;

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(_position.x * scaleFactor + xOffset,
                       yOffset - _position.y * scaleFactor);
    window.draw(sprite, states);
}

}  // namespace NB
