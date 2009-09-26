/******************************************************\
|This file and its contents ©Copyright 2008 Adam Hintz |
|and Alastair Lynn. You may not redistribute or use    |
|parts or the whole of this code without our express   |
|written permission. All rights reserved.              |
\******************************************************/

#ifndef __included_collision_h
#define __included_collision_h

#include "pacman01.h"

bool pacman_collision(int direction);
bool pacman_collision_up(int direction);
bool pacman_collision_down(int direction);
bool pacman_collision_left(int direction);
bool pacman_collision_right(int direction);

void remove_pellet(int x, int y);
void pac_death_anim();
void pacman_death();
void ghost_collision();

typedef std::string ST;

ST closest_ghost();

const int OBJ_SIZE = 6;
const int MOVE_UP = 0;
const int MOVE_DOWN = 1;
const int MOVE_LEFT = 2;
const int MOVE_RIGHT = 3;

extern bool transporting_up;
extern bool next_trans;

#endif