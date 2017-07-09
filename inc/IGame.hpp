//
// IGame.hpp for IGame in /home/bachinblack/work/cpp/cpp_arcade/inc/IGame
//
// Made by Philippe Bouttereux
// Login   <bachinblack@epitech.eu>
//
// Started on  Wed Mar 15 00:16:34 2017 Philippe Bouttereux
// Last update Wed Apr  5 11:59:03 2017 Philippe Bouttereux
//

#ifndef __IGAME_HPP__
# define __IGAME_HPP__

#include "IGraphix.hpp"

#define CONVERT(posx, posy) _size.x * posy + posx

class IGame
{
public:
  virtual ~IGame() {};
  virtual void    updateMap(const std::string& name, const std::string& code) = 0;
  virtual void    compute(void) = 0;
  virtual void    setGrixLib(IGraphix *lib) = 0;
  virtual void    getInput() = 0;
  virtual void    printInfos(void) = 0;
  virtual void    sendOutput(void) = 0;
};

enum    In
{
  WHERE_AM_I  = 0,
  GET_MAP     = 1,
  GO_UP       = 2,
  GO_DOWN     = 3,
  GO_LEFT     = 4,
  GO_RIGHT    = 5,
  GO_FORWARD  = 6,
  SHOOT       = 7,
  ILLEGAL     = 8,
  PLAY        = 9
};


enum    TileType
{
  EMPTY       = 0,
  BLOCK       = 1,
  OBSTACLE    = 2,
  EVIL_DUDE   = 3,
  EVIL_SHOOT  = 4,
  MY_SHOOT    = 5,
  POWERUP     = 6,
  OTHER       = 7,
  PLAYER      = 8,
  NONE        = 9
};

extern "C"
IGame    *initGame(IGraphix *glib);

extern "C"
bool    loopGame(void *data);

#endif /* __IGAME_HPP__ */
