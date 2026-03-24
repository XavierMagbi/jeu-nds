# Flappy Bird for Nintendo DS

A full recreation of **Flappy Bird** for the **Nintendo DS**, developed in **C** using **libnds** and **Maxmod**.  
This project reproduces the core gameplay of the original game while adapting it to the dual-screen and input capabilities of the Nintendo DS.

The game combines real-time sprite rendering, scrolling backgrounds, collision detection, progressive difficulty, touchscreen input, button controls, and sound playback. The result is a compact but complete handheld implementation of the Flappy Bird experience.

---

## Overview

The idea behind this project is simple: control a bird, avoid obstacles, and survive as long as possible.

The bird is constantly pulled downward by gravity. To keep it in the air, the player must repeatedly make it jump. At the same time, pipes move horizontally across the screen, creating gaps that the bird must pass through. As the game continues, the scrolling speed increases, which makes the timing more difficult and the gameplay more intense.

This project is designed specifically for the Nintendo DS, which means it takes advantage of:

- the **main screen** for the primary gameplay display
- the **sub screen** for secondary visual elements and touch interaction
- physical button input such as **START** and **B**
- sound playback through the DS audio system

The project is organized into separate modules for game logic, graphics, and timing, which makes the code easier to understand, maintain, and extend.

---

## Features

### Core gameplay
- Classic Flappy Bird gameplay adapted to Nintendo DS
- Smooth side-scrolling obstacle system
- Continuous gravity simulation for the bird
- Jump mechanic triggered by button press or touch input
- Pipe collision and ground collision detection
- Score progression based on successful survival and movement

### Visual behavior
- Scrolling background synchronized with gameplay
- Separate assets for menu, gameplay, and game over screens
- Bird and pipe sprites loaded from converted image assets
- Alternating gameplay backgrounds between runs for visual variety

### Audio
- Sound effects for jumping
- Audio cue when the game starts
- Game over sound effect
- Background music support through Maxmod audio assets

### Game flow
- Main menu state
- Active gameplay state
- Game over state
- Restart system using the START button

### Difficulty scaling
- Progressive speed increase over time
- More demanding timing as the game continues
- Higher difficulty without changing the core rules of the game

---

## Gameplay

### Main menu
When the program starts, the player is presented with a menu screen.  
This acts as the entry point of the game and waits for the player to begin.

The menu is responsible for giving a clean starting state before gameplay begins. In many simple games, this state is important because it separates initialization from the actual play session.

### In-game
Once the player presses **START**, the game enters the active gameplay state.

During the game:

- the bird falls continuously because of gravity
- the player must trigger jumps to keep the bird in the air
- pipes move from right to left across the screen
- the player must pass through the gaps without touching the pipes
- the scrolling speed gradually increases as time passes

A good way to picture the gameplay is to imagine balancing a small ball in the air while walls slide toward it. The bird is always being pulled down, and every jump is like a quick push upward. The challenge comes from finding the right rhythm.

### Game over
The run ends when the bird collides with an obstacle or the ground.

At that point:

- the current game stops updating as an active run
- a game over screen is displayed
- the player can press **START** to restart

The restart logic also allows the project to switch between background styles, which gives the game a bit more variety between runs.

---

## Controls

| Input | Action |
|------|--------|
| **START** | Start the game from the menu or restart after game over |
| **B** | Make the bird jump |
| **Touch screen** | Trigger the bird jump interaction |

The touch input is an important part of the Nintendo DS adaptation.  
Instead of relying only on buttons, the game also supports direct interaction through the touchscreen, which makes the gameplay feel more native to the platform.

---

## Project Structure

The repository is divided into configuration files, audio assets, graphics assets, and source code.

```text
.
├── .vscode/
│   ├── c_cpp_properties.json
│   ├── launch.json
│   ├── settings.json
│   └── tasks.json
├── audio/
│   ├── GameOver.wav
│   ├── Start.wav
│   ├── intro.wav
│   ├── jump.wav
│   └── music.xm
├── data/
│   ├── GameOver.grit
│   ├── GameOver.png
│   ├── Menu.grit
│   ├── Menu.png
│   ├── SubGameBg.grit
│   ├── SubGameBg.png
│   ├── Subbg.grit
│   ├── Subbg.png
│   ├── background.grit
│   ├── background.png
│   ├── background2.grit
│   ├── background2.png
│   ├── bird.grit
│   ├── bird.png
│   ├── pipe1.grit
│   ├── pipe1.png
│   ├── pipe2.grit
│   └── pipe2.png
├── source/
│   ├── graphics.c
│   ├── graphics.h
│   ├── main.c
│   ├── timer.c
│   └── timer.h
├── Makefile
└── README.md

```


## Running the Game on an Emulator

After building the project with:  make

the compiler generates a .nds file, which is the Nintendo DS game ROM. To run the game on your computer, open this .nds file in a Nintendo DS emulator such as melonDS on Windows or macOS, or OpenEmu on macOS. First, make sure the build completed successfully and locate the generated .nds file in the project directory.
Then, launch your emulator and use the Open ROM or Import option from its menu. Select the .nds file produced by the project and wait for the emulator to boot the game. Once loaded, the emulator will display the Nintendo DS screens and let you test the game as if it were running on the real console.
Keyboard keys will usually replace the DS buttons, while the mouse will simulate touch screen input.


If the game does not start correctly, check that you selected the correct .nds file and that the emulator is properly configured. For development and debugging, the usual workflow is to rebuild with make, reload the ROM in the emulator, and test the updated version again.
