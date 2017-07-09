//
// PutText.cpp for lol in /home/tetra/rendu/cpp/cpp_arcade/libs
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Tue Mar 21 14:21:47 2017 Arthur Josso
// Last update Wed Mar 22 19:29:18 2017 Arthur Josso
//

#include <iostream>
#include "AGraphix.hpp"

static Grix::Size charSize = {5, 7};

void AGraphix::putChar(char c, Grix::Position const & pos,
		       Grix::Color color, uint8_t size)
{
  Grix::Position charPos = {c * charSize.x, 0};
  Grix::Position endPos = {pos.x + charSize.x * size, pos.y + charSize.y * size};
  Grix::Position tmp;
  Grix::Position tmpChar;

  for (tmp.x = pos.x; tmp.x < endPos.x; tmp.x++)
    {
      for (tmp.y = pos.y; tmp.y < endPos.y; tmp.y++)
	{
	  tmpChar.x = MAP(tmp.x, pos.x, endPos.x, charPos.x, charPos.x + charSize.x);
	  tmpChar.y = MAP(tmp.y, pos.y, endPos.y, charPos.y, charPos.y + charSize.y);
	  if (_font->getPixel(tmpChar).argb[Grix::ALPHA] == 0xFF)
	    _PA->setPixel(tmp, color);
	}
    }
}

void AGraphix::putText(std::string const & text, Grix::Position const & pos,
		       Grix::Color color, uint8_t size, bool centered)
{
  Grix::Position tmp = pos;

  if (centered)
    tmp.x -= ((charSize.x + 1) * size * text.size()) / 2;
  for (size_t i = 0; text[i]; i++)
    {
      putChar(text[i], tmp, color, size);
      tmp.x += (charSize.x + 1) * size;
    }
}
