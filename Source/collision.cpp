/******************************************************\
|This file and its contents ©Copyright 2008 Adam Hintz |
|and Alastair Lynn. You may not redistribute or use    |
|parts or the whole of this code without our express   |
|written permission. All rights reserved.              |
\******************************************************/

#include "pacman01.h"
#include "collision.h"
#include "drawobject.h"
#include "sprite.h"
#include "sound.h"

bool transporting_up = false;
bool next_trans = false;

bool pacman_collision(int direction)
{
	ghost_collision();
	bool was_collision;
	switch (direction)
	{
		case (MOVE_UP):
		{
			transporting_up = true;
			was_collision = pacman_collision_up(direction);
			//cout << "'" << pacman.collided << "' @ " << pacman.x << ", " << pacman.next_y << " '" <<
			//	playfield [pacman.x] [pacman.next_y] << "'" << endl;
			
			//display_playfield();
			
			if (was_collision == true)
			{				
				switch (pacman.col_type)
				{
					case ('W'):	//collision is with wall
					{
						return true;
						break;
					}
					case ('p'):	//collision is with pellet
					{
						return false;
						break;
					}
					case ('P'):	//collision is with pacman?
					{
						problem(106);
						break;
					}
					default:
					{
						cout << pacman.col_type << endl;
						problem(107);
						break;
					}
				}
			} else
			{
				pacman.y = pacman.next_y;
			}
			break;
		}
		case (MOVE_DOWN):
		{
			transporting_up = false;
			was_collision = pacman_collision_down(direction);
			//cout << "'" << pacman.collided << "' @ " << pacman.x << ", " << pacman.next_y << " '" <<
			//	playfield [pacman.x] [pacman.next_y] << "'" << endl;
			
			//display_playfield();
			
			if (was_collision == true)
			{				
				switch (pacman.col_type)
				{
					case ('W'):	//collision is with wall
					{
						return true;
						break;
					}
					case ('p'):	//collision is with pellet
					{
						return false;
						break;
					}
					case ('P'):	//collision is with pacman?
					{
						problem(121);
						break;
					}
					default:
					{
						cout << pacman.col_type << endl;
						problem(108);
						break;
					}
				}
			} else
			{
				pacman.y = pacman.next_y;
			}
			break;
		}
		case (MOVE_LEFT):
		{
			was_collision = pacman_collision_left(direction);
			//cout << "'" << pacman.collided << "' @ " << pacman.next_x << ", " << pacman.y << " '" <<
			//	playfield [pacman.next_x] [pacman.y] << "'" << endl;
			
			//display_playfield();
			
			if (was_collision == true)
			{				
				switch (pacman.col_type)
				{
					case ('W'):	//collision is with wall
					{
						return true;
						break;
					}
					case ('p'):	//collision is with pellet
					{
						return false;
						break;
					}
					case ('P'):	//collision is with pacman?
					{
						problem(122);
						break;
					}
					default:
					{
						cout << pacman.col_type << endl;
						problem(109);
						break;
					}
				}
			} else
			{
				pacman.x = pacman.next_x;
			}
			break;
		}
		case (MOVE_RIGHT):
		{
			was_collision = pacman_collision_right(direction);
			//cout << "'" << pacman.collided << "' @ " << pacman.next_x << ", " << pacman.y << " '" <<
			//	playfield [pacman.next_x] [pacman.y] << "'" << endl;
			
			//display_playfield();
			
			if (was_collision == true)
			{				
				switch (pacman.col_type)
				{
					case ('W'):	//collision is with wall
					{
						return true;
						break;
					}
					case ('p'):	//collision is with pellet
					{
						return false;
						break;
					}
					case ('P'):	//collision is with pacman?
					{
						problem(123);
						break;
					}
					default:
					{
						cout << pacman.col_type << endl;
						problem(110);
						break;
					}
				}
			} else
			{
				pacman.x = pacman.next_x;
			}
			break;
		}
		default:
		{
			problem(104);
		}
	}
	return false;
}

bool pacman_collision_up(int direction)
{
	pacman.next_y = pacman.y - 1;
	pacman.collided = ' ';
	pacman.col_type = ' ';
	if (next_trans == true)
	{
		next_trans = false;
		trans_num = 1;
		return false;
	}
	for (int i = 0; i < OBJ_SIZE; i++)
	{
		if (playfield [pacman.x + i - 1] [pacman.next_y] == 'p')
		{
			remove_pellet(pacman.x + i - 1, pacman.next_y);
		}
		switch (playfield [pacman.x + i] [pacman.next_y])
		{
			case (' '):
			{
				break;
			}
			case ('p'):
			{
				break;
			}
			case ('-'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('w'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('e'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('V'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('<'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('>'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('x'):
			{
				num_pellets++;
				score--;
				remove_pellet(pacman.x + i, pacman.next_y);
				vitamin_time = floor(times_per_sec * 15);		//15 seconds of chasing
				break;
			}
			case ('T'):
			{
				if (pacman.x == 53)
				{
					trans_num = 1;
					return false;
				}
				if (pacman.x == 52 && direction == MOVE_RIGHT)
				{
					next_trans = true;
					pacman.col_type = 'W';
					return true;
				}
				if (pacman.x == 54 && direction == MOVE_LEFT)
				{
					next_trans = true;
					pacman.col_type = 'W';
					return true;
				}
				break;
			}
			/*case ('W'):		//shouldn't collide with these
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('E'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('^'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('|'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y];
				pacman.col_type = 'W';
				return true;
				break;
			}*/
			default:
			{
				cout << playfield [pacman.x + i] [pacman.next_y] << endl;
				problem(105);
			}
		}
	}
	return false;
}

bool pacman_collision_down(int direction)
{
	pacman.next_y = pacman.y + 1;
	pacman.collided = ' ';
	pacman.col_type = ' ';
	if (next_trans == true)
	{
		next_trans = false;
		trans_num = 1;
		return false;
	}
	for (int i = 0; i < OBJ_SIZE; i++)
	{
		/*if (playfield [pacman.next_x + i - 2] [pacman.y + 5] == 'p')
		{
			remove_pellet(pacman.next_x + i - 2, pacman.y + 5);
		}*/
		if (playfield [pacman.next_x + i - 1] [pacman.y + 5] == 'p')
		{
			remove_pellet(pacman.next_x + i - 1, pacman.y + 5);
		}
		switch (playfield [pacman.x + i] [pacman.next_y + 5])
		{
			case (' '):
			{
				break;
			}
			case ('p'):
			{
				break;
			}
			case ('-'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y + 5];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('W'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y + 5];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('E'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y + 5];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('^'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y + 5];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('<'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y + 5];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('>'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y + 5];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('x'):
			{
				num_pellets++;
				score--;
				remove_pellet(pacman.x + i, pacman.next_y + 5);
				vitamin_time = floor(times_per_sec * 15);		//15 seconds of chasing
				break;
			}
			case ('T'):
			{
				if (pacman.x = 53)
				{
					trans_num = 1;
					return false;
				}
				if (pacman.x == 52 && direction == MOVE_RIGHT)
				{
					next_trans = true;
					pacman.col_type = 'W';
					return true;
				}
				if (pacman.x == 54 && direction == MOVE_LEFT)
				{
					next_trans = true;
					pacman.col_type = 'W';
					return true;
				}
				
				break;
			}
			/*case ('|'):		//shouldn't collide with these
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y + 5];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('w'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y + 5];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('e'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y + 5];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('V'):
			{
				pacman.collided = playfield [pacman.x + i] [pacman.next_y + 5];
				pacman.col_type = 'W';
				return true;
				break;
			}*/
			default:
			{
				cout << playfield [pacman.x + i] [pacman.next_y + 5] << endl;
				problem(115);
			}
		}
	}
	return false;
}

bool pacman_collision_left(int direction)
{
	pacman.next_x = pacman.x - 1;
	pacman.collided = ' ';
	pacman.col_type = ' ';
	if (playfield [pacman.next_x - 1] [pacman.y + 2] == 'x')
	{
		num_pellets++;
		score--;
		remove_pellet(pacman.next_x - 1, pacman.y + 2);
		vitamin_time = floor(times_per_sec * 15);		//15 seconds of chasing
	}
	if (playfield [pacman.next_x - 1] [pacman.y + 2] == 'p')
	{
		remove_pellet(pacman.next_x - 1, pacman.y + 2);
	}
	for (int j = 0; j < OBJ_SIZE; j++)
	{
		switch (playfield [pacman.next_x] [pacman.y + j])
		{
			case (' '):
			{
				break;
			}
			case ('p'):
			{
				break;
			}
			case ('|'):
			{
				pacman.collided = playfield [pacman.next_x] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('E'):
			{
				pacman.collided = playfield [pacman.next_x] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('e'):
			{
				pacman.collided = playfield [pacman.next_x] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('V'):
			{
				pacman.collided = playfield [pacman.next_x] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('^'):
			{
				pacman.collided = playfield [pacman.next_x] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('>'):
			{
				pacman.collided = playfield [pacman.next_x] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			/*case ('-'):		//shouldn't collide with these
			{
				pacman.collided = playfield [pacman.next_x] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('W'):
			{
				pacman.collided = playfield [pacman.next_x] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('w'):
			{
				pacman.collided = playfield [pacman.next_x] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('<'):
			{
				pacman.collided = playfield [pacman.next_x] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}*/
			case ('x'):
			{
				problem(131);
				break;
			}
			default:
			{
				cout << playfield [pacman.next_x] [pacman.y + j] << endl;
				problem(118);
			}
		}
	}
	return false;
}

bool pacman_collision_right(int direction)
{
	pacman.next_x = pacman.x + 1;
	pacman.collided = ' ';
	pacman.col_type = ' ';
	if (playfield [pacman.next_x + 4] [pacman.y + 2] == 'p')
	{
		remove_pellet(pacman.next_x + 4, pacman.y + 2);
	}
	if (playfield [pacman.next_x + 4] [pacman.y + 1] == 'p')
	{
		remove_pellet(pacman.next_x + 4, pacman.y + 1);
	}
	for (int j = 0; j < OBJ_SIZE; j++)
	{
		switch (playfield [pacman.next_x + 5] [pacman.y + j])
		{
			case (' '):
			{
				break;
			}
			case ('p'):
			{
				break;
			}
			case ('|'):
			{
				pacman.collided = playfield [pacman.next_x + 5] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('W'):
			{
				pacman.collided = playfield [pacman.next_x + 5] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('w'):
			{
				pacman.collided = playfield [pacman.next_x + 5] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('V'):
			{
				pacman.collided = playfield [pacman.next_x + 5] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('^'):
			{
				pacman.collided = playfield [pacman.next_x + 5] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('<'):
			{
				pacman.collided = playfield [pacman.next_x + 5] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			/*case ('-'):		//shouldn't collide with these
			{
				pacman.collided = playfield [pacman.next_x + 5] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('E'):
			{
				pacman.collided = playfield [pacman.next_x + 5] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('e'):
			{
				pacman.collided = playfield [pacman.next_x + 5] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}
			case ('>'):
			{
				pacman.collided = playfield [pacman.next_x + 5] [pacman.y + j];
				pacman.col_type = 'W';
				return true;
				break;
			}*/
			case ('x'):
			{
				num_pellets++;
				score--;
				remove_pellet(pacman.next_x + 5, pacman.y + j);
				vitamin_time = floor(times_per_sec * 15);		//15 seconds of chasing
				break;
			}
			default:
			{
				cout << playfield [pacman.next_x + 5] [pacman.y + j] << endl;
				problem(119);
			}
		}
	}
	return false;
}

void remove_pellet(int x, int y)
{
	pellet_eaten = true;
	playfield [x] [y] = ' ';
	num_pellets--;
	//cout << x << ", " << y << endl;
	//cout << num_pellets << " pellets left." << endl;
	score++;
	if (num_pellets == 0)
	{
		reset = true;
	}
}

void pacman_death()
{
	ST closest = closest_ghost();
	if (closest == BLINKY)
	{
		if (g_blinky.status == ST_AFRAID)
		{
			g_blinky.status = ST_DEAD;
		} else
		{
			if (g_blinky.status == ST_BLINKY)
			{
				pac_death_anim();
			} else
			{
				return;
			}
		}
	}
	if (closest == PINKY)
	{
		if (g_pinky.status == ST_AFRAID)
		{
			g_pinky.status = ST_DEAD;
		} else
		{
			if (g_pinky.status == ST_PINKY)
			{
				pac_death_anim();
			} else
			{
				return;
			}
		}
	}
	if (closest == INKY)
	{
		if (g_inky.status == ST_AFRAID)
		{
			g_inky.status = ST_DEAD;
		} else
		{
			if (g_inky.status == ST_INKY)
			{
				pac_death_anim();
			} else
			{
				return;
			}
		}
	}
	if (closest == CLYDE)
	{
		if (g_clyde.status == ST_AFRAID)
		{
			g_clyde.status = ST_DEAD;
		} else
		{
			if (g_clyde.status == ST_CLYDE)
			{
				pac_death_anim();
			} else
			{
				return;
			}
		}
	}
	if (mute == false)
	{
		Sound::play("eatghost");
	}
	ghosts_eaten++;
	switch(ghosts_eaten)
	{
		case (1):
		{
			score += 200;
			break;
		}
		case (2):
		{
			score += 400;
			break;
		}
		case (3):
		{
			score += 800;
			break;
		}
		case (4):
		{
			score += 1600;
			break;
		}
		default:
		{
			problem(130);
			break;
		}
	}
	//cout << ghosts_eaten << endl;
	//cout << score << endl;
	//Finish code - send home AI - or perhaps built into class?
}

void pac_death_anim()
{
	int adj_y = -4;
	if (mute == false)
	{
		Sound::play("pacdeath2");
	}
	Sprite::draw("pacman_death_1", pacman.x, SCREENH - 1 - (pacman.y - adj_y), 5.0, 5.0, 0.0f, true);
	SDL_GL_SwapBuffers();
	wait(0.13);
	Sprite::draw("pacman_death_2", pacman.x, SCREENH - 1 - (pacman.y - adj_y), 5.0, 5.0, 0.0f, true);
	SDL_GL_SwapBuffers();
	wait(0.13);
	Sprite::draw("pacman_death_3", pacman.x, SCREENH - 1 - (pacman.y - adj_y), 5.0, 5.0, 0.0f, true);
	SDL_GL_SwapBuffers();
	wait(0.13);
	Sprite::draw("pacman_death_4", pacman.x, SCREENH - 1 - (pacman.y - adj_y), 5.0, 5.0, 0.0f, true);
	SDL_GL_SwapBuffers();
	wait(0.13);
	Sprite::draw("pacman_death_5", pacman.x, SCREENH - 1 - (pacman.y - adj_y), 5.0, 5.0, 0.0f, true);
	SDL_GL_SwapBuffers();
	wait(0.13);
	Sprite::draw("pacman_death_6", pacman.x, SCREENH - 1 - (pacman.y - adj_y), 5.0, 5.0, 0.0f, true);
	SDL_GL_SwapBuffers();
	wait(0.13);
	Sprite::draw("pacman_death_7", pacman.x, SCREENH - 1 - (pacman.y - adj_y), 5.0, 5.0, 0.0f, true);
	SDL_GL_SwapBuffers();
	wait(0.13);
	Sprite::draw("pacman_death_8", pacman.x, SCREENH - 1 - (pacman.y - adj_y), 5.0, 5.0, 0.0f, true);
	SDL_GL_SwapBuffers();
	wait(0.13);
	Sprite::draw("pacman_death_9", pacman.x, SCREENH - 1 - (pacman.y - adj_y), 5.0, 5.0, 0.0f, true);
	SDL_GL_SwapBuffers();
	wait(0.13);
	Sprite::draw("pacman_death_10", pacman.x, SCREENH - 1 - (pacman.y - adj_y), 5.0, 5.0, 0.0f, true);
	SDL_GL_SwapBuffers();
	wait(0.13);
	Sprite::draw("pacman_death_11", pacman.x, SCREENH - 1 - (pacman.y - adj_y), 5.0, 5.0, 0.0f, true);
	SDL_GL_SwapBuffers();
	wait(0.13);
	Sprite::draw("pacman_death_12", pacman.x, SCREENH - 1 - (pacman.y - adj_y), 5.0, 5.0, 0.0f, true);
	SDL_GL_SwapBuffers();
	wait(0.13);
	reset = true;
	lives--;
	if (lives == 0)
	{
		cout << "Score: " << score << endl;
		problem(99);
	}
}

void ghost_collision()
{
	for (int k = 0; k < OBJ_SIZE; k++)
	{		
		if (ghostfield [g_blinky.x + k] [g_blinky.y] == 'P')
		{
			pacman_death();
		} else
		if (ghostfield [g_blinky.x + k] [g_blinky.y + 5] == 'P') 
		{
			pacman_death();
		} else
		if (ghostfield [g_blinky.x] [g_blinky.y + k] == 'P') 
		{
			pacman_death();
		} else
		if (ghostfield [g_blinky.x + 5] [g_blinky.y + k] == 'P') 
		{
			pacman_death();
		}
		if (ghostfield [g_pinky.x + k] [g_pinky.y] == 'P')
		{
			pacman_death();
		} else
		if (ghostfield [g_pinky.x + k] [g_pinky.y + 5] == 'P') 
		{
			pacman_death();
		} else
		if (ghostfield [g_pinky.x] [g_pinky.y + k] == 'P') 
		{
			pacman_death();
		} else
		if (ghostfield [g_pinky.x + 5] [g_pinky.y + k] == 'P') 
		{
			pacman_death();
		}
		if (ghostfield [g_inky.x + k] [g_inky.y] == 'P')
		{
			pacman_death();
		} else
		if (ghostfield [g_inky.x + k] [g_inky.y + 5] == 'P') 
		{
			pacman_death();
		} else
		if (ghostfield [g_inky.x] [g_inky.y + k] == 'P') 
		{
			pacman_death();
		} else
		if (ghostfield [g_inky.x + 5] [g_inky.y + k] == 'P') 
		{
			pacman_death();
		}
		if (ghostfield [g_clyde.x + k] [g_clyde.y] == 'P')
		{
			pacman_death();
		} else
		if (ghostfield [g_clyde.x + k] [g_clyde.y + 5] == 'P') 
		{
			pacman_death();
		} else
		if (ghostfield [g_clyde.x] [g_clyde.y + k] == 'P') 
		{
			pacman_death();
		} else
		if (ghostfield [g_clyde.x + 5] [g_clyde.y + k] == 'P') 
		{
			pacman_death();
		}
	}
}

ST closest_ghost()
{
	ST closest;
	g_blinky.distance = (pacman.x - g_blinky.x) * (pacman.x - g_blinky.x) +
		(pacman.y - g_blinky.y) * (pacman.y - g_blinky.y);
	g_pinky.distance = (pacman.x - g_pinky.x) * (pacman.x - g_pinky.x) +
		(pacman.y - g_pinky.y) * (pacman.y - g_pinky.y);
	g_inky.distance = (pacman.x - g_inky.x) * (pacman.x - g_inky.x) +
		(pacman.y - g_inky.y) * (pacman.y - g_inky.y);
	g_clyde.distance = (pacman.x - g_clyde.x) * (pacman.x - g_clyde.x) +
		(pacman.y - g_clyde.y) * (pacman.y - g_clyde.y);
	if (g_blinky.distance < g_pinky.distance &&
		g_blinky.distance < g_inky.distance &&
		g_blinky.distance < g_clyde.distance)			//blinky is closest
	{
		closest = BLINKY;
	} else
	{
		if (g_pinky.distance < g_inky.distance &&
			g_pinky.distance < g_clyde.distance)		//pinky is closest
		{
			closest = PINKY;
		} else
		{
			if (g_inky.distance < g_clyde.distance)		//inky is closest
			{
				closest = INKY;
			} else										//clyde is closest
			{
				closest = CLYDE;
			}
		}
	}
	return closest;
}