/******************************************************\
|This file and its contents ©Copyright 2008 Adam Hintz |
|and Alastair Lynn. You may not redistribute or use    |
|parts or the whole of this code without our express   |
|written permission. All rights reserved.              |
\******************************************************/

#include "file_manager.h"

static FileManager* rfm = NULL;

#ifdef __MACH__
extern "C" const char* resourcePath ();
#endif

FileManager::FileManager ( const std::string& dir )
: root(dir)
{
}

FileManager::~FileManager ()
{
}

FileManager* FileManager::GetSingleton ()
{
	if (!rfm)
	{
		std::string root;
#ifdef __MACH__
		root = resourcePath();
		root.push_back('/');
#elif defined(WIN32)
		root = ".\\";
#else
		root = "./";
#endif
		rfm = new FileManager ( root );
		assert(rfm);
	}
	return rfm;
}

SDL_RWops* FileManager::OpenFile ( const std::string& file )
{
	SDL_RWops* ops = SDL_RWFromFile((root + file).c_str(), "rb");
	if (!ops)
	{
		// printf("Failed to open file '%s' - full path: %s\n", file.c_str(), (root + file).c_str());
		return NULL;
	}
	return ops;
}
