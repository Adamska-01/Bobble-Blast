# Bobble-Blast
BubbleBobble-like game created with 'SDL'.


# Table of contents
* [Download & Setup](#download-&-setup)
* [General info](#general-info)
* [Technologies](#technologies)


## Download & Setup  
**`DOWNLOAD THE PROJECT AND START THE SOLUTION ON x86 PLATFORM. IT WON'T RUN ON x64`**

## General info
This project is simple gamme where the player has to shoot falling bobbles matching the colour. **`Multiplayer support added`**.
#### How to play
**`THIS IS A DEMO MADE TO TEST THE CONTROLLER FUNCTIONALITIES WITH SDL, KEYBOARD WON'T WORK`**  
The player can rotate the cannon loaded with the Booble using the directional buttons, and change its colour using RB and LB. After directing the cannon towards the target, the player can select the colour of the Bobble and shoot the targets using the A button. If the colour matches, the player scores points, whereas if it doesn’t, he loses points. 
The number of lives per game is 3. The lives can be lost by letting the spawned Bobbles fall to the ground.
#### Game architecture
The only instance present in the main is the Application. The whole game logic gets handled internally.    
The player can choose in runtime whether to play in single-player or multiplayer from the main menu. Based on the selection, the game initializes the correct map and everything that depends on it, and of course the right number of players.  
All the objects present in the implementation have an Update and a draw function, that gets called in the Application class.  
The Application’s Update keeps looping all the components’ updates and then proceeds to render the objects. The map takes care of the spawner, the score texts, the background, and the collisions with both Bobbles and walls. The Player handles the Bobble’s vector direction (and its normalization), as well as its destruction and respawn.   
The Win/Lose condition is given by the number of lives that the player has. If that number reaches 0, the game is considered over and exits the loop freeing the occupied memory.  

## Technologies:
- C/C++
- SDL2
- SDL2_image-2.0.1
- SDL2_mixer-2.0.4
- SDL2_ttf-2.0.15

