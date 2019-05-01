#include "audioEngine.h"
#include <iostream>

AudioEngine::AudioEngine() {
  engine.init();
  bgm.load(gameBgmPath.c_str());
  bgm.setLooping(true);
  mouseover.load(mouseoverSoundPath.c_str());
  wJump.load(wJumpSoundPath.c_str());
  spaceJump.load(spaceJumpSoundPath.c_str());

  auto handle = engine.play(bgm);
  engine.setProtectVoice(handle, true);
}

AudioEngine::~AudioEngine() {
  engine.fadeGlobalVolume(0, 1);
  engine.deinit();
}

void AudioEngine::playMouseOver() {
  engine.play(mouseover, mouseOverVolume);
}

void AudioEngine::setVolume(float vol) {
  engine.setGlobalVolume(vol);
}

void AudioEngine::playJump(char key) {
  if (key == ' ') {
    engine.play(wJump, wJumpVolume);
  } else if (key == 'w') {
    if (engine.getActiveVoiceCount() < voiceLimit) 
      engine.play(spaceJump, spaceJumpVolume);
  }
}
