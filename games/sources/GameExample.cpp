//
// GameExample.cpp for GameExample in /home/bachinblack/work/cpp/lol/cpp_arcade/games/sources/GameExample
//
// Made by Philippe Bouttereux
// Login   <bachinblack@epitech.eu>
//
// Started on  Sat Apr  8 16:47:02 2017 Philippe Bouttereux
// Last update Sat Apr  8 17:01:33 2017 Philippe Bouttereux
//

#include "GameExample.hpp"

extern "C"
IGame    *initGame(IGraphix *glib)
{
  return new Example(40, 40, glib);
}

extern "C"
void Play(void)
{
  Example ex(50, 50, NULL);
  ex.readInput();
}

Example::Example(const uint16_t& width, const uint16_t& height, IGraphix *glib)
: AGame(width, height, glib)
{

}

Example::~Example() 
{

}
