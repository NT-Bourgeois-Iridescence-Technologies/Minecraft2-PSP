#include "MusicManager.h"

#include <stdlib.h>
#include <time.h>
#include <string>
#include <mclib/core/Client.h>

namespace Minecraft::Audio {
	RandomMusicGenerator::RandomMusicGenerator()
	{
		timeUntilNext = 0;
		snd = NULL;
	}
	RandomMusicGenerator::~RandomMusicGenerator()
	{

	}
	void RandomMusicGenerator::Init()
	{
		srand(time(NULL));
		timeUntilNext = rand() % 800 + 201;
	}
	void RandomMusicGenerator::Cleanup()
	{
		if(snd != NULL){
			oslStopSound(snd);
		}
	}
	void RandomMusicGenerator::FixedUpdate()
	{
		timeUntilNext--;
		if (timeUntilNext <= 0) {
			//PLAY RANDOM
			
			if (snd != NULL) {
				oslStopSound(snd);
			}

			int choice = rand() % 4;

			int maxLim = 0;
			
			std::string path = "./assets/sounds/music/game/";

			switch (choice) {
			case 0: {
				path += "hal";
				maxLim = 4;
				break;
			}
			case 1: {
				path += "nuance";
				maxLim = 2;
				break;
			}
			case 2: {
				path += "calm";
				maxLim = 3;
				break;
			}
			case 3: {
				path += "piano";
				maxLim = 3;
			}

			}

			int actualChoice = 1 + rand() % maxLim;
			path += std::to_string(actualChoice);
			path += ".bgm";

			snd = oslLoadSoundFile(path.c_str(), OSL_FMT_STREAM); //STREAM!
			g_AudioManager.PlayMusic(snd);

			srand(time(NULL));
			timeUntilNext = 6001 + rand() % 2000;
		}
	}
}