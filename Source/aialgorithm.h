/******************************************************\
|This file and its contents ©Copyright 2008 Adam Hintz |
|and Alastair Lynn. You may not redistribute or use    |
|parts or the whole of this code without our express   |
|written permission. All rights reserved.              |
\******************************************************/

#ifndef __included_aialgorithm_h
#define __included_aialgorithm_h

#include "eatem.h"

extern bool blinky_moving;
extern bool pinky_moving;
extern bool inky_moving;
extern bool clyde_moving;

namespace Ai
{

void a_star(int loc_x, int loc_y, int dest_x, int dest_y, bool run_to);
void implement();
void blinky_move(int x_pac_quad, int y_pac_quad);
void pinky_move(int x_pac_quad, int y_pac_quad);
void inky_move(int x_pac_quad, int y_pac_quad);
void clyde_move(int x_pac_quad, int y_pac_quad);
void encompassing();		//temporary name, should change when I know what this means in the project

}

#endif