/******************************************************\
|This file and its contents ©Copyright 2008 Adam Hintz |
|and Alastair Lynn. You may not redistribute or use    |
|parts or the whole of this code without our express   |
|written permission. All rights reserved.              |
\******************************************************/

#include "pacman01.h"

extern int resolution [2];

typedef std::string RES;
const RES macbook = "1280x800";
const RES lowend = "1024x768";
extern RES trueres;

namespace Menu
{

void draw_main();
void draw_options();
void main();
void options();
void credits();

}