# ENGR103 Game
# Author
Raymond Cen

## What is the game?

### Cyclone Replica

#### Game Description

This game is a replica of the popular arcade game, Cyclone. The user must flip the switch for the game to start. The game will play a pattern that sets all of the pixels to red, orange, yellow, then green. Then a random pixel will be set to green. Then a pattern will begin where a blue pixel will start to go through all of the pixels and the user has to attempt to press the A or B button when the blue pixel is on the green pixel. If the user succeeds then it will blink a green pixel pattern along with a sound signaling the completion of that level and the pattern will go faster next level with a total of 5 levels. If the user fails they are presented with a red pixel pattern and a lower pitch sound and is reset to the first level. During either the green or red patterns the user can click either the A or B button to either go onto the next level or be resetted back to the first level depending if you won or failed. If the user completes all of the leves then a rainbow pattern will play. The user can then turn off the game or press either the A or B button to restart the entire game.

#### Input/Output Definition Sheet

##### Input
Button A and Button B
Switch
##### Output
###### NeoPixels
Used to signal start of the game
Used to signal end of a level
Used to signal end of game
###### Sound
Used to signal passing a level or failing it
