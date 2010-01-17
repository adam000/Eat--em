/******************************************************\
|This file and its contents ©Copyright 2008 Adam Hintz |
|and Alastair Lynn. You may not redistribute or use    |
|parts or the whole of this code without our express   |
|written permission. All rights reserved.              |
\******************************************************/

#include "eatem.h"
#include "drawobject.h"
#include "aialgorithm.h"

bool blinky_moving = false;
bool pinky_moving = false;
bool inky_moving = false;
bool clyde_moving = false;
bool on_course = false;

namespace Ai
{

void a_star(int loc_x, int loc_y, int dest_x, int dest_y, bool run_to)
{
	char ghost_move [SCREENW] [SCREENH];
	for (int j = 0; j < SCREENH; j++)
	{
		for (int i = 0; i < SCREENW; i++)
		{
			
		}
	}
	//calculate a* pathfinding, changing the ghost direction and having them move in that direction
	//Set up coasting for ghosts - when they come to a junction, recalculate
}

void implement()
{
	
}

void blinky_move(int x_pac_quad, int y_pac_quad)
{
	if (blinky_moving != true)
	{
		if(g_blinky.status == ST_BLINKY)	//alive, not afraid
		{
			a_star(g_blinky.x, g_blinky.y, pacman.x, pacman.y, true);
		} else
		{
			if(g_blinky.status == ST_AFRAID)	//afraid
			{
				int x_quad;
				int y_quad;
				for (int z = 1; z <= 4; z++)
				{
					if (g_clyde.x < SCREENW / z)
					{
						x_quad = z;
					}
					if (g_clyde.y < SCREENH / z)
					{
						y_quad = z;
					}
				}
			}
		}
	}
}

void pinky_move(int x_pac_quad, int y_pac_quad)	// perhaps these can all be merged into one, as with LOS?
{
	if (pinky_moving != true)
	{
		if(g_pinky.status == ST_PINKY)	//alive, not afraid
		{
			a_star(g_pinky.x, g_pinky.y, pacman.x, pacman.y, true);
		} else
		{
			if(g_pinky.status == ST_AFRAID)	//afraid
			{
				int x_quad;
				int y_quad;
				for (int z = 1; z <= 4; z++)
				{
					if (g_pinky.x < SCREENW / z)
					{
						x_quad = z;
					}
					if (g_pinky.y < SCREENH / z)
					{
						y_quad = z;
					}
				}
			}
		}
	}
}

void inky_move(int x_pac_quad, int y_pac_quad)	//has possibly incorrect algorithm
{
	if (inky_moving != true)
	{
		if(g_inky.status == ST_INKY)	//alive, not afraid
		{
			a_star(g_inky.x, g_inky.y, pacman.x, pacman.y, true);
		} else
		{
			if(g_inky.status == ST_AFRAID)	//afraid
			{
				int x_diff = g_inky.x - pacman.x;
				int y_diff = g_inky.y - pacman.y;
				int x_dir;
				int y_dir;
				if (x_diff > 0)
				{
					x_dir = -1;
					g_inky.direction = ST_LEFT;
					on_course = true;
				} else
				{
					if (x_diff < 0)
					{
						x_dir = 1;
						g_inky.direction = ST_RIGHT;
						on_course = true;
					} else
					{
						//LOS code should have run
						problem (134);
					}
				}
				if (y_diff > 0)
				{
					y_dir = -1;
					g_inky.direction = ST_DOWN;
					on_course = true;
				} else
				{
					if (y_diff < 0)
					{
						y_dir = 1;
						g_inky.direction = ST_UP;
						on_course = true;
					} else
					{
						//LOS code should have run
						problem (133);
					}
				}
				if (x_diff * x_diff >= y_diff * y_diff)		//There's a bigger gap in xs than ys, go via x
				{
					Ai::a_star(g_clyde.x, g_clyde.y, 6, SCREENH - 6, false);
						//temp run telling them to go to corner
				} else		//There's a bigger gap in ys than xs, go via y
				{
					Ai::a_star(g_clyde.x, g_clyde.y, 6, SCREENH - 6, false);
						//temp run telling them to go to corner
				}
			}
		}
	}
}

void clyde_move(int x_pac_quad, int y_pac_quad)	//has correct algorithm
{
	if (clyde_moving != true)
	{
		if(g_clyde.status == ST_CLYDE)	//alive, not afraid
		{
			a_star(g_clyde.x, g_clyde.y, g_clyde.x, g_clyde.y, true);
		} else
		{
			if (g_clyde.status == ST_AFRAID)	//afraid
			{
				//the ghosts should find the direction that Pacman is coming from and go the other way
				Ai::a_star(g_clyde.x, g_clyde.y, 6, SCREENH - 6, false);	//temp run telling them to go to corner
			}
		}
	}
}

void encompassing()
{
	int x_quad;
	int y_quad;
	for (int z = 1; z <= 4; z++)
	{
		if (pacman.x < SCREENW / z)
		{
			x_quad = z;
		}
		if (pacman.y < SCREENH / z)
		{
			y_quad = z;
		}
	}
	g_blinky.line_of_sight();
	g_pinky.line_of_sight();
	g_inky.line_of_sight();
	g_clyde.line_of_sight();
	//blinky_move(int x_quad, int y_quad);
	//pinky_move(int x_quad, int y_quad);
	//inky_move(int x_quad, int y_quad);
	//clyde_move(int x_quad, int y_quad);
}

}