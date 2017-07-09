//
// PixArray.cpp for lol in /home/tetra/rendu/cpp/cpp_arcade/libs
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Wed Mar 15 18:11:15 2017 Arthur Josso
// Last update Fri Mar 24 19:01:18 2017 Arthur Josso
//

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "IGraphix.hpp"
#include "PixArray.hpp"

Grix::PixArray::PixArray(Size const & size, Color const & color)
  : _size(size)
{
  _buffer = new Color [_size.x * _size.y];
  for (size_t i = 0; i < _size.x * _size.y; i++)
    _buffer[i] = color;
}

Grix::PixArray::~PixArray()
{
  delete [] _buffer;
}

void Grix::PixArray::setSize(Size const & size)
{
  Color *tmp;
  Position pos;

  if (_size.x == size.x && _size.y == size.y)
    return;
  tmp = new Color [size.x * size.y];
  for (pos.x = 0; pos.x < size.x; pos.x++)
    for (pos.y = 0; pos.y < size.y; pos.y++)
      tmp[pos.y * size.x + pos.x] =
	getPixel((Position){MAP0(pos.x, size.x, _size.x),
	      MAP0(pos.y, size.y, _size.y)});
  delete [] _buffer;
  _size = size;
  _buffer = tmp;
}

Grix::Color const & Grix::PixArray::getPixel(Position const & pos) const
{
  if (pos.x >= _size.x || pos.y >= _size.y)
    return (_buffer[0]);
  return (_buffer[pos.y * _size.x + pos.x]);
}

void Grix::PixArray::setPixel(Position const & pos, Color const & color)
{
  if (pos.x >= _size.x || pos.y >= _size.y)
    return ;
  if (color.argb[ALPHA] == 0xFF)
    _buffer[pos.y * _size.x + pos.x] = color;
}

void Grix::PixArray::clear()
{
  memset(_buffer, 0, sizeof(uint32_t) * _size.x * _size.y);
}

Grix::Size const & Grix::PixArray::getSize() const { return (_size); }

typedef struct
{
  unsigned short magic;
  unsigned int  size;
  unsigned int  none;
  unsigned int  start;
  unsigned int  header_size;
  unsigned int  width;
  unsigned int  height;
  unsigned short nb_plan;
  unsigned short bpp;
  unsigned int  compression;
  unsigned int  img_size;
  unsigned int  ppm_width;
  unsigned int  ppm_height;
  unsigned int  nb_col_pal;
  unsigned int  nb_col_imp;
} __attribute__ ((packed)) t_bmp;

Grix::PixArray::PixArray(std::string const & bmpPath)
{
  std::ifstream file;
  t_bmp header;
  Color col, buff;

  file.open(bmpPath, std::ios::in | std::ios::binary);
  if (!file.is_open())
    goto failtoload;
  file.seekg(0);
  if (!file.read(reinterpret_cast<char*>(&header), sizeof(t_bmp)))
    {
      file.close();
      goto failtoload;
    }
  file.seekg(header.start);

  _size.x = header.width;
  _size.y = header.height;
  _buffer = new Color [_size.x * _size.y]();

  for (uint32_t i = 0; i < _size.x * _size.y; i++)
    {
      if (!file.read(reinterpret_cast<char*>(&buff), sizeof(Color)))
	break;
      col.full = buff.full >> 8;
      col.argb[3] = buff.argb[0];
      setPixel((Position){i % _size.x, _size.y - i / _size.x - 1}, col);
    }
  file.close();
  return;
  
 failtoload:
  std::cerr << "ERROR: Cannot load \"" << bmpPath << "\" as a bmp" << std::endl;
  _size.x = 1;
  _size.y = 1;
  _buffer = new Color [_size.x * _size.y]();
}

bool Grix::PixArray::isValid()
{
  if (_size.x == 1 && _size.y == 1 && _buffer[0].full == 0)
    return (false);
  return (true);
}
