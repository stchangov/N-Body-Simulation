# N-Body Simulation

## Overview
This project simulates the motion of the sun and the inner planets of the solar system. It models gravitational forces to create realistic orbital motion and uses SFML for graphical rendering of real-time planetary movement.

## Features
- Real-time simulation of gravitational forces and planetary orbits
- Graphical visualization powered by the SFML library
- Data-driven configuration of celestial bodies through input files

## Requirements
- **C++17 Compiler**: Compatible with the C++17 standard
- **SFML Library**: Required for graphical rendering
- **Make**: For building the project with the provided Makefile

## Project Structure
- **CelestialBody.cpp / .hpp**: Defines the `CelestialBody` class to represent planets and the sun.
- **Universe.cpp / .hpp**: Manages the universe, handles interactions between celestial bodies, and reads input data.
- **main.cpp**: Entry point to run the simulation.
- **Makefile**: Automates the build process, linking necessary files into an executable.
- **planets.txt**: Sample input file that specifies initial data for celestial bodies.

## Usage
1. **Build the Project**:
   Run `make` in the project directory to compile the simulation using the C++17 standard.
   
2. **Run the Simulation**:
   Execute the built program:
   ```bash
   ./NBody < planets.txt
   ```
   This reads data from `planets.txt` to initialize and run the simulation.

## Configuration
- **planets.txt**: Edit this file to change the number and properties of celestial bodies (e.g., position, velocity, mass).

## Acknowledgments
- **SFML**: Used for rendering the graphical simulation.

## Licenses
This project is released under the MIT License. Please refer to the LICENSE file for more details.
