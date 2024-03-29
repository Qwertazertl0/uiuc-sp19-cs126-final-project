# Development Log (4/7/19 -- 5/1/19)

This log maintains a list of current and achieved objectives throughout the development of the project "DOT".

Minimum Viable Product:
 * A smooth little platformer with music, graphically pleasing, and with one demo scroller level.

## Reach objectives and ideas for future development
 * Start Menu:
	* Smooth transitions

 * Issues and improvements:
	* Framerate problems and inconsistent crackling in audio?
		* Current workaround: set framerate low to 30 fps
	* Slow state creation; need to create once and "store" the state
		* Note: It's not really *that* slow, but it would be better to not make a new state every time

 * Game:
	* Add slow particle drift to background

## Implemented
 * Dot game physics at acceptable levels
	* Camera scrolling implemented (background at half-pace)
	* Platforms added, dot reset and jumping finalized
	* Home button and fading controls message added
 * Start menu complete for minimum viable product:
	* About page finished
	* Options: Volume control slider and double jump limit toggle
	* Start and quit functionality
 * Audio engine and particle system up and running

## Weekly Logs

### April 29th - May 1st:
 * __Finishing touches__
	* Added fading controls to the game screen
	* Volume bar position renders correctly when returning to home screen
	* Added extra function in audio engine to play extra sounds if needed
	* Resolved unexpected numerical errors crashing application when minimized

### April 21th - April 28th:
 * __Dot Physics__
	* Modified the dot left and right movements be more complex and have slightly more natural platform movements
	* Jumping glitch is fixed, but will allow dot to "climb" up vertical surfaces which is honestly ok
	* Double jumping added; isInAir() fixed for axis-aligned surfaces

 * __Game World__
	* Added static body class to help generate all the platforms
	* Having just one platform already makes the init kind of slow; init in ofApp::setup()?
	* Added return to start menu button
	* Dot resets upon falling irrecoverably into gap
	* All platforms added

 * __Start Menu__
	* Added about text
	* Added volume control and jumping toggles to the options page

### April 14th - April 20th:
 * __Dot aesthetics__
	* Did a fair amount of research on fbos. The dot trail was getting glitchy and slow so the better solution was to keep track of previous positions.

 * __Start Menu__
	* Created clickable class to model buttons and act as transitions
	* Added title screen and menus buttons (required several hours of tedious Photoshop and pixel measurements)
	* Linked start and quit buttons to respective functionalities as well as about and options (which still need content)
	* Basic particle system implemented; needs balancing
		* Particle system improved to handle many particles and automatic generation
		* However, the distribution of random generation may need to be improved because sometimes dense areas of particles are generated

 * __Icon__
	* Added an icon for the application (and a resource.h file). This required(?) that I change the target subsystem from console to windows. I do not know if this will cause later issues.

 * __Audio__
	* Setup basic audio engine with a background music loop
	* Added start menu mouseover sound effect

### April 7th - April 13th:

 * __Working with ofxBox2D__
    * Severe issues with linker being unable to find the Box2D.h file (not an include issue)
    * Potential issue may be the Windows SDK version, but no solution could be found
    * Will likely not use this addon after all

 * __Testing SoLoud__
    * Had difficulty understanding how to incorporate external library with project structure, but managed to get everything linked up
    * Demos demonstrate the flexibility and ease of use for the SoLoud audio engine; I have created a simple example application myself to understand how to get audio to play. It required the use of SDL2 as a "back-end" (see documentation), but this library will be very important to firing sounds easily from the oF application.
    
 * __Exploring OpenGL__
    * Found a YouTube channel (TheChernoProject) with a series dedicated to OpenGL
    * Tested basic functions in personal test application, should not be difficult to use, given that it is part of the oF core.

 * __Box2D library__
    * Will be using the Box2D library rather than the addon. It is well-documented and seems very powerful.
    
 * __Other__
    * Decided to model application as a finite state machine to move from screen to screen.
    * Separated out audio into its own engine class, will work on it after game physics implemented
