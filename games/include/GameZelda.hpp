//
// zelda.hpp for zelda in /home/bachinblack/work/cpp/lol/cpp_arcade/games/include/zelda
//
// Made by Philippe Bouttereux
// Login   <bachinblack@epitech.eu>
//
// Started on  Tue Mar 28 01:48:45 2017 Philippe Bouttereux
// Last update Sat Apr  8 17:01:20 2017 Philippe Bouttereux
//

#ifndef __ZELDA_HPP__
# define __ZELDA_HPP__

# define TILES 0
# define OBJECTS 45
# define NBSPRITES 7
# define HCHARACTER 2
# define LCHARACTER 3

# define MAXFRAME EVILFRAMES
# define LINKFRAMES 11
# define EVILFRAMES 9

# define ABS(x) (x < 0 ? -x : x)

enum Tiles
{
  EXIT = 0,
  INPUT = 1,
  FENCE = 2,
};

enum Look
{
  UP = 1,
  RIGHT = 3,
  DOWN = 5,
  LEFT = 7,
  HITUP = 9,
  HITRIGHT = 11,
  HITDOWN = 13,
  HITLEFT = 15
};

#include "AGame.hpp"

class Character
{
public:
  Character(const Grix::Size& size, const std::vector<uint16_t>& tiles, const uint16_t& pixA = 1);
  Grix::Position  _precPos;
  Grix::Position  _pos;
  uint16_t        _look;
  uint16_t        _frame;
  uint16_t        _pixA;
};

class Zelda : public AGame
{
public:
  Zelda(const uint16_t& width, const uint16_t& height, IGraphix *glib);
  ~Zelda();

private:
  void    goForward(void);
  void    blitMap(void) const;
  void    drawTile(const Grix::Position& cpos, const uint16_t& it, const Grix::Position& offset = (Grix::Position {0,0}), const uint16_t& h = 0) const;
  void    blitGuy(const Character& c, const bool& offset) const;

private:
  void      goDown(void);
  void      goLeft(void);
  void      goRight(void);
  void      goUp(void);
  void      refresh(void);
  void      compute(void);
  void      decrlives(void);
  void      Shoot(void);
  void      levelUp(void);
  void      lookAtMe(Character& c);

private:
  Grix::Position              _precPos;
  Grix::IPixArray            *_sprite;
  Grix::IPixArray            *_char[2];
  std::vector<uint16_t>       _objects;
  std::vector<Character>      _chars;
  uint16_t                    _invu;
};

#endif /* __ZELDA_HPP__ */