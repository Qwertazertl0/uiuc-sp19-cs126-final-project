#include "audioEngine.h"
#include <iostream>

AudioEngine::AudioEngine() {
  engine.init();
  bgm.load(gameBgmPath.c_str());
  bgm.setLooping(true);
  mouseover.load(mouseoverSoundPath.c_str());

  auto handle = engine.play(bgm);
  engine.setProtectVoice(handle, true);
}

AudioEngine::~AudioEngine() {
  engine.fadeGlobalVolume(0, 1);
  engine.deinit();
}

void AudioEngine::playMouseOver() {
  engine.play(mouseover, 2.0f);
}

void AudioEngine::setVolume(float vol) {
  engine.setGlobalVolume(vol);
}
