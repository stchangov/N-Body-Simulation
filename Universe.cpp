// Copyright 2024 Stephan Tchangov
#include <cmath>
#include <fstream>
#include <utility>
#include "Universe.hpp"

namespace NB {
Universe::Universe() : _numBodies(0), _radius(0.0) {}

Universe::Universe(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file " + filename);
        }

        file >> *this;
}

void Universe::setWindowDimensions(float width, float height) {
    _windowWidth = width;
    _windowHeight = height;

    for (auto& body : _celestialBodies) {
        body->setWindowDimensions(_windowWidth, _windowHeight);
    }
}

const CelestialBody& Universe::operator[](size_t i) const {
    if (i >= _celestialBodies.size()) {
        throw std::out_of_range("Index out of range.");
    }

    return *_celestialBodies[i];
}

void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    for (const auto& body : _celestialBodies) {
        window.draw(*body, states);
    }
}

std::istream& operator>>(std::istream& is, Universe& uni) {
    is >> uni._numBodies >> uni._radius;

    for (size_t i = 0; i < uni._numBodies; ++i) {
        auto body = std::make_unique<CelestialBody>();
        is >> *body;
        body->setWindowDimensions(uni._windowWidth, uni._windowHeight);
        uni._celestialBodies.push_back(std::move(body));
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Universe& uni) {
    os << uni._numBodies << std::endl << uni._radius << std::endl;
    for (const auto& body : uni._celestialBodies) {
        os << *body << "\n";
    }

    return os;
}

void Universe::step(double dt) {
    const double G = -6.67e-11;

    sf::Vector2f acceleration;
    sf::Vector2f netForce(0.0f, 0.0f);
    sf::Vector2f newVelocity(0.0f, 0.0f);
    sf::Vector2f newPosition(0.0f, 0.0f);

    for (size_t i = 0 ; i < _numBodies; ++i) {
        netForce = {0 , 0};
        acceleration = {0, 0};
        newVelocity = {0, 0};
        newPosition = {0, 0};
        for (size_t j = 0; j < _numBodies; ++j) {
            if (i == j) continue;

            float deltaX = _celestialBodies[i]->position().x -
                           _celestialBodies[j]->position().x;

            float deltaY = _celestialBodies[i]->position().y -
                           _celestialBodies[j]->position().y;

            float distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

            float pairwiseForce = (G * _celestialBodies[i]->mass()
                                     * _celestialBodies[j]->mass())
                                     / pow(distance, 2);

            float pairwiseX = pairwiseForce * (deltaX / distance);
            float pairwiseY = pairwiseForce * (deltaY / distance);

            netForce.x += pairwiseX;
            netForce.y += pairwiseY;
        }

        // Calculate acceleration
        acceleration.x += netForce.x / _celestialBodies[i]->mass();
        acceleration.y += netForce.y / _celestialBodies[i]->mass();

        // Calculate new velocity
        float vx = _celestialBodies[i]->velocity().x;
        float vy = _celestialBodies[i]->velocity().y;
        float ax = acceleration.x;
        float ay = acceleration.y;

        newVelocity.x = vx + dt * ax;
        newVelocity.y = vy + dt * ay;

        // Set new velocity
        _celestialBodies[i]->setVelocity(newVelocity);
    }

    for (size_t i = 0; i < _numBodies; ++i) {
        float px = _celestialBodies[i]->position().x;
        float py = _celestialBodies[i]->position().y;

        float vx = _celestialBodies[i]->velocity().x;
        float vy = _celestialBodies[i]->velocity().y;

        newPosition.x = px + dt * vx;
        newPosition.y = py + dt * vy;

        _celestialBodies[i]->setPosition(newPosition);
    }
}

}  // namespace NB
