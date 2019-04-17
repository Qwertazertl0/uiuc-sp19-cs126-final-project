#include "audioEngine.h"
#include <iostream>

AudioEngine::AudioEngine() {
  engine.init();
  bgm.load(gameBgmPath.c_str());
  bgm.setLooping(true);
  mouseover.load(mouseoverSoundPath.c_str());

  std::cout << engine.play(bgm) << std::endl;
}

AudioEngine::~AudioEngine() {
  engine.fadeGlobalVolume(0, 1);
  engine.deinit();
}
