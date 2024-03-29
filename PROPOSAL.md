# CS 126 SP19 - Final Project Proposal

**DOT: A Visual Experience** by Maxwell Jong (Qwertazertl0)

## Overview
The project will be a game centered around the theme of a dot, as per the title of the program, **DOT**. The aim of the project is to create a minimalist and aesthetic game experience complete with sound. The user will control a dot, the central character, in a platform environment. Movements will be simple, intuitive, and well-paced.

While somewhat simple in its core functionality, the motto of this project will be detail. I hope to make this game visually appealing with excellent UI/UX.
  
## Details
The project will be an openFrameworks application running in a windowed application. The user will see a basic menu with a title, an option to play the game, and a button to display information about the program and any external music and graphics I may have used. The game itself will be in a 2d environment with hard frictional polygonal surfaces for the dot roll and jump around on. The current dot design includes a fading trail. The user controls the dot with basic commands left, right, and jump, as well a double jump motion only available once while not in contact with any surface. Music will play while the program is running.

Time-permitting, and in no particular order, as many of the following will be implemented:
* Add a settings screen from menu (adjust volume, change skin/color palette, control sensitivity)
* Allow user to load their own music (process to locate strong beats)
* Add visually appealing menu art
* Include some sort of timer or gauge for playing time/level progress/score
* Add texture/gradient/glow to the environment so it doesn't look flat
* Create a story/game scenario for the dot (E.g. "You are a dot...")

## Libraries and Resources
The following libraries are integral to the project:
* [__SoLoud__](http://sol.gfxile.net/soloud/index.html): Game audio engine for "fire-and-forget" sounds
* [__Box2D__](https://github.com/erincatto/Box2D): Physics engine for rigid-body 2D environments
