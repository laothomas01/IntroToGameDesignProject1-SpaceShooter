# IntroToGameDesignProject1-SpaceShooter
SJSU - CS 134 – Game Design Programming Project 1 – Part 1 – Foundation Classes
A Vintage 2D Shooter Arcade Game
In this assignment (Part 1-3), you will build a vintage 2D “Shooter” style
game that will be based on the theme of the “space invader” style games
of the past. The game will leverage the object-oriented and graphics
capabilities of OpenFrameworks and you will learn the basics of game
interaction, 2D game graphics using sprites, rudimentary collision
detection and basic animation. This assignment will be broken down into
three (3) parts. By the end of Part 3, you will have written your own game.
The game should be easily ported to mobile devices such as a smart phone
or tablet. Let’s get started!
Part I Basic Functionality
For Part 1 the basic functionality is as follows:
- [ ] The game starts up in idle mode, waiting to receive a “spacebar”
keyboard event to start the game.
- [ ] The user will be able to use either arrow keys or the mouse (both
must be supported) to move “the Player” which is a small gun
turret in any direction in the play window (up and down, left and
right). The gun turret’s motion is limited by the play area size. You
need to check the bounds for that. (but turret can partially leave
window that is acceptable).
- [ ]  You must support rotation of the turret. You can choose to rotate the turret with a key press OR you can
animate the rotation for a special effect. Your choice. The implementation must use matrix rotations as
described below in requirements.
- [ ]  The spacebar will be used to fire missiles from the turret. Holding the spacebar will cause the missiles to
fire automatically. The rate of fire should be adjustable internally (by a method in the class – see
below). You will need to create a slider to adjust this rate for game playability testing.
- [ ]  The direction of fire should be adjustable by modifying a vector. You also need to create a slider to test
this feature. (These diagnostic sliders should be able to be hidden).
- [ ]  The firing of the missiles should emit a burst sound effect of your choosing.
The visual design of the turret, missiles and background of the playing area (image files) and the sounds
used are up to you. You have creative control over these aspects. Please feel free to put on your game
artist hat. You are required to create the turret image yourself.


• In the next part (Part 2 – next week), we will implement more sophisticated motion and collision
detection.
Required Steps
1. Use an object-oriented design like what we had discussed in the lecture. This will include the classes:
Emitter, Sprite and the SpriteSystem. You will want to use this method (or similar) because we will later
reuse these components for other parts of the game. An example *.h file will be included that shows
how these classes can be defined. 
© K e v i n S m i t h 2 0 2 1 P a g e 2 | 2
2. Modify/Implement matrix transformations (translate, rotate, scale) for the turret as we covered in the
lecture and lab. You don’t need to do any animated scaling of the turret in your game unless you would
like to.
3. Determine the size (in Pixels) of your window for your game. If you would like to ultimately target an
iPhone 6, then the iPhone resolution is: 1334 X 750. If you target an iPad air, the resolution is 2048 X
1536. Knowing in advance what platform you want to target first will help you make decisions on sizes
of elements in the game (players, enemy, sprites etc.). Depending on your PC, you may also be limited
on display size for your window. The window resolution is set in the file, main.cpp.
4. A movie link will be posted that provides a tutorial on how to make images for your sprites. You do not
need final images at this stage, but you will for Part 3 when you complete your final game. If no images
are installed, your program must be robust enough to draw some representation of your sprites and
emitters (missiles and turret(s)). This could be a rectangle.
What to Submit
1. Submit only main.cpp, ofApp.h and ofApp.cpp files for your project (and any other sources files required
to build your project). Zip it into a .zip file using the following naming convention:
 Project1-Foundation-<your name>-<date>.zip.
As an example:
Project1-Foundation-KevinSmith-09042018.zip
No other compressed format will be accepted (zip is available natively on both windows and Mac).
2. Submit a video demonstrating part 1. Use a screen capture program. Mobile phone videos will not be
accepted. Video should be submitted a separate file from the .zip
Due Date
This Part 1 is a one-week assignment. Due date will be posted in Canvas system.
Grading Criteria
To receive the highest grade on the assignment, the code most be original, robust and well documented
(commented) with all functionality specified included. Please refer to the Rubric in the assignment for a
breakdown of the grading.
Any code that is copied or derived from third party sources (with exception of class examples distributed by
instructor ) will not be credited and the assignment will receive a score of a 0.
