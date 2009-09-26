/******************************************************\
|This file and its contents ©Copyright 2008 Adam Hintz |
|and Alastair Lynn. You may not redistribute or use    |
|parts or the whole of this code without our express   |
|written permission. All rights reserved.              |
\******************************************************/

#include "pacman01.h"
#include "sprite.h"
#include "sound.h"
#include "drawobject.h"
#include "collision.h"
#include "aialgorithm.h"
#include "menu.h"

ofstream fileout("logging.txt");

bool done = false;
bool stop = false;
bool first = false;
bool inverted_axes = false;
bool menu_quit = false;
bool pellet_eaten = false;
bool change_key = false;
bool other_time = false;
bool reset = false;
int timer_speed = 85;	//85 preferred, 50 for better speed / debugging (old:130)
int ghosts_eaten = 0;
int score = 0;
int lives = 1;
int num_pellets = 182;
unsigned int vitamin_time = 0;
char last_press = ' ';
double times_per_sec = 1000/85;

SDL_TimerID timer;

Uint32 game_timer(Uint32 interval, void* param)
{
	SDL_Event event;
	
	event.type = SDL_USEREVENT;
	event.user.code = RUN_GAME_LOOP;
	event.user.data1 = 0;
	event.user.data2 = 0;
	
	SDL_PushEvent(&event);
	
	return interval;
}

void problem(int errornum)
{
	if (errornum != 99)
	{
		cout << "The program has encountered an error. Error: " << errornum;
	} else
	{
		cout << "Game Over. :|";
	}
	exit(101);
}

void event_loop()
{
	SDL_Event event;
	while(!done)
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type) 
			{
	//			case SDL_MOUSEBUTTONDOWN:
				case SDL_QUIT:
				{
					done = true;
					break;
				}
				case SDL_USEREVENT:
				{
					if (event.user.code == RUN_GAME_LOOP) 
					{
						if (vitamin_time > 0)
						{
							vitamin_time--;
							if (g_blinky.status == ST_BLINKY)
							{
								g_blinky.status = ST_AFRAID;
							}
							if (g_pinky.status == ST_PINKY)
							{
								g_pinky.status = ST_AFRAID;
							}
							if (g_inky.status == ST_INKY)
							{
								g_inky.status = ST_AFRAID;
							}
							if (g_clyde.status == ST_CLYDE)
							{
								g_clyde.status = ST_AFRAID;
							}
						} else
						{
							if (g_blinky.status != ST_DEAD)
							{
								g_blinky.status = ST_BLINKY;
							}
							if (g_pinky.status != ST_DEAD)
							{
								g_pinky.status = ST_PINKY;
							}
							if (g_inky.status != ST_DEAD)
							{
								g_inky.status = ST_INKY;
							}
							if (g_clyde.status != ST_DEAD)
							{
								g_clyde.status = ST_CLYDE;
							}
						}
						animation = !(animation);
						if (animation == true)
						{
							other_time = !other_time;
						}
						if (trans_num != 0)
						{
							draw_scene();
							break;
						}
						if (change_key == true)
						{
							change_key = false;
						}
						if (change_key == false)
						{
							switch (last_press)
							{
								case (' '):
								{
									break;
								}
								case ('w'):
								{
									if (pacman_collision(MOVE_UP) == false)
									{
										pacrot = 1;
									} else
									{
										last_press = ' ';
									}
									draw_scene();
									break;
								}
								case ('a'):
								{
									if (pacman_collision(MOVE_LEFT) == false)
									{
										pacrot = 2;
									} else
									{
										last_press = ' ';
									}
									draw_scene();
									break;
								}
								case ('s'):
								{
									if (pacman_collision(MOVE_DOWN) == false)
									{
										pacrot = 3;
									} else
									{
										last_press = ' ';
									}
									draw_scene();
									break;
								}
								case ('d'):
								{
									if (pacman_collision(MOVE_RIGHT) == false)
									{
										pacrot = 0;
									} else
									{
										last_press = ' ';
									}
									draw_scene();
									break;
								}
								default:
								cout << last_press << endl;
								problem(127);
							}
						}
						if (pellet_eaten == true)
						{
							if (mute == false)
							{
								Sound::play("eatpellet");
							}
							pellet_eaten = false;
						}
						//display_ghostfield();
						draw_scene();
					}
					break;
				}
				case SDL_KEYDOWN:
				{
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
						{
							done = true;
							//displayfield(ghostrun);
							break;
						}
						/*case SDLK_x:
						{
							if (SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE)
							{
								first = false;
								SDL_ShowCursor(SDL_DISABLE);
								SDL_WM_GrabInput(SDL_GRAB_ON);
							}else
							{
								first = false;
								SDL_ShowCursor(SDL_ENABLE);
								SDL_WM_GrabInput(SDL_GRAB_OFF);
							}
							break;
						}*/
						case SDLK_k:		//purposeful kill
						{
							cout << pacman.x << ", " << pacman.y << endl;
							pacman_death();
							break;
						}
						case SDLK_w:
						{
							if (trans_num == 0)
							{
								if (last_press != 'w')
								{
									last_press = 'w';
									if (pacman_collision(MOVE_UP) == false)
									{
										pacrot = 1;
									}
									change_key = true;
									draw_scene();
								}
							}
							break;
						}
						case SDLK_s:
						{
							if (trans_num == 0)
							{
								if (last_press != 's')
								{
									last_press = 's';
									if (pacman_collision(MOVE_DOWN) == false)
									{
										pacrot = 3;
									}
									change_key = true;
									draw_scene();
								}
							}
							break;
						}
						case SDLK_a:
						{
							if (trans_num == 0)
							{
								if (last_press != 'a')
								{
									last_press = 'a';
									if (pacman_collision(MOVE_LEFT) == false)
									{
										pacrot = 2;
									}
									change_key = true;
									draw_scene();
								}
							}
							break;
						}
						case SDLK_d:
						{
							if (trans_num == 0)
							{
								if (last_press != 'd')
								{
									last_press = 'd';
									if (pacman_collision(MOVE_RIGHT) == false)
									{
										pacrot = 0;
									}
									change_key = true;
									draw_scene();
								}
							}
							break;
						}
						/*case SDLK_LEFT: //Fullscreening
						{
							if (!stop)
							{
								Uint32 flags = SDL_OPENGL | SDL_FULLSCREEN;
								SDL_Surface* drawContext;
								drawContext = SDL_SetVideoMode(resolution[0], resolution[1], 0, flags);
								draw_scene();
								SDL_GL_SwapBuffers();
							}
							break;
						}
						case SDLK_RIGHT: //Window-izing
						{
							if (!stop)
							{
								Uint32 flags = SDL_OPENGL;
								SDL_Surface* drawContext;
								drawContext = SDL_SetVideoMode(resolution[0], resolution[1], 0, flags);
								draw_scene();
								SDL_GL_SwapBuffers();
							}
							break;
						}*/
						case SDLK_RETURN:
						{
							if (!stop)
							{
							}
							break;
						}
						default: break;
					}
				}
				default: break;
			}
		}
    }
}

void initialize()
{
	srand(time(NULL));
	int sdl_error = SDL_Init(SDL_INIT_EVERYTHING);
	if (sdl_error != false)
	{
		fileout << "Error in SDL initialization: " << sdl_error;
		problem(100);
	}else
	{
		fileout << "No SDL initialization errors." << endl << flush;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);
	Uint32 flags = SDL_OPENGL;
//	Uint32 flags = SDL_OPENGL | SDL_FULLSCREEN;
	SDL_Surface* drawContext;
	drawContext = SDL_SetVideoMode(resolution[0] / 2, resolution[1] / 2, 0, flags);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_TEXTURE_RECTANGLE_ARB);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-2.0, SCREENTW - 2.0, -2.0, SCREENTH - 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Sound::music("eatpellet");
	Sound::music("eatghost");
	Sound::music("pacdeath2");
	Sound::music("moo_theme");
	g_blinky.pers_status = ST_BLINKY;
	g_pinky.pers_status = ST_PINKY;
	g_inky.pers_status = ST_INKY;
	g_clyde.pers_status = ST_CLYDE;
	get_control_points();
}

void wait (float seconds)
{
	Uint32 ms = seconds * 1000;
	SDL_Delay(ms);
}

void draw_scene()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	if (firstdraw == true || reset == true)
	{
		if (firstdraw == true)
		{
			timer = SDL_AddTimer(timer_speed, game_timer, 0);
			setfield("ghostmap.txt", ghostfield);
			setfield("pacmap-inversion.txt", ghostrun);
			pacman.next_x = pacman.x + 1;
		}
		setfield("pacmap.txt", playfield);
		//initialize ghosts
		g_blinky.status = ST_BLINKY;
		g_pinky.status = ST_PINKY;
		g_inky.status = ST_INKY;
		g_clyde.status = ST_CLYDE;
		g_blinky.direction = ST_LEFT;
		g_pinky.direction = ST_LEFT;
		g_inky.direction = ST_LEFT;
		g_clyde.direction = ST_LEFT;
		g_blinky.has_los = false;
		g_pinky.has_los = false;
		g_inky.has_los = false;
		g_clyde.has_los = false;
		g_blinky.x = 43;
		g_blinky.y = 8;
		g_pinky.x = 53;
		g_pinky.y = 15;
		g_inky.x = 51;
		g_inky.y = 22;
		g_clyde.x = 57;
		g_clyde.y = 22;
	}
	Ai::encompassing();
	//displayfield(ghostfield);
	draw_playfield();
	draw_pacman();
	draw_ghosts();
	draw_score();
	
	SDL_GL_SwapBuffers();
	int error = glGetError();
	if (error != 0)
	{
		fileout << "Error: " << error << endl << flush;
		cout << "Error: " << error << endl << flush;
	}
}

int main(int argc, char *argv[])
{	
	initialize();
	fileout << "Initialization complete." << endl << flush;
	Menu::main();
	
	if (menu_quit == false)
	{
		//SDL_ShowCursor(SDL_DISABLE);
		//SDL_WM_GrabInput(SDL_GRAB_ON);
		draw_scene();
		
		event_loop();
		fileout << endl << "Event loop finished." << endl << flush;
    }
    SDL_Quit();
	fileout << "Cleanup complete." << endl << flush;
    return 0;
}