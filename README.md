# VoidShift: A 2D Dimensional Puzzle-Platformer

## Overview
VoidShift is an innovative 2D puzzle-platformer built in C++ using the SFML library. Players manipulate dimensional rifts to alter the environment, shifting platforms and walls to solve spatial puzzles and reach the level exit. The game combines platforming with dynamic environment manipulation, offering a unique experience distinct from traditional puzzle or platformer games.

This open-source project is designed for developers, gamers, and educators interested in C++ game development, spatial puzzles, and dynamic mechanics. By sponsoring VoidShift via GitHub Sponsors, you support new features, level designs, and educational resources for the community.

## Features
- **Dimensional Rift Mechanics**: Place rifts to shift platforms and walls in the environment.
- **Spatial Puzzles**: Solve puzzles by altering the level layout to create paths.
- **Minimalist Visuals**: Clean 2D graphics with glowing rift effects.
- **Cross-Platform**: Runs on Windows, macOS, and Linux via SFML.
- **Modular Codebase**: Well-structured C++ code for easy extension and learning.

## Getting Started

### Prerequisites
- **C++ Compiler**: GCC, Clang, or MSVC with C++17 support.
- **SFML Library**: Version 2.5.1 or later (install via [SFML's official site](https://www.sfml-dev.org/) or package manager).
- **CMake**: Version 3.10 or later for building.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/voidshift.git
   cd voidshift
   ```
2. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
3. Configure with CMake:
   ```bash
   cmake ..
   ```
4. Build the project:
   ```bash
   cmake --build .
   ```
5. Run the game:
   ```bash
   ./VoidShift
   ```

## Gameplay
- **Objective**: Reach the exit by placing dimensional rifts to shift the environment and create paths.
- **Controls**:
  - **WASD**: Move the player (W to jump).
  - **Arrow Keys**: Move the cursor to place rifts.
  - **Space**: Place a rift.
  - **R**: Reset the level.
  - **Esc**: Pause or exit.
- **Mechanics**: Rifts shift nearby platforms and walls, altering the level layout. Strategically place rifts to solve puzzles while avoiding traps.

## Project Structure
- `src/main.cpp`: Game entry point and main loop.
- `src/Entity.hpp`: Base class for game entities (player, platforms, rifts, exit).
- `src/Game.hpp`: Core game logic, environment manipulation, and rendering.
- `assets/`: Placeholder for textures/fonts (add your own or use SFML defaults).

## Contributing
Contributions are welcome! Fork the repo, create a feature branch, and submit a pull request. For major changes, open an issue to discuss your ideas.

## Sponsorship
Support VoidShift’s development through [GitHub Sponsors](https://github.com/sponsors/yourusername)! Your contributions fund:
- New levels and environmental mechanics.
- Advanced rift effects and puzzle complexity.
- Tutorials for C++ and game development.
- Optimizations for broader platform support.

## License
Licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgments
- Built with [SFML](https://www.sfml-dev.org/) for graphics and input.
- Inspired by spatial puzzles and platforming adventures.
- Thanks to the open-source community for feedback and inspiration.

---

**Sponsor VoidShift to reshape the future of puzzle-platformers!**