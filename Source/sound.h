#ifndef __included_sound_h
#define __included_sound_h

#include <string>

namespace Sound
{

void play ( const std::string& sound );
void music ( const std::string& music );
void stopmusic ();

}

#endif