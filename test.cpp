// Copyright 2024 Stephan Tchangov
#include <iostream>
#include <string>
#include <cmath>

#include "Universe.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

using NB::Universe;
using NB::CelestialBody;

// Universe tests
BOOST_AUTO_TEST_CASE(testUniverseSize) {
    Universe universe("planets.txt");
    BOOST_REQUIRE_EQUAL(universe.size(), 5);
}

BOOST_AUTO_TEST_CASE(testUniverseRadius) {
    Universe universe("planets.txt");
    double radius = 2.50e+11;
    BOOST_REQUIRE_EQUAL(universe.radius(), radius);
}

BOOST_AUTO_TEST_CASE(universePlanetCountTest) {
    Universe universe("planets.txt");

    size_t expectedPlanets = 5;
    BOOST_REQUIRE_EQUAL(universe.size(), expectedPlanets);
}

// Celestial tests
BOOST_AUTO_TEST_CASE(testCelestialBodyExtractionOperator) {
    std::string data = "1.4960e+11 0.0000e+00 0.0000e+00 "
                   "2.9800e+04 5.9740e+24 earth.gif\n";
    std::istringstream input(data);
    CelestialBody body;
    input >> body;

    BOOST_CHECK_CLOSE(body.position().x, 1.4960e+11, 1e-5);
    BOOST_CHECK_CLOSE(body.position().y, 0.0, 1e-5);
    BOOST_CHECK_CLOSE(body.velocity().x, 0.0, 1e-5);
    BOOST_CHECK_CLOSE(body.velocity().y, 2.9800e+04, 1e-5);
    BOOST_CHECK_CLOSE(body.mass(), 5.9740e+24, 1e-5);
}

BOOST_AUTO_TEST_CASE(testCelestialBodyInsertionOperator) {
    std::string data = "1.4960e+11 0.0000e+00 0.0000e+00 "
                   "2.9800e+04 5.9740e+24 earth.gif\n";
    std::istringstream input(data);

    CelestialBody earth;
    input >> earth;

    std::ostringstream oss;
    oss << earth;

    std::string output = oss.str();
    std::istringstream outputStream(output);

    float posX, posY, velX, velY, mass;
    std::string imageName;

    outputStream >> posX >> posY >> velX >> velY >> mass >> imageName;

    BOOST_CHECK_CLOSE(posX, 1.4960e+11, 1e-5);
    BOOST_CHECK_CLOSE(posY, 0.0f, 1e-5);
    BOOST_CHECK_CLOSE(velX, 0.0f, 1e-5);
    BOOST_CHECK_CLOSE(velY, 2.9800e+04, 1e-5);
    BOOST_CHECK_CLOSE(mass, 5.9740e+24, 1e-5);
    BOOST_CHECK_EQUAL(imageName, "earth.gif");
}

// Part b
// BOOST_AUTO_TEST_CASE(testAcceleration) {
//     Universe universe("planets.txt");
//     CelestialBody earth = universe[0];
//     CelestialBody mars = universe[1];

//     const double G = 6.674e-11;

//     sf::Vector2f netForce(0.0f, 0.0f);
//     sf::Vector2f newVelocity(0.0f, 0.0f);
//     sf::Vector2f newPosition(0.0f, 0.0f);

//     double dt = 10;
//     universe.step(dt);

//     // float dx = earth.position().x - mars.position().x;
//     // float dy = earth.position().y - mars.position().y;

//     for (size_t i = 0; i < universe.size(); ++i) {
//         netForce = {0, 0};
//         for (size_t j = i + 1; j < universe.size(); ++j) {
//             float deltaX = universe[i].position().x -
//                            universe[j].position().x;
//             float deltaY = universe[i].position().y -
//                            universe[j].position().y;

//             float distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

            //    float partwiseForce = (G * universe[i].mass() *
//                                       universe[j].mass())
            //                             / pow(distance, 2);

//             float partwiseX = partwiseForce * (deltaX / distance);
//             float partWiseY = partwiseForce * (deltaY / distance);

//             netForce.x += partwiseX;
//             netForce.y += partWiseY;
//         }
//     }

//     sf::Vector2f acceleration;
//     acceleration.x += netForce.x / earth.mass();
//     acceleration.y += netForce.y / earth.mass();

//     std::cout << "Ax" << acceleration.x << std::endl;
//     std::cout << "Ay" << acceleration.y << std::endl;

    // float vx = universe[i].velocity().x;
    // float vy = universe[i].velocity().y;
    // float ax = acceleration.x;
    // float ay = acceleration.y;
    // newVelocity.x = (vx + dt) * ax;
    // newVelocity.y = (vy + dt) * ay;
    // float px = universe[i].position().x;
    // float py = universe[i].position().y;
    // float vx = newVelocity.x;
    // float vy = newVelocity.y;
//     newPosition.x = (px + dt) * vx;
//     newPosition.y = (py + dt) * vy;
// }

BOOST_AUTO_TEST_CASE(test_position_change) {
    Universe universe("planets.txt");
    CelestialBody earth = universe[0];
    CelestialBody mars = universe[1];

    sf::Vector2f initialEarthPosition = earth.position();
    sf::Vector2f initialMarsPosition = mars.position();

    double dt = 10;
    universe.step(dt);

    sf::Vector2f newEarthPosition = earth.position();
    sf::Vector2f newMarsPosition = mars.position();

    BOOST_CHECK_CLOSE(initialEarthPosition.x, newEarthPosition.x, 1e-5);
    BOOST_CHECK_CLOSE(initialEarthPosition.y, newEarthPosition.y, 1e-5);

    BOOST_CHECK_CLOSE(initialMarsPosition.x, newMarsPosition.x, 1e-5);
    BOOST_CHECK_CLOSE(initialMarsPosition.y, newMarsPosition.y, 1e-5);
}
