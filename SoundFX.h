#ifndef SOUNDFX_H_
#define SOUNDFX_H_

#include <string>
#include <SDL2/SDL_mixer.h>
#include <map>
#include <iostream>

class SoundFXController
{
  public:
	void playClip(std::string soundFile)
	{
		// Stop any currently playing music
		if (Mix_PlayingMusic())
		{
			Mix_HaltMusic();
		}
		
		// Try to load and play as music (for theme.wav)
		Mix_Music* music = Mix_LoadMUS(soundFile.c_str());
		if (music != nullptr)
		{
			// Check if this is the theme music (should loop)
			int loops = (soundFile.find("theme") != std::string::npos) ? -1 : 0;
			Mix_PlayMusic(music, loops);  // -1 = loop forever, 0 = play once
			m_musicMap[soundFile] = music;
		}
		else
		{
			// Try to load as chunk (sound effect)
			Mix_Chunk* chunk = Mix_LoadWAV(soundFile.c_str());
			if (chunk != nullptr)
			{
				Mix_PlayChannel(-1, chunk, 0);
				m_chunkMap[soundFile] = chunk;
			}
			else
			{
				std::cerr << "Cannot load sound: " << soundFile << " - " << Mix_GetError() << std::endl;
			}
		}
	}

	void abortClip()
	{
		if (Mix_PlayingMusic())
		{
			Mix_HaltMusic();
		}
		Mix_HaltChannel(-1);  // Stop all channels
	}

	static SoundFXController& getInstance();

  private:
	std::map<std::string, Mix_Music*> m_musicMap;
	std::map<std::string, Mix_Chunk*> m_chunkMap;

	SoundFXController()
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
			std::cout << "Game will be silent." << std::endl;
		}
	}

	~SoundFXController()
	{
		abortClip();
		for (auto& pair : m_musicMap)
		{
			Mix_FreeMusic(pair.second);
		}
		for (auto& pair : m_chunkMap)
		{
			Mix_FreeChunk(pair.second);
		}
		m_musicMap.clear();
		m_chunkMap.clear();
		Mix_CloseAudio();
	}

	SoundFXController(const SoundFXController&);
	SoundFXController& operator=(const SoundFXController&);
};

  // Meyers singleton pattern
inline SoundFXController& SoundFXController::getInstance()
{
	static SoundFXController instance;
	return instance;
}

inline SoundFXController& SoundFX()
{
	return SoundFXController::getInstance();
}

#endif // SOUNDFX_H_
