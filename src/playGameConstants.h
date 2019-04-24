#pragma once
#include "Box2D/Box2D.h"

//Box2D world physics solver parameters
const float timeStep = 1.0f / 60.0f;
const int velocityIterations = 10;
const int positionIterations = 8;

//World and Dot physical constants
const b2Vec2 gravity(0.0f, -80.0f);
const float dotRadius = 1.0f;
const float dotDensity = 0.3f;
const float dotFriction = 0.0f;
const float dotHorVelDampFactor = 0.96f;

//Dot graphics constants
const int numFadeCircles = 15;
const float dotDrawRadius = 40.0f;
const float fadeRadiusShrinkage = 20.0f;

//Static body constants
const int groundOffset = 20;

//Camera constants
const int cameraPanDist = 400; // in pixels
const int numScreenWidths = 3;
const int screenWidthMeters = 36;
const int screenHeightMeters = 24;

//Miscellaneous
const float meterInPixels = 40.0f; //Changing this may require changes to some constants above
const std::string playGameBgPath = "graphics/gameBackground3.jpg";