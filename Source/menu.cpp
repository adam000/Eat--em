/******************************************************\
|This file and its contents ©Copyright 2008 Adam Hintz |
|and Alastair Lynn. You may not redistribute or use    |
|parts or the whole of this code without our express   |
|written permission. All rights reserved.              |
\******************************************************/

#include "pacman01.h"
#include "menu.h"
#include "sound.h"
#include "sprite.h"

int resolution [2] = {1280, 800};
RES trueres = macbook;

namespace Menu
{

void draw_main()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	Sprite::load_set("mainscreen");
	glColor3f(1.0, 1.0, 1.0);
	Sprite::draw("paclogo", 50.0, 50.0, 0.7, 0.7, 0.0f, false);
	Sprite::load_set("sprites");
	Sprite::draw("alp_s", 4.0, 16.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_t", 6.1, 16.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_a", 8.2, 16.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_r", 10.3, 16.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_t", 12.4, 16.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_o", 4.0, 12.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_p", 6.1, 12.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_t", 8.2, 12.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_i", 10.3, 12.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_o", 12.4, 12.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_n", 14.5, 12.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_s", 16.6, 12.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_c", 4.0, 8.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_r", 6.1, 8.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_e", 8.2, 8.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_d", 10.3, 8.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_i", 12.4, 8.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_t", 14.5, 8.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_s", 16.6, 8.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_q", 4.0, 4.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_u", 6.1, 4.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_i", 8.2, 4.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_t", 10.3, 4.0, 2.0, 2.0, 0.0f, true);
	SDL_GL_SwapBuffers();
}

void draw_options()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	Sprite::draw("alp_r", 4.0, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_e", 6.1, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_s", 8.2, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_o", 10.3, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_l", 12.4, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_u", 14.5, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_t", 16.6, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_i", 18.7, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_o", 20.8, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_n", 22.9, 50.0, 2.0, 2.0, 0.0f, true);
	
	if (trueres == macbook)
	{
		Sprite::draw("num_1", 26.5, 50.0, 2.0, 2.0, 0.0f, true);
		Sprite::draw("num_2", 28.6, 50.0, 2.0, 2.0, 0.0f, true);
		Sprite::draw("num_8", 30.7, 50.0, 2.0, 2.0, 0.0f, true);
		Sprite::draw("num_0", 32.8, 50.0, 2.0, 2.0, 0.0f, true);
		Sprite::draw("alp_x", 34.9, 50.0, 2.0, 2.0, 0.0f, true);
		Sprite::draw("num_8", 37.0, 50.0, 2.0, 2.0, 0.0f, true);
		Sprite::draw("num_0", 39.1, 50.0, 2.0, 2.0, 0.0f, true);
		Sprite::draw("num_0", 41.2, 50.0, 2.0, 2.0, 0.0f, true);
	} else
	{
		if (trueres == lowend)
		{
			Sprite::draw("num_1", 26.5, 50.0, 2.0, 2.0, 0.0f, true);
			Sprite::draw("num_0", 28.6, 50.0, 2.0, 2.0, 0.0f, true);
			Sprite::draw("num_2", 30.7, 50.0, 2.0, 2.0, 0.0f, true);
			Sprite::draw("num_4", 32.8, 50.0, 2.0, 2.0, 0.0f, true);
			Sprite::draw("alp_x", 34.9, 50.0, 2.0, 2.0, 0.0f, true);
			Sprite::draw("num_7", 37.0, 50.0, 2.0, 2.0, 0.0f, true);
			Sprite::draw("num_6", 39.1, 50.0, 2.0, 2.0, 0.0f, true);
			Sprite::draw("num_8", 41.2, 50.0, 2.0, 2.0, 0.0f, true);
		}
	}
	
	Sprite::draw("alp_r", 4.0, 4.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_e", 6.1, 4.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_t", 8.2, 4.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_u", 10.3, 4.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_r", 12.4, 4.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_n", 14.5, 4.0, 2.0, 2.0, 0.0f, true);
	SDL_GL_SwapBuffers();
}

void options()
{
	Menu::draw_options();
	SDL_Event event;
	bool done = false;
	while(!done)
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type) 
			{
				case SDL_KEYDOWN:
				{
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						Menu::draw_main();
						return;
					}
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					switch (event.button.button)
					{
						case SDL_BUTTON_LEFT:
						{
							int x_loc = event.button.x;
							int y_loc = event.button.y;
							GLdouble mv_matrix [16];
							GLdouble prj_matrix [16];
							GLint vp [4];
							GLdouble xdest, ydest, zdest;
							glGetDoublev(GL_MODELVIEW_MATRIX, mv_matrix);
							glGetDoublev(GL_PROJECTION_MATRIX, prj_matrix);
							glGetIntegerv(GL_VIEWPORT, vp);
							gluUnProject(x_loc, y_loc, 0, mv_matrix, prj_matrix, vp,
										 &xdest, &ydest, &zdest);
							ydest = SCREENTH - ydest;		//SDL --> OGL point conversion
							fileout << "(" << xdest << ", " << ydest << ", "
								<< zdest << ")" << endl;
							if (ydest >= 54 && ydest <= 56 && xdest >= 4 && xdest <= 24.9)	//Change res
							{
								if (trueres == macbook)
								{
									trueres = lowend;
									resolution[0] = 1024;
									resolution[1] = 768;
								} else
								{
									trueres = macbook;
									resolution[0] = 1280;
									resolution[1] = 800;
								}
								SDL_Surface* drawContext;
								Uint32 flags = SDL_OPENGL /*| SDL_FULLSCREEN*/;
								drawContext = SDL_SetVideoMode(resolution[0], resolution[1], 0, flags);
								gluOrtho2D(-2.0, SCREENTW - 2.0, -2.0, SCREENTH - 2.0);
								SDL_GL_SwapBuffers();
								draw_options();
								SDL_GL_SwapBuffers();
							}
							if (ydest >= 8 && ydest <= 10 && xdest > 4 && xdest < 14)	//Return
							{
								Menu::draw_main();
								return;
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

void credits()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	Sprite::draw("alp_t", 4.0, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_h", 6.1, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_i", 8.2, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_s", 10.3, 50.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_g", 13.9, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_a", 16.0, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_m", 18.1, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_e", 20.2, 50.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_m", 23.8, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_a", 25.9, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_d", 28.0, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_e", 30.1, 50.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_b", 33.7, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_y", 35.8, 50.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_a", 39.4, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_d", 41.5, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_a", 43.6, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_m", 45.7, 50.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_h", 49.3, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_i", 51.4, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_n", 53.5, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_t", 55.6, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_z", 57.7, 50.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_w", 61.3, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_i", 63.4, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_t", 65.5, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_h", 67.6, 50.0, 2.0, 2.0, 0.0f, true);
		
	Sprite::draw("alp_m", 71.2, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_u", 73.3, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_c", 75.4, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_h", 77.5, 50.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_h", 81.1, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_e", 83.2, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_l", 85.3, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_p", 87.4, 50.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_f", 91.0, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_r", 93.1, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_o", 95.2, 50.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_m", 97.3, 50.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_a", 4.0, 47.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_l", 6.1, 47.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_a", 8.2, 47.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_s", 10.3, 47.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_t", 12.4, 47.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_a", 14.5, 47.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_i", 16.6, 47.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_r", 18.7, 47.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_l", 22.3, 47.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_y", 24.4, 47.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_n", 26.5, 47.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_n", 28.6, 47.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_p", 4.0, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_a", 6.1, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_c", 8.2, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_m", 10.3, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_a", 12.4, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_n", 14.5, 44.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_i", 18.1, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_s", 20.2, 44.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_c", 23.8, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_o", 25.9, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_p", 28.0, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_y", 30.1, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_r", 32.2, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_i", 34.3, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_g", 36.4, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_h", 38.5, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_t", 40.6, 44.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_o", 44.2, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_f", 46.3, 44.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_n", 49.9, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_a", 52.0, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_m", 54.1, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_c", 56.2, 44.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_o", 58.3, 44.0, 2.0, 2.0, 0.0f, true);
	
	Sprite::draw("alp_r", 4.0, 30.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_e", 6.1, 30.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_t", 8.2, 30.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_u", 10.3, 30.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_r", 12.4, 30.0, 2.0, 2.0, 0.0f, true);
	Sprite::draw("alp_n", 14.5, 30.0, 2.0, 2.0, 0.0f, true);
	SDL_GL_SwapBuffers();
	SDL_Event event;
	bool done = false;
	while(!done)
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type) 
			{
				case SDL_KEYDOWN:
				{
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						Menu::draw_main();
						return;
					}
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					switch (event.button.button)
					{
						case SDL_BUTTON_LEFT:
						{
							int x_loc = event.button.x;
							int y_loc = event.button.y;
							GLdouble mv_matrix [16];
							GLdouble prj_matrix [16];
							GLint vp [4];
							GLdouble xdest, ydest, zdest;
							glGetDoublev(GL_MODELVIEW_MATRIX, mv_matrix);
							glGetDoublev(GL_PROJECTION_MATRIX, prj_matrix);
							glGetIntegerv(GL_VIEWPORT, vp);
							gluUnProject(x_loc, y_loc, 0, mv_matrix, prj_matrix, vp,
										 &xdest, &ydest, &zdest);
							ydest = SCREENTH - ydest;		//SDL --> OGL point conversion
							fileout << "(" << xdest << ", " << ydest << ", "
								<< zdest << ")" << endl;
							if (ydest >= 34 && ydest <= 36 && xdest > 4 && xdest < 16.5)	//Return
							{
								Menu::draw_main();
								return;
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

void main()
{
	if (mute == false)
	{
		//Sound::play("moo_theme");
	}
	Menu::draw_main();
	bool done = false;
	SDL_Event event;
	while(!done)
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type) 
			{
				case SDL_KEYDOWN:
				{
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						done = true;
						menu_quit = true;
						return;
					}
					if (event.key.keysym.sym == SDLK_a)
					{
						Sound::stopmusic();
						done = true;
						menu_quit = false;
						return;
					}
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					switch (event.button.button)
					{
						case SDL_BUTTON_LEFT:
						{
							int x_loc = event.button.x;
							int y_loc = event.button.y;
							GLdouble mv_matrix [16];
							GLdouble prj_matrix [16];
							GLint vp [4];
							GLdouble xdest, ydest, zdest;
							glGetDoublev(GL_MODELVIEW_MATRIX, mv_matrix);
							glGetDoublev(GL_PROJECTION_MATRIX, prj_matrix);
							glGetIntegerv(GL_VIEWPORT, vp);
							gluUnProject(x_loc, y_loc, 0, mv_matrix, prj_matrix, vp,
								&xdest, &ydest, &zdest);
							ydest = SCREENTH - ydest;		//SDL --> OGL point conversion
							fileout << "(" << xdest << ", " << ydest << ", "
								<< zdest << ")" << endl;
							if (ydest >= 20 && ydest <= 22 && xdest >= 4 && xdest <= 14.4)	//Play
							{
								done = true;
								menu_quit = false;
							}
							if (ydest >= 16 && ydest <= 18 && xdest >= 4 && xdest <= 18.6)	//Options
							{
								Menu::options();
							}
							if (ydest >= 12 && ydest <= 14 && xdest >= 4 && xdest <= 18.6)	//Credits
							{
								Menu::credits();
							}
							if (ydest >= 8 && ydest <= 10 && xdest >= 4 && xdest <= 12.3)	//Quit
							{
								done = true;
								menu_quit = true;
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
	Sound::stopmusic();
}

}