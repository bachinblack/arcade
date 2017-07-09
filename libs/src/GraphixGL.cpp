//
// GraphixSDL.cpp for lol in /home/tetra/rendu/cpp/cpp_arcade/libs
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Thu Mar  9 19:05:36 2017 Arthur Josso
// Last update Fri Mar 24 15:00:28 2017 Arthur Josso
//

#include <iostream>
#include "GraphixGL.hpp"
#include "Errors.hpp"

GraphixGL::GraphixGL() : AGraphix()
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    throw (GraphicError("Failed to init GL context"));

  _context = SDL_CreateWindow("Arcade - GL", 0, 0, _PA->getSize().x,
			      _PA->getSize().y, SDL_WINDOW_OPENGL);
  if (!_context)
    throw (GraphicError("Failed to open GL"));

  _GLcontext = SDL_GL_CreateContext(_context);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  
  SDL_GL_SetSwapInterval(1);

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glRotatef(180, 1.0f, 0.0f, 0.0f);
  SDL_GL_SwapWindow(_context);
}

GraphixGL::~GraphixGL()
{
  SDL_GL_DeleteContext(_GLcontext);
  SDL_DestroyWindow(_context);
  SDL_Quit();
}

const uint8_t * GraphixGL::getKbSate()
{
  const Uint8 *tmp_keys;

  SDL_PumpEvents();
  tmp_keys = SDL_GetKeyboardState(NULL);
  memset(_kbState, 0, Key::LAST);
  for (int key = Key::_FIRST; key < Key::LAST; key++)
    _kbState[key] = tmp_keys[SDL_GetScancodeFromKey(key)];
  return (_kbState);
}

bool GraphixGL::processFrame(GameLoop userLoop, void *userData)
{
  if (!userLoop(userData))
    return (false);

  flush();
  
  return (true);
}

void GraphixGL::flush()
{
  // flush
  Grix::Position pos;
  Grix::Color color;
  Grix::Size ws = _PA->getSize();
  float psx = 2.0 / ws.x;
  float psy = 2.0 / ws.y;
  float ppx;
  float ppy;
  
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  for (pos.x = 0; pos.x < ws.x; pos.x++)
    for (pos.y = 0; pos.y < ws.y; pos.y++)
      {
	color = _PA->getPixel(pos);
	glBegin(GL_QUADS);
	glColor3f(FCOLOR(color.argb[Grix::RED]), FCOLOR(color.argb[Grix::GREEN]),
		  FCOLOR(color.argb[Grix::BLUE]));
	ppx = FMAP(pos.x, ws.x, 2.0) - 1.0;
	ppy = FMAP(pos.y, ws.y, 2.0) - 1.0;
	glVertex2f(ppx, ppy);
	glVertex2f(ppx + psx, ppy);
	glVertex2f(ppx + psx, ppy + psy);
	glVertex2f(ppx, ppy + psy);
	glEnd();
      }
  glFlush();
  SDL_GL_SwapWindow(_context);

  // clear screen
  _PA->clear();

  // pause the lib if frame limit
  _frameLimit();

  SDL_Event event;
  while (SDL_PollEvent(&event))
    if (event.type == SDL_QUIT)
      _kbState[Key::_ESCAPE] = true;
}

extern "C"
IGraphix	*create()
{
  return (new GraphixGL);
}
