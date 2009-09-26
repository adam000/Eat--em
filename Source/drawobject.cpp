/******************************************************\
|This file and its contents ©Copyright 2008 Adam Hintz |
|and Alastair Lynn. You may not redistribute or use    |
|parts or the whole of this code without our express   |
|written permission. All rights reserved.              |
\******************************************************/

#include "sprite.h"
#include "drawobject.h"
#include "collision.h"
#include "file_manager.h"

int pacrot;
bool firstdraw = true;
bool animation = false;
bool afraid_ghosts = false;
int adj_x = 0;
int adj_y = 5;
int trans_num = 0;

pacman_class pacman;

ghost_class g_blinky;
ghost_class g_pinky;
ghost_class g_inky;
ghost_class g_clyde;


char playfield [SCREENW] [SCREENH];
char ghostfield [SCREENW] [SCREENH];
char ghostrun [SCREENW] [SCREENH];

void draw_playfield()	//playfield is 57 (8 blocks + walls) by 113 (16 blocks + walls)
{
	for(int j = 0; j < SCREENH; j++)
	{
		for(int i = 0; i < SCREENW; i++)
		{
			switch(playfield [i] [SCREENH - 1 - j])
			{
				case(' '):	//empty
				{
					break;
				}
				case('p'):	//pellet
				{
					Sprite::draw("pellet", i, j, 2.0, 1.0, 0.0f, true);
					break;
				}
				case('|'):	//vertwall
				{
					Sprite::draw("wall", i + 0.8, j, 1.0, 1.0, 90.0f, true);
					break;
				}
				case('-'):	//horizwall
				{
					Sprite::draw("wall", i - 0.1, j, 1.0, 1.0, 0.0f, true);
					break;
				}
				case('<'):	//leftstop
				{
					Sprite::draw("dead_end", i - 0.2, j + 0.2, 1.0, 1.0, 0.0f, true);
					break;
				}
				case('>'):	//rightstop
				{
					Sprite::draw("dead_end", i + 0.7, j + 1.2, 1.0, 1.0, 180.0f, true);
					break;
				}
				case('^'):	//topstop
				{
					Sprite::draw("dead_end", i - 0.4, j + 1.0, 1.0, 1.0, 270.0f, true);
					break;
				}
				case('V'):	//botstop
				{
					Sprite::draw("dead_end", i + 0.66, j + 0.2, 1.0, 1.0, 90.0f, true);
					break;
				}
				case('W'):	//nwcorner
				{
					Sprite::draw("ne_corner", i + 1.0, j, 1.0, 1.0, 90.0f, true);
					break;
				}
				case('E'):	//ne_corner
				{
					Sprite::draw("ne_corner", i - 0.7, j, 1.0, 1.0, 0.0f, true);
					break;
				}
				case('w'):	//swcorner
				{
					Sprite::draw("ne_corner", i + 1.0, j + 1.43, 1.0, 1.0, 180.0f, true);
					break;
				}
				case('e'):	//secorner
				{
					Sprite::draw("ne_corner", i - 0.5, j + 1.4, 1.0, 1.0, 270.0f, true);
					break;
				}
				case('a'):	//toptee
				{
					Sprite::draw("tee_intersect", i - 0.3, j, 1.0, 1.0, 0.0f, true);
					break;
				}
				case('b'):	//bottee
				{
					Sprite::draw("tee_intersect", i + 0.7, j + 1.4, 1.0, 1.0, 180.0f, true);
					break;
				}
				case('c'):	//lefttee
				{
					Sprite::draw("tee_intersect", i + 0.9, j + 0.1, 1.0, 1.0, 90.0f, true);
					break;
				}
				case('d'):	//righttee
				{
					Sprite::draw("tee_intersect", i - 0.6, j + 1.1, 1.0, 1.0, 270.0f, true);
					break;
				}
				case('x'):	//vitamin
				{
					if (other_time == true)
					{
						Sprite::draw("pellet", i, j, 2.0, 2.0, 0.0f, true);
					}
					break;
				}
				case('G'):	//ghost - will specify elsewhere
				{
				}
				case('P'):	//pacman - will specify elsewhere
				{
				}
				case('T'):	//Teleport - will define later
				{
					break;
				}
				default:
				{
					cout << "'" << playfield [i] [j] << "'" << endl
					<< "@ " << i << ", " << j << endl << __FILE__ << ", " << __LINE__ << endl;
					problem(101);
					break;
				}
			}
		}
	}
}

void setfield(const std::string& playfield_file, char temp_array [SCREENW] [SCREENH])
{
	SDL_RWops* ops = FM->OpenFile(playfield_file);
	char readChar;
	if (!ops)
	{
		problem(102);
	}
	for (int j = 0; j < SCREENH; j++)
	{
		for (int i = 0; i < SCREENW; i++)
		{
			SDL_RWread(ops, &readChar, 1, 1);
			temp_array [i] [j] = readChar;
			//cout << temp_array [i] [j];
		}
		SDL_RWread(ops, &readChar, 1, 1);
		//cout << readChar;
	}
	fileout << "File load complete." << endl;
}

void get_control_points()
{
	fileout.close();
	int num = 0;
	int filler [94] [2];
	ifstream fin("control_points.txt");
	assert (!fin.fail());
	bool trigger = false;
	while (num != 188)
	{
		int temp = floor(num / 2);
		fin >> filler [temp] [trigger];
		//cout << filler [temp] [trigger] << endl;
		num++;
	}
	ofstream fileout("logging.txt", ios::app);
}

void displayfield(char temp_array [SCREENW] [SCREENH])
{
	for (int j = 0; j < SCREENH; j++)
	{
		for (int i = 0; i < SCREENW; i++)
		{
			cout << temp_array [i] [j];
		}
		cout << endl;
	}
}

void draw_pacman()
{
	if (trans_num != 0)
	{
		if (trans_num < 12)
		{
			if (transporting_up == true)
			{
				draw_pac_trans_up();
			} else
			{
				draw_pac_trans_down();
			}
			trans_num++;
			return;
		} else
		{
			trans_num = 0;
		}
	}
	if (firstdraw == true || reset == true)
	{
		pacrot = 0;
		pacman.x = 54;
		pacman.y = 29;
		firstdraw = false;
		reset = false;
	}
	if (pacman.collided == ' ')
	{
		switch (pacrot)
		{
			case (0):		//facing right
			{
				adj_x = 0;
				adj_y = 5;
				for (int j = 0; j < OBJ_SIZE; j++)
				{
					ghostfield [pacman.next_x - 1] [pacman.y + j] = ' ';
					ghostfield [pacman.next_x + 5] [pacman.y + j] = 'P';
				}
				break;
			}
			case (1):		//facing up
			{
				adj_x = 5;
				adj_y = 5;
				for (int i = 0; i < OBJ_SIZE; i++)
				{
					ghostfield [pacman.x + i] [pacman.next_y] = 'P';
					ghostfield [pacman.x + i] [pacman.next_y + 6] = ' ';
				}
				break;
			}
			case (2):		//facing left
			{
				adj_x = 5;
				adj_y = 0;
				for (int j = 0; j < OBJ_SIZE; j++)
				{
					ghostfield [pacman.next_x] [pacman.y + j] = 'P';
					ghostfield [pacman.next_x + 6] [pacman.y + j] = ' ';
				}
				break;
			}
			case (3):		//facing down
			{
				adj_x = 0;
				adj_y = 0;
				for (int i = 0; i < OBJ_SIZE; i++)
				{
					ghostfield [pacman.x + i] [pacman.next_y - 1] = ' ';
					ghostfield [pacman.x + i] [pacman.next_y + 5] = 'P';
				}
				break;
			}
			default:
			{
				problem(103);
				break;
			}
		}
	}
	if (animation == false)
	{
		Sprite::draw("pacman_rt_1", pacman.x + adj_x, SCREENH - (pacman.y + adj_y), 5.0, 5.0, pacrot * 90.0, true);
	} else
	{
		Sprite::draw("pacman_rt_2", pacman.x + adj_x, SCREENH - (pacman.y + adj_y), 5.0, 5.0, pacrot * 90.0, true);
	}
	//Sprite::draw("wall", pacman.x, SCREENH - 1 - pacman.y, 1.0, 1.0, 0.0, true);
	//cout << pacman.x << ", " << pacman.y << endl;
}

void draw_pac_trans_down()
{
	adj_x = 0;
	adj_y = 0;
	if (trans_num < 7)
	{
		for (int i = 0; i < OBJ_SIZE; i++)
		{
			ghostfield [pacman.x + i] [pacman.y - 1 + trans_num] = ' ';
		}
		if (animation == false)
		{
			Sprite::draw("pacman_rt_1", pacman.x + adj_x, SCREENH - (pacman.y + adj_y) - trans_num, 5.0, 5.0, 270.0, true);
		} else
		{
			Sprite::draw("pacman_rt_2", pacman.x + adj_x, SCREENH - (pacman.y + adj_y) - trans_num, 5.0, 5.0, 270.0, true);
		}
	}
	if (trans_num > 5)
	{
		if (trans_num == 6)
		{
			pacman.y = 1;
		}
		if (trans_num == 8)
		{
			remove_pellet(53, 3);
			remove_pellet(57, 3);
		}
		for (int i = 0; i < OBJ_SIZE; i++)
		{
			ghostfield [pacman.x + i] [pacman.y + trans_num - 6] = 'P';
		}
		if (animation == false)
		{
			Sprite::draw("pacman_rt_1", pacman.x + adj_x, SCREENH - (pacman.y + adj_y + trans_num - 11), 5.0, 5.0, 270.0, true);
		} else
		{
			Sprite::draw("pacman_rt_2", pacman.x + adj_x, SCREENH - (pacman.y + adj_y + trans_num - 11), 5.0, 5.0, 270.0, true);
		}
	}
}

void draw_pac_trans_up()
{
	adj_x = 5;
	adj_y = 5;
	if (trans_num < 7)
	{
		for (int i = 0; i < OBJ_SIZE; i++)
		{
			ghostfield [pacman.x + i] [pacman.next_y + 7 - trans_num] = ' ';
		}
		if (animation == false)
		{
			Sprite::draw("pacman_rt_1", pacman.x + adj_x, SCREENH - (pacman.y + adj_y) + trans_num - 1, 5.0, 5.0, 90.0, true);
		} else
		{
			Sprite::draw("pacman_rt_2", pacman.x + adj_x, SCREENH - (pacman.y + adj_y) + trans_num - 1, 5.0, 5.0, 90.0, true);
		}
	}
	if (trans_num > 5)
	{
		if (trans_num == 6)
		{
			pacman.y = SCREENH - 7;
		}
		if (trans_num == 8)
		{
			remove_pellet(53, 52);
			remove_pellet(58, 52);
		}
		for (int i = 0; i < OBJ_SIZE; i++)
		{
			ghostfield [pacman.x + i] [pacman.y - trans_num + 11] = 'P';
		}
		if (animation == false)
		{
			Sprite::draw("pacman_rt_1", pacman.x + adj_x, SCREENH - (pacman.y + adj_y) + trans_num - 11, 5.0, 5.0, 90.0, true);
		} else
		{
			Sprite::draw("pacman_rt_2", pacman.x + adj_x, SCREENH - (pacman.y + adj_y) + trans_num - 11, 5.0, 5.0, 90.0, true);
		}
	}
}

void draw_ghosts()
{
	glColor4f(1.0, 1.0, 1.0, 0.2);	//.2 transparency?	//I need help - this isn't making ghosts transparent
	
	ST num;
	if (animation == false)
	{
		num = '1';
	} else
	{
		num = '2';
	}
	if (g_blinky.status == ST_BLINKY)			//alive
	{
		Sprite::draw(g_blinky.status + g_blinky.direction + num, g_blinky.x, SCREENH - (g_blinky.y + 5), 5.0, 5.0, 0.0, true);
	} else
	{
		if (g_blinky.status == ST_AFRAID)		//afraid
		{
			Sprite::draw(g_blinky.status + num, g_blinky.x, SCREENH - (g_blinky.y + 5), 5.0, 5.0, 0.0, true);
		} else									//dead
		{
			Sprite::draw(g_blinky.status + g_blinky.direction + num, g_blinky.x, SCREENH - (g_blinky.y + 5), 5.0, 5.0, 0.0, true);
		}
	}
	if (g_pinky.status == ST_PINKY)				//alive
	{
		Sprite::draw(g_pinky.status + g_pinky.direction + num, g_pinky.x, SCREENH - (g_pinky.y + 5), 5.0, 5.0, 0.0, true);
	} else
	{
		if (g_pinky.status == ST_AFRAID)		//afraid
		{
			Sprite::draw(g_pinky.status + num, g_pinky.x, SCREENH - (g_pinky.y + 5), 5.0, 5.0, 0.0, true);
		} else									//dead
		{
			Sprite::draw(g_pinky.status + g_pinky.direction + num, g_pinky.x, SCREENH - (g_pinky.y + 5), 5.0, 5.0, 0.0, true);
		}
	}
	if (g_inky.status == ST_INKY)				//alive
	{
		Sprite::draw(g_inky.status + g_inky.direction + num, g_inky.x, SCREENH - (g_inky.y + 5), 5.0, 5.0, 0.0, true);
	} else
	{
		if (g_inky.status == ST_AFRAID)			//afraid
		{
			Sprite::draw(g_inky.status + num, g_inky.x, SCREENH - (g_inky.y + 5), 5.0, 5.0, 0.0, true);
		} else									//dead
		{
			Sprite::draw(g_inky.status + g_inky.direction + num, g_inky.x, SCREENH - (g_inky.y + 5), 5.0, 5.0, 0.0, true);
		}
	}
	if (g_clyde.status == ST_CLYDE)				//alive
	{
		Sprite::draw(g_clyde.status + g_clyde.direction + num, g_clyde.x, SCREENH - (g_clyde.y + 5), 5.0, 5.0, 0.0, true);
	} else
	{
		if (g_clyde.status == ST_AFRAID)		//afraid
		{
			Sprite::draw(g_clyde.status + num, g_clyde.x, SCREENH - (g_clyde.y + 5), 5.0, 5.0, 0.0, true);
		} else									//dead
		{
			Sprite::draw(g_clyde.status + g_clyde.direction + num, g_clyde.x, SCREENH - (g_clyde.y + 5), 5.0, 5.0, 0.0, true);
		}
	}
	glColor4f(1.0, 1.0, 1.0, 0.0);	//return to no transparency
}

void draw_score()
{
	glDisable(GL_TEXTURE_RECTANGLE_ARB);
	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.0);
	glVertex2i( 0, 57);
	glVertex2i(90, 57);
	glVertex2i(90, 75);
	glVertex2i( 0, 75);
	glVertex2i( 0, -4);
	glVertex2i(90, -4);
	glVertex2i(90,  0);
	glVertex2i( 0,  0);
	glEnd();
	glEnable(GL_TEXTURE_RECTANGLE_ARB);
	glColor3f(1.0, 1.0, 1.0);
	ST score_k_num = score_init((score - (score % 1000)) / 1000);
	ST score_c_num = score_init(((score % 1000) - (score % 100)) / 100);
	ST score_d_num = score_init(((score % 100) - (score % 10)) / 10);
	ST score_u_num = score_init((score % 10) - (score % 1));
	Sprite::draw("alp_s",  9.0, 60, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_c", 11.1, 60, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_o", 13.2, 60, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_r", 15.3, 60, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_e", 17.4, 60, 2.0, 2.0, 0.0f, true);
	Sprite::draw("num_" + score_k_num, 20.0, 60, 2.0, 2.0, 0.0f, true);
	Sprite::draw("num_" + score_c_num, 22.1, 60, 2.0, 2.0, 0.0f, true);
	Sprite::draw("num_" + score_d_num, 24.2, 60, 2.0, 2.0, 0.0f, true);
	Sprite::draw("num_" + score_u_num, 26.3, 60, 2.0, 2.0, 0.0f, true);
}

ST score_init(int score1)
{
	switch (score1)
	{
		case (0):
		{
			return ST_0;
			break;
		}
		case (1):
		{
			return ST_1;
			break;
		}
		case (2):
		{
			return ST_2;
			break;
		}
		case (3):
		{
			return ST_3;
			break;
		}
		case (4):
		{
			return ST_4;
			break;
		}
		case (5):
		{
			return ST_5;
			break;
		}
		case (6):
		{
			return ST_6;
			break;
		}
		case (7):
		{
			return ST_7;
			break;
		}
		case (8):
		{
			return ST_8;
			break;
		}
		case (9):
		{
			return ST_9;
			break;
		}
	}
	return ST_0;
}