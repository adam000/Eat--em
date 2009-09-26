/******************************************************\
|This file and its contents ©Copyright 2008 Adam Hintz |
|and Alastair Lynn. You may not redistribute or use    |
|parts or the whole of this code without our express   |
|written permission. All rights reserved.              |
\******************************************************/

#include "sprite.h"
#include "pacman01.h"

#include <OpenGL/gl.h>
#include <map>
#include "file_manager.h"
#include "tinyxml.h"
#include <SDL_image/SDL_image.h>

namespace
{

struct texsheet
{
	SDL_Surface* surface;
	GLuint texture;
	unsigned refcount;
	
	texsheet ( SDL_RWops* ops, int freesrc )
	: refcount(1)
	{
		surface = IMG_Load_RW(ops, freesrc);
		assert(surface);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture);
		glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		if (surface->format->BytesPerPixel == 3)
		{
			glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, 3, surface->w, surface->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, 4, surface->w, surface->h, 0, GL_RGBA,
						 GL_UNSIGNED_INT_8_8_8_8, surface->pixels);
		}
	}
	
	~texsheet ()
	{
	}
	
	void retain ()
	{
		refcount++;
	}
	
	void release ()
	{
		refcount--;
		if (refcount == 0)
			delete this;
	}
};

struct sprite
{
	texsheet* sheet;
	unsigned x, y;
	unsigned w, h;
};

std::map<std::string, sprite*> sprites;

sprite* getsprite ( const std::string& name )
{
	std::map<std::string, sprite*>::iterator iter = sprites.find(name);
	if (iter == sprites.end())
		return NULL;
	else
		return iter->second;
}

}

namespace Sprite
{

void load ( const std::string& name, const std::string& sourcefile )
{
	SDL_RWops* rwops = FM->OpenFile(sourcefile);
	if (rwops)
	{
		texsheet* ts = new texsheet ( rwops, 1 );
		sprite* sp = new sprite;
		sp->sheet = ts;
		sp->x = sp->y = 0;
		sp->w = ts->surface->w;
		sp->h = ts->surface->h;
		sprites[name] = sp;
	}
	else
	{
		sprites[name] = NULL;
	}
}

void load_set ( const std::string& setfile )
{
	SDL_RWops* conf = FM->OpenFile(setfile + ".sheet");
	assert(conf);
	if (conf)
	{
		unsigned long s = SDL_RWseek(conf, 0, SEEK_END);
		void* data = malloc(s);
		assert(data);
		SDL_RWseek(conf, 0, SEEK_SET);
		SDL_RWread(conf, data, s, 1);
		SDL_RWclose(conf);
		TiXmlDocument* doc = new TiXmlDocument;
		assert(doc);
		doc->Parse((const char*)data, NULL, TIXML_ENCODING_UTF8);
		free(data);
		TiXmlElement* root = doc->RootElement();
		assert(root);
		const char* sheetname = root->Attribute("src");
		assert(sheetname);
		SDL_RWops* sheetrw = FM->OpenFile(sheetname);
		assert(sheetrw);
		texsheet* st = new texsheet(sheetrw, 1);
		assert(st);
		TiXmlElement* spritenode = NULL;
		while (spritenode = dynamic_cast<TiXmlElement*>(root->IterateChildren(spritenode)))
		{
			int x, y, w, h;
			spritenode->Attribute("x", &x);
			spritenode->Attribute("y", &y);
			spritenode->Attribute("width", &w);
			spritenode->Attribute("height", &h);
			sprite* sp = new sprite;
			sp->sheet = st;
			st->retain();
			sp->w = w;
			sp->h = h;
			sp->x = x;
			sp->y = y;
			const char* name = spritenode->Attribute("name");
			assert(name);
			sprites[name] = sp;
		}
		st->release();
	}
}

bool loaded ( const std::string& sprite )
{
	return (getsprite(sprite));
}

void draw (const std::string& name, GLfloat x, GLfloat y, GLfloat mw, GLfloat mh, GLfloat rotz, bool resize)
{
	sprite* sp = getsprite(name);
	if (!sp)
	{
		problem(112);
	}
	glPushMatrix();
	glTranslatef(x, y, 0.0f);
	glRotatef(rotz, 0.0f, 0.0f, 1.0f);
	
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, sp->sheet->texture);
	
	glColor3f(1.0, 1.0, 1.0);
	if(resize == true)
	{
		GLfloat tex_stuff [8] =
		{sp->x, sp->y + sp->h,
		sp->x + sp->w, sp->y + sp->h,
		sp->x + sp->w, sp->y,
		sp->x, sp->y};
		
		GLfloat vert_stuff [8] = 
		{0, 0,
		mw, 0,
		mw, mh,
		0, mh};
		
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, tex_stuff);
		glVertexPointer(2, GL_FLOAT, 0, vert_stuff);
		glDrawArrays(GL_QUADS, 0, 4);
	} else
	{
		GLfloat tex_stuff [8] =
		{sp->x, sp->y + sp->h,
		sp->x + sp->w, sp->y + sp->h,
		sp->x + sp->w, sp->y,
		sp->x, sp->y};
				
		GLfloat vert_stuff [8] = 
		{0, 0,
		sp->w * mw, 0,
		sp->w * mw, sp->h * mh,
		0, sp->h * mh};
				
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, tex_stuff);
		glVertexPointer(2, GL_FLOAT, 0, vert_stuff);
		glDrawArrays(GL_QUADS, 0, 4);
	}

	glPopMatrix();
}

}

