# Flappy Bird for Nintendo DS
🎮 Overview
This project is a fully functional recreation of the Flappy Bird game for the Nintendo DS using the libnds development library. The game features smooth physics, dynamic background scrolling, interactive touch controls, and sound effects. Players control the bird by tapping the touch screen or pressing the B button to fly through moving pipes.

# 🚀 Features
Smooth Background Scrolling: The background scrolls smoothly in sync with the pipes for a seamless experience.
Dynamic Speed Increase: The game speed increases linearly over time, raising the difficulty gradually.
Gravity Simulation: Realistic gravity pulls the bird down unless the player makes it jump.
Jump Mechanics: Press B or tap the bird on the sub-screen to make it jump.
Collision Detection: The game ends when the bird touches pipes or the ground.
Touchscreen Interaction: Tap the bird on the sub-screen to make it jump.
Game Over Panel: Displays the score, distance, and a "Press Start to Restart" message.
Background Switching: Alternates between two backgrounds each time the game restarts.
Sound Effects: Sound plays when the bird jumps, when the game starts, and on game over.
🎮 Gameplay
# Main Menu:

-> Displays a scrolling background and a blinking "Press Start to Play" message.
-> Press Start to begin the game.
-> During Gameplay:

-> Press B or tap Flappy on the sub-screen to make the bird jump.
-> Avoid the pipes and stay in the air!
# Game Over:

A Game Over screen appears with the score and distance.
Press Start to restart the game.
Background Change:

The background alternates between two styles every new game.
🕹️ Controls
B Button: Make the bird jump.
Touch Screen: Tap the bird on the sub-screen to make it jump.
Start Button: Starts the game or restarts after Game Over.
🗂️ Code Structure
📁 Files
-> main.c – Handles the game loop and state transitions.
-> graphics.c / graphics.h – Manages background, sprites, and visual elements.
-> timer.c / timer.h – Controls background scrolling and speed scaling.
-> soundbank.h / soundbank_bin.h – Manages sound effects.
# 🔑 Key Functions

initMainScreenBackground() – Initializes the background (switches between two backgrounds).
updateBackground() – Scrolls the background in sync with the pipes.
updatePipes() – Moves pipes and checks for bird passage.
checkCollisions() – Ends the game when the bird hits a pipe or the ground.
displayGameOverPanel() – Displays the Game Over screen with the score.
initScrollTimer() – Manages background scrolling speed.
disableScrollTimer() – Stops the background from scrolling.

# 🎨 Assets
Bird Sprite: 32x32 pixels.
Pipes: 64x64 pixels, designed to scroll smoothly.
Backgrounds: Two distinct backgrounds for variety.
Menu Screen: Custom background with a blinking text prompt.
🔄 Future Improvements
Add a score counter displayed during gameplay.
Introduce a medal system based on the score.
Implement parallax scrolling for depth.
Add a high score system to track the best runs.
📜 License
This project is open-source under the EPFL License.
You are free to modify, distribute, and improve the game.

# 🙏 Acknowledgments
Inspired by the original Flappy Bird by Dong Nguyen.
Developed using libnds from the DevkitPro toolchain.
Sound system powered by MaxMod.

--------------------------------------------------------------------------------------------------------------------------------


