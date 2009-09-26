/******************************************************\
|This file and its contents ©Copyright 2008 Adam Hintz |
|and Alastair Lynn. You may not redistribute or use    |
|parts or the whole of this code without our express   |
|written permission. All rights reserved.              |
\******************************************************/

#ifndef __included_file_manager_h
#define __included_file_manager_h

#include <string>
#include <SDL/SDL.h>

class FileManager
{
	private:
	std::string root;
	FileManager ( const std::string& dir );
	~FileManager ();
	public:
	static FileManager* GetSingleton ();
	SDL_RWops* OpenFile ( const std::string& name );
};

#define FM FileManager::GetSingleton()

#endif
