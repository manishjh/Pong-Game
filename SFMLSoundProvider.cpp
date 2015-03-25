#include "stdafx.h"
#include "SFMLSoundProvider.h"
#include "SoundFileCache.h"

SFMLSoundProvider::SFMLSoundProvider() : _currentSongName("")
{
}

void SFMLSoundProvider::PlaySound(std::string filename)
{
	int availChannel = -1;

	for (int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		if (_currentSounds[i].getStatus() != sf::Sound::Playing)
		{
			availChannel = i;
			break;
		}
	}

	//if all sound channels are in use, do nothing for now
	if (availChannel != -1)
	{
		try
		{
			_currentSounds[availChannel] = _soundFileCache.GetSound(filename);
			_currentSounds[availChannel].play();
		}
		catch (SoundNotFoundExeption& snfe)
		{
			// Currently, this will simply mean nothing happens if an error occurs
		}
	}
	
}

void SFMLSoundProvider::PlaySong(std::string filename, bool looping)
{
	sf::Music * currentSong;
	try
	{
		currentSong = _soundFileCache.GetSong(filename);
	}
	catch (SoundNotFoundException&)
	{
		return;
	}

	if (_currentSongName != "")
	{
		try
		{
			sf::Music* priorSong = _soundFileCache.GetSong(_currentSongName);
			if (priorSong->getStatus() != sf::Sound::Stopped)
			{
				priorSong->stop();
			}
		}
		catch (SoundNotFoundExeception&)
		{
		
		}

		_currentSongName = filename;
		currentSong->setLoop(looping);
		currentSong->play();

	}
}

void SFMLSoundProvider::StopAllSounds()
{
	for (int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		_currentSounds[i].stop();
	}

	if (_currentSongName != "")
	{
		sf::Music * currentSong = _soundFileCache.GetSong(_currentSongName);
		if (currentSong->getStatus() == sf::Sound::Playing)
		{
			currentSong->stop();
		}
	}
}

bool SFMLSoundProvider::IsSoundPlaying()
{
	for (int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		if (_currentSounds[i].getStatus() == sf::Sound::Playing)
			return true;
	}
	return false;
}

bool SFMLSoundProvider::IsSongPlaying()
{
	if (_currentSongName != "")
	{
		return _soundFileCache.GetSong(_currentSongName)->GetStatus() == sf::Music::Playing;
	}
	return false;
}