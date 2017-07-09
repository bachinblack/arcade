//
// GSnake.hpp for GSnake in /home/bachinblack/work/cpp/lol/cpp_arcade/games/include/GSnake
//
// Made by Philippe Bouttereux
// Login   <bachinblack@epitech.eu>
//
// Started on  Fri Mar 17 14:13:44 2017 Philippe Bouttereux
// Last update Sat Apr  8 17:00:17 2017 Philippe Bouttereux
//

#ifndef __GSNAKE_HPP__
# define __GSNAKE_HPP__

#include "AGame.hpp"

class Snake : public AGame
{
public:
  Snake(const uint16_t& width, const uint16_t& height, IGraphix *glib);
  ~Snake();
  void compute();

public:
  void    blitGuy(void) const;
  void    addPowerUp(void);
  void    refresh(void);

private:
  bool    checkPos(const Grix::Position& pos) const;
  void    goForward(void);
  void    goDown(void);
  void    goLeft(void);
  void    goRight(void);
  void    goUp(void);
  void    addPos(void);
  void    levelUp(void);
  void    whereAmI(void);
  void    printMap(void);

private:
  Grix::Position              _applePos;
  unsigned int                _snakeSize;
};

extern "C"
void play();

#endif /* __GSNAKE_HPP__ */
