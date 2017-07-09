//
// GameExample.hpp for GameExample in /home/bachinblack/work/cpp/lol/cpp_arcade/games/include/GameExample
//
// Made by Philippe Bouttereux
// Login   <bachinblack@epitech.eu>
//
// Started on  Sat Apr  8 16:47:22 2017 Philippe Bouttereux
// Last update Sat Apr  8 17:01:29 2017 Philippe Bouttereux
//

#ifndef __GAME_EXAMPLE_HPP__
# define __GAME_EXAMPLE_HPP__

#include "AGame.hpp"

class Example : public AGame
{
public:
  Example(const uint16_t& width, const uint16_t& height, IGraphix *glib);
  ~Example();
};

#endif /* __GAME_EXAMPLE_HPP__ */