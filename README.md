# Flappy Bird for Nintendo DS

## Overview
This project is a recreation of the popular Flappy Bird game, designed and implemented for the Nintendo DS platform using the **libnds** development library. The game features smooth physics, jump mechanics, gravity simulation, and collision detection. Players navigate a bird by pressing the `A` button to jump while avoiding obstacles.

## Features
- **Gravity Simulation**: The bird falls naturally due to gravity.
- **Jump Mechanics**: Press the `A` button to make the bird jump upward.
- **Collision Detection**: The bird stops when it hits the ground or the edges of the screen.
- **Background Scrolling**: Smoothly scrolling background for a dynamic visual effect.
- **Customizable Physics**: Easily tweak gravity, jump force, and other gameplay parameters.

## Gameplay
1. **Start Screen**: Upon launching the game, a message prompts the player to press the `START` button to begin.
2. **Playing**: The bird stays fixed horizontally while jumping vertically to avoid falling. The objective is to navigate through gaps in pipes or other obstacles (not yet implemented).
3. **Game Over**: The game stops if the bird touches the ground or flies out of bounds.

## Controls
- `A` Button: Makes the bird jump.
- `START` Button: Starts the game from the main menu.

## Code Structure
### Files
1. **main.c**: Contains the main game loop and handles the game state transitions.
2. **simulation.c** / **simulation.h**: Manages game initialization, reset, and bird physics.
3. **graphics.c** / **graphics.h**: Handles sprite and background rendering.
4. **timer.c** / **timer.h**: Implements timers for frame updates and animations.

### Key Functions
- **initGame()**: Initializes game variables and state.
- **handleInput()**: Handles user input (jump and start).
- **updateBird()**: Applies gravity and updates the bird’s position.
- **updateBackground()**: Scrolls the background for a dynamic effect.
- **resetGame()**: Resets the game after a collision or game over.

## Physics Settings
You can adjust the physics parameters in `simulation.c`:
- **Gravity**: Change the `gravity` constant to make the bird fall faster or slower.
- **Jump Force**: Modify `jumpForce` for higher or lower jumps.
- **Ground Level**: Set the `groundLevel` constant for different ground positions.

## Installation
### Prerequisites
- DevkitPro/Libnds: Required for developing and running homebrew applications on the Nintendo DS.
- GRIT: To convert assets (sprites, background) into NDS-compatible formats.

### Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/your-repo/flappy-bird-nds.git
   ```
2. Build the project using `make`:
   ```bash
   cd flappy-bird-nds
   make
   ```
3. Transfer the `.nds` file to your Nintendo DS or emulator.
4. Launch the game on your device/emulator.

## Assets
- **Bird Sprite**: A small 32x32 pixel sprite representing the bird.
- **Background**: A scrolling tiled background depicting a city skyline.

## How to Customize
1. **Sprites**: Replace `bird.png` or `background.png` with your custom assets and use GRIT to convert them.
2. **Physics**: Adjust the constants in `simulation.c` to change game dynamics.

## Future Improvements
- Add obstacles (pipes) for the bird to navigate.
- Implement scoring based on the distance traveled.
- Add sound effects for jumps and collisions.
- Enhance background visuals with parallax scrolling.

## License
This project is open-source and released under the EPFL License. You are free to modify and distribute it as you like.

## Acknowledgments
- Inspired by the original Flappy Bird by Dong Nguyen.
- Developed using **libnds** from the DevkitPro toolchain.

--------------------------------------------------------------------------------------------------------------------------------


