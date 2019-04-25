#pragma once

#include "ofMain.h"
#include <string>

//Miscellaneous graphics
const int logoCircleResolution = 100;
const int logoCircleRadius = 30;
const glm::vec2 logoCirclePos = glm::vec2(375, 170);
const ofColor volumeBarColor = ofColor(252, 35, 255, 100);

//Positioning of buttons/labels in pixels (assumes screen is 1440x960)
const int menuButtonWidth = 433;
const int menuButtonHeight = 96;
const int startYCoord = 450;
const int optionsYCoord = 560;
const int aboutYCoord = 670;
const int quitYCoord = 780;
const int logoCornerOffset = 82;

const int returnWidth = 292;
const int returnHeight = 141;
const int returnXCoord = 574;
const int returnYCoord = 735;

const int aboutTextX = 108;
const int aboutTextY = 126;
const int volTextX = 191;
const int volTextY = 234;
const int volBarX = 587;
const int volBarY = 259;
const int volBarWidth = 644;
const int volBarHeight = 38;
const int jumpLimX = 183;
const int jumpLimY = 488;

const int onOffX = 652;
const int onOffY = 473;
const int onOffWidth = 181;
const int onOffHeight = 110;
const int sliderY = 238;
const int sliderWidth = 40;
const int sliderHeight = 80;
const int sliderDefaultX = 1211;

//Particles constants
const int numInitParticles = 80;
const glm::vec2 initVel(-0.7, -0.14);

//Graphics image paths
const std::string startMenuBgPath = "graphics/start_menu_background4.jpg";
const std::string logoPath = "graphics/dotLogo.png";

const std::string startNeutralPath = "graphics/startNeutral.png";
const std::string startHoverPath = "graphics/startHover.png";
const std::string optionsNeutralPath = "graphics/optionsNeutral.png";
const std::string optionsHoverPath = "graphics/optionsHover.png";
const std::string aboutNeutralPath = "graphics/aboutNeutral.png";
const std::string aboutHoverPath = "graphics/aboutHover.png";
const std::string quitNeutralPath = "graphics/quitNeutral.png";
const ::string quitHoverPath = "graphics/quitHover.png";
const std::string returnNeutralPath = "graphics/backNeutral.png";
const std::string returnHoverPath = "graphics/backHover.png";

const std::string volTextPath = "graphics/volumeText.png";
const std::string volBarPath = "graphics/volumeBar.png";
const std::string sliderPath = "graphics/slider.png";
const std::string jumpLimitPath = "graphics/jumpLimitText.png";
const std::string onNeutralPath = "graphics/onNeutral.png";
const std::string onHoverPath = "graphics/onHover.png";
const std::string offNeutralPath = "graphics/offNeutral.png";
const std::string offHoverPath = "graphics/offHover.png";
const std::string aboutTextPath = "graphics/aboutText.png";