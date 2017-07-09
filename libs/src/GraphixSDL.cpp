//
// GraphixSDL.cpp for lol in /home/tetra/rendu/cpp/cpp_arcade/libs
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Thu Mar  9 19:05:36 2017 Arthur Josso
// Last update Wed Mar 22 19:27:17 2017 Arthur Josso
//

#include <iostream>
#include "GraphixSDL.hpp"
#include "Errors.hpp"

GraphixSDL::GraphixSDL() : AGraphix()
{
  SDL_WM_SetCaption("Arcade - SDL", NULL);
  _context = SDL_SetVideoMode(_PA->getSize().x, _PA->getSize().y, 32, SDL_HWSURFACE);
  if (_context == NULL)
    throw (GraphicError("Failed to open SDL"));
}

GraphixSDL::~GraphixSDL()
{
  SDL_Quit();
}

const uint8_t * GraphixSDL::getKbSate()
{
  const Uint8 *tmp_keys;

  tmp_keys = SDL_GetKeyState(NULL);
  memcpy(_kbState, tmp_keys, Key::LAST);
  return (_kbState);
}

bool GraphixSDL::processFrame(GameLoop userLoop, void *userData)
{
  if (!userLoop(userData))
    return (false);

  flush();
  
  return (true);
}

void GraphixSDL::flush()
{
  Grix::Position pos;
  
  // flush
  if (SDL_MUSTLOCK(_context))
    if (SDL_LockSurface(_context) < 0)
      return;
  for (pos.x = 0; pos.x < _PA->getSize().x; pos.x++)
    for (pos.y = 0; pos.y < _PA->getSize().y; pos.y++)
      ((uint32_t*)_context->pixels)[pos.y * _PA->getSize().x + pos.x] =
	_PA->getPixel(pos).full;
  if (SDL_MUSTLOCK(_context))
    SDL_UnlockSurface(_context);
  SDL_UpdateRect(_context, 0, 0, _PA->getSize().x, _PA->getSize().y);

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
  return (new GraphixSDL);
}
