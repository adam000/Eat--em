/******************************************************\
|This file and its contents ©Copyright 2008 Adam Hintz |
|and Alastair Lynn. You may not redistribute or use    |
|parts or the whole of this code without our express   |
|written permission. All rights reserved.              |
\******************************************************/

#ifndef __included_drawobject_h
#define __included_drawobject_h

#include "eatem.h"
#include "collision.h"

const int SIZE = 6;

const ST BLINKY = "g_blinky.";
const ST PINKY = "g_pinky.";
const ST INKY = "g_inky.";
const ST CLYDE = "g_clyde.";
const ST ST_UP = "_up_";
const ST ST_DOWN = "_dn_";
const ST ST_LEFT = "_lt_";
const ST ST_RIGHT = "_rt_";
const ST ST_BLINKY = "blinky";
const ST ST_PINKY = "pinky";
const ST ST_INKY = "inky";
const ST ST_CLYDE = "clyde";
const ST ST_AFRAID = "afraid_ghost_";
const ST ST_DEAD = "dead_ghost";
const ST ST_0 = "0";
const ST ST_1 = "1";
const ST ST_2 = "2";
const ST ST_3 = "3";
const ST ST_4 = "4";
const ST ST_5 = "5";
const ST ST_6 = "6";
const ST ST_7 = "7";
const ST ST_8 = "8";
const ST ST_9 = "9";

extern int pacrot;
extern int trans_num;

extern bool firstdraw;
extern bool animation;
extern bool afraid_ghosts;

extern char playfield [SCREENW] [SCREENH];
extern char ghostfield [SCREENW] [SCREENH];
extern char ghostrun [SCREENW] [SCREENH];

void draw_playfield();

void setfield(const std::string& playfield_file, char temp_array [SCREENW] [SCREENH]);
void get_control_points();
void displayfield(char temp_array [SCREENW] [SCREENH]);
void draw_pacman();

void draw_pac_trans_down();
void draw_pac_trans_up();

void draw_ghosts();

void draw_score();

ST score_init(int score1);

class entity
{
	public:
	int x;
	int y;
	int next_x;
	int next_y;
};

class pacman_class : public entity
{
	public:
	char collided;
	char col_type;
};

extern pacman_class pacman;

class ghost_class : public entity
{
	public:
	ST direction;
	ST pers_status;
	ST status;
	int distance;
	bool has_los;
	void line_of_sight()
	{
		if (status == pers_status)
		{
			if (x == pacman.x)
			{
				if (y < pacman.y)		//pacman is below
				{
					if (y + 5 == pacman.y)
					{
						pacman_death();
					}
					for (int j = 1; j < SCREENH; j++)
					{
						if (y + j == pacman.y)
						{
							direction = ST_DOWN;
							y++;
							return;
						}
						if (ghostrun [x] [SCREENH - (y + j)] == 'O')
						{
							return;
						}
					}
				} else					//pacman is above
				{
					if (y - 6 == pacman.y)
					{
						pacman_death();
					}
					for (int j = 1; j < SCREENH; j++)
					{
						if (y - j == pacman.y)
						{
							direction = ST_UP;
							y--;
							return;
						}
						if (ghostrun [x - 1] [SCREENH + y - j] == 'O')
						{
							return;
						}
					}
				}
			}
			if (y == pacman.y)
			{
				if (x < pacman.x)		//pacman is to right
				{
					if (x + 6 == pacman.x)
					{
						pacman_death();
					}
					for (int i = 1; i < SCREENW; i++)
					{
						if (x + i == pacman.x)
						{
							direction = ST_RIGHT;
							x++;
							return;
						}
						if (ghostrun [x + i] [y] == 'O')
						{
							return;
						}
					}
				} else					//pacman is to left
				{
					if (x - 5 == pacman.x)
					{
						pacman_death();
					}
					for (int i = 1; i < SCREENW; i++)
					{
						if (x - i == pacman.x)
						{
							direction = ST_LEFT;
							x--;
							return;
						}
						if (ghostrun [x - i] [SCREENH - y + 1] == 'O')
						{
							return;
						}
					}
				}
			}
		}
	}
};

extern ghost_class g_blinky;
extern ghost_class g_pinky;
extern ghost_class g_inky;
extern ghost_class g_clyde;

#endif