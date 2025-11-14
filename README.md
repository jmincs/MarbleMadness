# Marble Madness

OOP-based C++ game where you navigate through levels, collect crystals, avoid enemies, and reach the exit.

## Requirements

- macOS, Linux, or Windows
- SDL2 and SDL2 extensions (SDL2_image, SDL2_mixer, SDL2_ttf)
- OpenGL
- C++17 compatible compiler

## Setup

Install SDL2 and the required extensions (SDL2_image, SDL2_mixer, SDL2_ttf) for your platform.

For detailed installation instructions, see the [official SDL2 installation guide](https://wiki.libsdl.org/SDL2/Installation).

**Quick start (macOS with Homebrew):**
```bash
brew install sdl2 sdl2_image sdl2_mixer sdl2_ttf
```

## Build

```bash
make
```

This will create the `MarbleMadness` executable.

To clean build files:

```bash
make clean
```

## Run Game

```bash
./MarbleMadness
```

Make sure the `Assets` directory is in the same directory as the executable, as it contains all game sprites, sounds, and level files.

## Controls

- **Arrow Keys** or **WASD**: Move player
- **Enter**: Confirm/continue
- **Q**: Quit game

## Gameplay

- Navigate through maze-like levels
- Collect crystals to progress
- Avoid or defeat enemy robots
- Collect power-ups (health, ammo, extra lives)
- Reach the exit to complete each level
- Your score, lives, health, and ammo are displayed at the top of the screen

## Game Features

- Multiple levels
- Enemy robots (ragebots, thiefbots)
- Power-ups and collectibles
- Sound effects and background music
- Score tracking system


