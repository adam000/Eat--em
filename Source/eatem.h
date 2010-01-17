/******************************************************\
|This file and its contents ©Copyright 2008 Adam Hintz |
|and Alastair Lynn. You may not redistribute or use    |
|parts or the whole of this code without our express   |
|written permission. All rights reserved.              |
\******************************************************/

#ifndef __included_eatem_h
#define __included_eatem_h

////////////////////////
//Libraries////////////
//////////////////////
#include <iostream>
#include <fstream>
#include <math.h>
#include "SDL.h"
#include "SDL_OpenGL.h"
#include "opengl/glu.h"
#include <stdio.h>
#include <stdlib.h>
//#include <sys/stat.h>	what does this do?
#include "SDL_image/SDL_image.h"

using namespace std;

#ifndef _BIG_ENDIAN_
#define ENDIAN 1
#else
#define ENDIAN 0
#endif

////////////////////////
//Defined Functions////
//////////////////////
extern ofstream fileout;
void wait(float seconds);
void draw_scene();
Uint32 game_timer(Uint32 interval, void* param);
void problem(int errornum);

////////////////////////
//Variables////////////
//////////////////////

//CONSTANTS
const GLfloat SCREENTH = 73.125;		//true height (in units)
const GLfloat SCREENTW = 117;			//true width (in units)
const int RUN_GAME_LOOP = 1;
const int GHOST_TIME_EXPIRE_1 = 2;
const int GHOST_TIME_EXPIRE_2 = 3;
const int SCREENH = 57;					//game screen height (in units)
const int SCREENW = 113;				//game screen width (in units)
const int SCREENGH = 8;
const int SCREENGW = 16;
const bool mute = false;

//INTEGERS
extern int timer_speed;
extern int score;
extern int lives;
extern int num_pellets;
extern int ghosts_eaten;

//UNSIGNED INTEGERS
extern unsigned int vitamin_time;

//FLOATS

//DOUBLES
extern double times_per_sec;

//CHARACTERS
extern char last_press;

//ARRAYS

//BOOLEAN
extern bool done;
extern bool stop;
extern bool first;
extern bool menu_quit;
extern bool inverted_axes;
extern bool first_draw;
extern bool pellet_eaten;
extern bool change_key;
extern bool other_time;
extern bool reset;

//SDL TIMER
extern SDL_TimerID timer;
extern Uint32 ghost_afraid_timer(Uint32 interval, void* param);

////////////////////////
//Classes//////////////
//////////////////////

////////////////////////
//Structs//////////////
//////////////////////
/*typedef struct
{
	GLfloat texture1 [2];
	GLfloat vertex1 [2];
	GLfloat texture2 [2];
	GLfloat vertex2 [2];
	GLfloat texture3 [2];
	GLfloat vertex3 [2];
	GLfloat texture4 [2];
	GLfloat vertex4 [2];
} texture2vertex;

extern texture2vertex tex;*/

#endif