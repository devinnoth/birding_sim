# Devin Noth: Final Project - Birding Simulator

My final project is a birding simulator, with the goal to find 1 different bird on each of the 4 stages. 

## How To Play  

### To Build  & Run 
To build, use the command  
```make```  
to create the executable. Then use  
```./final```  
to run the newly created executable. 

### Game Controls  
 - WASD moves the player around the setting
 - The mouse rotates the camera  
**IMPORTANT:** The program locks your mouse into the window, TAB will unlock your mouse and pause the game to stop this.
 - 'e' or 'E' switches between your camera and journal
 - SPACEBAR moves onto the next level once you've successfully taken a photo of the required bird
 - While the camera is equipped, RIGHT MOUSE BUTTON will put you into viewfinder mode
 - Hit RIGHT MOUSE BUTTON while in viewfinder mode to continue zooming in.
 - While in viewfinder mode, hit LEFT MOUSE BUTTON to take a picture.
 - 'f' or 'F' will interact with bird feeders if you are close enough to them
 - ESC will exit the program
 
### Objectives
 - By equipping your journal (hitting E) you can see what bird you are currently searching for.
 - Hints about how to find the specific bird can also be found in the journal.
 - For example: if the journal says the bird often uses feeders, make sure both feeders are filled for the bird to spawn
 - Once you see the bird you're searching for: Equip your camera, use RMB to go to viewfinder mode, make sure you line up the shot and hit LMB to take the picture.
 - After you take the picture, check your journal for a check mark on the page, then hit space to move onto the next bird
 - Complete all 4 stages to beat the game
 
### Other Controls
 Due to my computer having a bad graphics card, I made some graphics limiting/enhacing variables that might be helpful for using this project.
 - 'z' or 'Z' will toggle the lighting on and off
 - 'x' or 'X' will toggle the shadows on and off
 - 'c' or 'C' will turn the lake reflection on and off
 - The up and down arrow keys will increase/decrease the amount of vertexes used to create round surfaces (spheres, cylinders, cones, etc.)
 
If your framerate seems to be hindering your experience, I suggest using these to toggle things

## What to Pay Attention To

### Objects and Textures
 - All objects are models I designed myself in OpenGL. I did not use blender or import any OBJ files.
 - These objects include all the birds, vegetation, handheld objects, birdfeeders, etc.
 - I made custom textures for each of my models. While some of these were just scaling and cropping images, some were actually complicated.
 - I made a custom spawn method with the birds, which cycles through a circular array despawning and spawning different birds on each level based on time.
 - The positioning of the handheld camera and journal works rotates with the player and looks fluid and nice
 
### Graphics
 - I was able to derive the lake reflection graphic from the shadow stencil example. While it is graphics heavy, I'm very happy with how it looks in the scene.
 - I made a flash animation using an overlay and the ambient/diffuse variables.
 - The flash animation can be seen by taking a picture in level 4 (the night-time owl hunt)
 - The custom camera viewfinder overlay was simple but I'm very happy with how it looks.
 - I'm proud of the lighting I derived for each scene, creating a golden hour feeling in the day scene, and a gloomier feelng in the night.
 
### Interactables
 - There are walking boundaries around the setting. Also to simulate wading through water, movement is a quarter speed while within the lake
 - The detection for if the user correctly captured the bird. It could be improved, but I'm still happy with it.
 - The interaction with the birdfeeders is fluid is nice. Especially with the rotating help text that appears
 
## What's Changed / Current Bugs

### Implemented Since Project Review
 - There is now hit detection / movement restriction. You cannot walk outside the boundaries and you are slowed within the lake
 - I added shadows to the rocks that needed them

### Current Known Bugs / Desired features
 - BIGGEST BUG Was that I failed to implement the actual photo taking feature (not due to lack of trying). This sadly affects the journal textures, as there will not be the photo shown even if a successful photo is taken
 - More fauna or objects to the scene
 - Shadows of the trees sometimes don't appear on the path
 
## Used Code Credit

There are detailed comments in different files explaining ways I changed functions from code I derived, but I will summarize them here as well.
 - Shadow functions: I used the stencil shadow method from ex34. I didn't change much from the shadow method, but was able to adapt this into my own reflection method.
 - Shape functions: I used parts of some of this classes original shape functions like sphere and cube, and made my own like cylinders and spheres.
 - Overlay functions: I derived the cockpit overlay function used in an earlier example to understand how to print directly to the screen, I then used this to make my camera viewfinder and shutter animation


