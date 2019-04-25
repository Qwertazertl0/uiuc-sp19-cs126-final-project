#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_wavstream.h"
#include <string>

const std::string gameBgmPath = "./data/audio/gameBgm.wav";
const std::string mouseoverSoundPath = "./data/audio/mouseover2.wav";

class AudioEngine {
		SoLoud::Soloud engine;
    SoLoud::WavStream bgm;
    SoLoud::Wav mouseover;
	public:
		AudioEngine();
		~AudioEngine();
    void playMouseOver();
    void setVolume(float vol);
};