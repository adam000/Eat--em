#include "sound.h"
#include <SDL_mixer/SDL_mixer.h>
#include "file_manager.h"
#include <map>

/*
 _________________________________________________________________________________ 
/  ____  _______        ___    ____  _____    ___  _____   _____ _   _ _____      \
| | __ )| ____\ \      / / \  |  _ \| ____|  / _ \|  ___| |_   _| | | | ____|     |
| |  _ \|  _|  \ \ /\ / / _ \ | |_) |  _|   | | | | |_      | | | |_| |  _|       |
| | |_) | |___  \ V  V / ___ \|  _ <| |___  | |_| |  _|     | | |  _  | |___      |
| |____/|_____|  \_/\_/_/   \_\_| \_\_____|  \___/|_|       |_| |_| |_|_____|     |
|                                                                                 |
|  _  _____ _     _     _____ ____     ____ ___ ____      _    _____ _____ _____  |
| | |/ /_ _| |   | |   | ____|  _ \   / ___|_ _|  _ \    / \  |  ___|  ___| ____| |
| | ' / | || |   | |   |  _| | |_) | | |  _ | || |_) |  / _ \ | |_  | |_  |  _|   |
| | . \ | || |___| |___| |___|  _ <  | |_| || ||  _ <  / ___ \|  _| |  _| | |___  |
| |_|\_\___|_____|_____|_____|_| \_\  \____|___|_| \_\/_/   \_\_|   |_|   |_____| |
\                                                                                 /
 --------------------------------------------------------------------------------- 
          \
           \
            \          __---__
                    _-       /--______
               __--( /     \ )XXXXXXXXXXX\v.
             .-XXX(   O   O  )XXXXXXXXXXXXXXX-
            /XXX(       U     )        XXXXXXX\
          /XXXXX(              )--_  XXXXXXXXXXX\
         /XXXXX/ (      O     )   XXXXXX   \XXXXX\
         XXXXX/   /            XXXXXX   \__ \XXXXX
         XXXXXX__/          XXXXXX         \__---->
 ---___  XXX__/          XXXXXX      \__         /
   \-  --__/   ___/\  XXXXXX            /  ___--/=
    \-\    ___/    XXXXXX              '--- XXXXXX
       \-\/XXX\ XXXXXX                      /XXXXX
         \XXXXXXXXX   \                    /XXXXX/
          \XXXXXX      >                 _/XXXXX/
            \XXXXX--__/              __-- XXXX/
             -XXXXXXXX---------------  XXXXXX-
                \XXXXXXXXXXXXXXXXXXXXXXXXXX/
                  ""VXXXXXXXXXXXXXXXXXXV""
				  
				  */

namespace
{

bool initted = false;
Mix_Music* current_music = NULL;

void init ()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024 * 8);
	Mix_AllocateChannels(32);
	initted = true;
}

std::map<std::string, Mix_Chunk*> chunks;

}

namespace Sound
{

void play ( const std::string& sound )
{
	if (!initted)
		init();
	Mix_Chunk* cnk;
	std::map<std::string, Mix_Chunk*>::iterator iter = chunks.find(sound);
	if (iter == chunks.end())
	{
		// load the sound
		SDL_RWops* ops = FM->OpenFile(sound + ".wav");
		cnk = Mix_LoadWAV_RW(ops, 1);
		chunks[sound] = cnk;
	}
	else
	{
		cnk = iter->second;
	}
	if (cnk)
	{
		Mix_PlayChannel(-1, cnk, 0);
	}
}

void music ( const std::string& music )
{
	if (!initted)
		init();
	if (current_music)
		stopmusic();
	SDL_RWops* ops = FM->OpenFile(music + ".wav");
	if (!ops)
	{
		ops = FM->OpenFile(music + ".ogg");
	}
	current_music = Mix_LoadMUS_RW(ops);
	Mix_PlayMusic(current_music, -1);
}

void stopmusic ()
{
	if (!initted)
		return;
	if (current_music)
	{
		Mix_FreeMusic(current_music);
		Mix_HaltMusic();
	}
	current_music = NULL;
}

}

