
# Cube3D

## Introduction

Cube3D is a 3D graphics project inspired by the early days of 3D gaming. It aims to recreate the essence of classic 3D rendering techniques, specifically ray-casting, to generate a 3D perspective from a 2D map. This project serves as an educational tool for understanding the basics of 3D graphics, game development, and the mathematical principles behind rendering techniques.

## Project Description

At its core, Cube3D is about bringing a simple 2D map layout to life in 3D space. Using the ray-casting technique, similar to what was used in the classic game Wolfenstein 3D, Cube3D renders walls, textures, and simple objects into a navigable 3D environment. The project is built to demonstrate how 2D projections can be transformed into 3D visuals, offering a glimpse into the fundamentals of game development and computer graphics.

### Features

- **Ray-Casting Rendering:** Utilizes the ray-casting technique to render a 3D perspective from a 2D map.
- **Texture Mapping:** Applies textures to walls and objects, enhancing the visual experience.
- **Basic Collision Detection:** Implements simple collision detection to prevent the player from walking through walls.
- **Dynamic Camera Movement:** Allows the player to navigate the 3D environment, exploring the map from a first-person perspective.
- **Map Parsing:** Reads and interprets a 2D map layout from a file, translating it into a playable 3D environment.

## Getting Started

### Prerequisites

To run Cube3D, you'll need:

- A C compiler (GCC or Clang recommended)
- The MinilibX graphics library (or any equivalent library capable of handling basic windowing and graphical rendering)

### Installation

1. **Clone the Repository:**

```bash
git clone https://github.com/yourusername/Cube3D.git
cd Cube3D
```
2.  **Compile the Project:**

Using the Makefile included in the project directory, compile Cube3D:


```bash
make
``` 

3.  **Run Cube3D:**

After compilation, you can start Cube3D by running:

bashCopy code

```bash
./cube3d maps/map.cub
```

## Controls

-   **WASD:** Move the player through the 3D environment.
-   **Left/Right Arrow Keys:** Rotate the camera.
 -   **MOUSE:** Rotate the camera.
 -   **R:** Reload weapon.
 -    **MOUSE RIGHT CLICK** Shoot.
  -    **P** Pause the game.
-   **ESC:** Exit the game.
