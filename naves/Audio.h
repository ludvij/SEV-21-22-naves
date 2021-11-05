#pragma once


#include <iostream> 
#include <string>  

#include <SDL.h>
#include <SDL_mixer.h> // libreria de audio 

class Audio
{
public:
	Audio(std::string filename, bool loop);
	~Audio(); //destructor 
	void play();
	bool loop;
private:
	Mix_Music* mix; // Lib mixer 
	SDL_AudioSpec wavSpec; // Lib SDL Standard 
	Uint32 wavLength;
	Uint8* wavBuffer;
	SDL_AudioDeviceID deviceId;
};

