#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_wavstream.h"
#include <string>

const std::string gameBgmPath = "./data/audio/gameBgm.wav";
const std::string mouseoverSoundPath = "./data/audio/mouseover2.wav";
const std::string wJumpSoundPath = "./data/audio/jump1.wav";
const std::string spaceJumpSoundPath = "./data/audio/jump2.wav";
const int voiceLimit = 10;
const float mouseOverVolume = 2.5f;
const float wJumpVolume = 0.1f;
const float spaceJumpVolume = 0.1f;

class AudioEngine {
		SoLoud::Soloud engine;
    SoLoud::WavStream bgm;
    SoLoud::Wav mouseover;
    SoLoud::Wav wJump;
    SoLoud::Wav spaceJump;
	public:
		AudioEngine();
		~AudioEngine();
    void playMouseOver();
    void playJump(char key);
    void setVolume(float vol);
};