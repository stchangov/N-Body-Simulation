// Copyright 2024 Stephan Tchangov
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#include "Universe.hpp"
#include "CelestialBody.hpp"

std::string formatElapsedTime(double elapsedTime) {
    int seconds = static_cast<int>(elapsedTime);

    int years = seconds / 31536000;
    seconds %= 31536000;

    int months = seconds / 2592000;
    seconds %= 2592000;

    int days = seconds / 86400;
    seconds %= 86400;

    std::ostringstream oss;
    oss << "Elapsed Time: "
        << years << "y "
        << months << "m "
        << days << "d";

    return oss.str();
}

int main(int argc, const char* argv[]) {
    const int windowWidth = 500;
    const int windowHeight = 500;

    if (argc != 3) {
        throw std::invalid_argument("Usage: " + std::string(argv[0]) +
                                    " [T] [dt]");
    }

    NB::Universe universe;
    std::cin >> universe;

    double T = std::stod(argv[1]);
    double dt = std::stod(argv[2]);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
                            "The Solar System!");
    universe.setWindowDimensions(windowWidth, windowHeight);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.jpeg")) {
        throw std::runtime_error("Failed to load background texture.");
    }

    sf::Sprite backgroundSprite(backgroundTexture);

    sf::Music music;
    if (!music.openFromFile("Bladerunner_2049_-_Mesa.ogg")) {
        throw std::runtime_error("Failed to load music.");
    }

    music.setLoop(true);
    music.play();

    sf::Font font;
    if (!font.loadFromFile("Roboto-Bold.ttf")) {
        throw std::runtime_error("Failed to load font.");
    }

    sf::Text elapsedTimeText;
    elapsedTimeText.setFont(font);
    elapsedTimeText.setCharacterSize(24);
    elapsedTimeText.setFillColor(sf::Color::White);
    elapsedTimeText.setPosition(10.f, 10.f);

    double t = 0;
    while (t < T && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        universe.step(dt);
        t += dt;

        elapsedTimeText.setString(formatElapsedTime(t));

        window.clear();
        window.draw(backgroundSprite);
        window.draw(universe);
        window.draw(elapsedTimeText);
        window.display();
    }

    std::cout << universe;

    return 1;
}
