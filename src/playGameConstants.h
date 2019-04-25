#pragma once
#include "Box2D/Box2D.h"

//Miscellaneous
const float pixelsPerMeter = 40.0f; //Changing this may require changes to some constants above
const std::string playGameBgPath = "graphics/gameBackground3.jpg";
const std::string homeNeutralPath = "graphics/homeNeutral.png";
const std::string homeHoverPath = "graphics/homeHover.png";
const int homeButtonSideLength = 60;
const int cornerOffset = 15;
const ofColor themePurple = ofColor(252, 35, 255);
const int dotResetHeight = -15;

//Box2D world physics solver parameters
const float timeStep = 1.0f / 30.0f;
const int velocityIterations = 10;
const int positionIterations = 8;

//World and Dot physical constants
const b2Vec2 gravity(0.0f, -40.0f);
const float dotRadius = 0.75f;
const float dotDensity = 0.3f;
const float dotFriction = 0.0f;
const float dotHorVelDampFactor = 0.45f;
const float inAirHorVelDampFactor = 0.96f;

//Dot dynamics constants
const float maxHorSpeed = 20;
const float horInc = 6.0f;
const float maxVertSpeed = 30;
const float airborneYDiffContactLimit = 0.1f;

//Dot graphics constants
const int numFadeCircles = 15;
const float dotDrawRadius = dotRadius * pixelsPerMeter;
const float fadeRadiusShrinkage = 20.0f;

//Static body constants
const int groundOffset = 20;
const int numBodies = 12;
const float bodyWidths[] = {8, 5, 5, 1.5, 1.5, 1.5, 2, 2, 2, 2, 2, 2};
const float bodyHeights[] = {4, 1, 1, 14, 26, 4, 2, 2, 2, 24, 2, 2};
const float bodyCenterX[] = {40, 54, 64, 78, 86, 86, 179, 188, 196, 202, 210, 215};
const float bodyCenterY[] = {2, 14, 8, 7, 23, 2, 1, 12, 6, 24, 10, 1};
const int numGroundPieces = 4;
const float worldEnd = 288;
const float groundBounds[] = {0, 44, 77.25, 78.75, 85.25, 180, 214, worldEnd};

//Camera constants
const float bgRelSpeed = 0.75;
const int cameraPanDist = 200; // in pixels
const int numScreenWidths = 8;
const int screenWidthMeters = 36;
const int screenHeightMeters = 24;