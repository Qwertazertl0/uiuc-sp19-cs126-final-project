#include "audioEngine.h"
#include <iostream>

AudioEngine::AudioEngine() {
  engine.init();
  bgm.load(gameBgmPath.c_str());
  bgm.setLooping(true);
  mouseover.load(mouseoverSoundPath.c_str());

  engine.play(bgm);
}

AudioEngine::~AudioEngine() {
  engine.fadeGlobalVolume(0, 1);
  engine.deinit();
}

void AudioEngine::playMouseOver() {
  engine.play(mouseover, 2.0f);
}
