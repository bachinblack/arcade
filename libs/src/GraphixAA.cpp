//
// GraphixAA.cpp for lol in /home/tetra/rendu/cpp/cpp_arcade/libs
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Thu Mar  9 19:05:36 2017 Arthur Josso
// Last update Thu Mar 23 17:12:04 2017 Arthur Josso
//

#include <iostream>
#include <cstring>
#include "GraphixAA.hpp"
#include "Errors.hpp"

GraphixAA::GraphixAA() : AGraphix()
{
  _context = aa_autoinit(&aa_defparams);
  if (_context == NULL)
    throw (GraphicError("Failed to open AA"));
  if (aa_autoinitkbd(_context, 0) == 0)
    throw (GraphicError("Failed to init keyboard for AA"));
  _keyTab =
    {
      {Key::_ESCAPE, AA_ESC},
      {Key::_z, 'z'},
      {Key::_s, 's'},
      {Key::_q, 'q'},
      {Key::_d, 'd'},
      {Key::_QUOTEDBL, '\"'},
      {Key::_QUOTE, '\''},
      {Key::_AMPERSAND, '&'},
      {Key::_LEFTPAREN, '('},
      {Key::_MINUS, '-'},
      {Key::_UNDERSCORE, '_'},
      {Key::_RETURN, '\r'}
    };
}

GraphixAA::~GraphixAA()
{
  aa_close(_context);
}

const uint8_t * GraphixAA::getKbSate()
{
  int key;

  while ((key = aa_getkey(_context, 0)) != AA_NONE)
    for (auto& it : _keyTab)
      _kbState[it.first] = key == it.second ? true : false;
  return (_kbState);
}

bool GraphixAA::processFrame(GameLoop userLoop, void *userData)
{
  // game loop
  if (!userLoop(userData))
    return (false);

  flush();
  return (true);
}

void GraphixAA::flush()
{
  Grix::Position pos;

  // blit PA to screen
  for (pos.x = 0; pos.x < _PA->getSize().x; pos.x++)
    for (pos.y = 0; pos.y < _PA->getSize().y; pos.y++)
      {
	Grix::Color color32 = _PA->getPixel(pos);
	uint8_t color8 =
	  (color32.argb[Grix::RED] +
	   color32.argb[Grix::GREEN] +
	   color32.argb[Grix::BLUE]) / 3;
	aa_putpixel(_context,
		    MAP0(pos.x, _PA->getSize().x, aa_scrwidth(_context) * 2),
		    MAP0(pos.y, _PA->getSize().y, aa_scrheight(_context) * 2),
		    color8);
      }
  aa_flush(_context);
  aa_render(_context, &aa_defrenderparams, 0, 0,
	    aa_scrwidth(_context), aa_scrheight(_context));
  
  // clear screen
  _PA->clear();

  // pause the lib if frame limit
  _frameLimit();
}

extern "C"
IGraphix	*create()
{
  return (new GraphixAA);
}
