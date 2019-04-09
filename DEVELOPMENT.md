# Development Log (4/7/19 -- Present)

This log maintains a list of current and achieved objectives throughout the development of the project "DOT".

## Current Objectives
 * Create screen-to-screen states and transitions and implement all outermost attributes (windows initialization, etc.)
 * Create basic "room/level" and implement basic 2D collision physics for player
 
## Already Implemented
 * No implementation yet

## Weekly Logs
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
