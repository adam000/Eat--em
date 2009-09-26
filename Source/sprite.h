/******************************************************\
|This file and its contents ©Copyright 2008 Adam Hintz |
|and Alastair Lynn. You may not redistribute or use    |
|parts or the whole of this code without our express   |
|written permission. All rights reserved.              |
\******************************************************/

#ifndef __included_sprite_h
#define __included_sprite_h

#include <string>

namespace Sprite
{

void load ( const std::string& name, const std::string& sourcefile );
void load_set ( const std::string& setfile );
bool loaded ( const std::string& sprite );
void draw ( const std::string& sprite, float i, float j, float mw, float mh, float rotz, bool resize );

}

#endif