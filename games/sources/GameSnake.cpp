//
// Snake.cpp for Snake in /home/bachinblack/work/cpp/lol/cpp_arcade/games/sources/Snake
//
// Made by Philippe Bouttereux
// Login   <bachinblack@epitech.eu>
//
// Started on  Fri Mar 17 14:16:19 2017 Philippe Bouttereux
// Last update Sat Apr  8 17:00:14 2017 Philippe Bouttereux
//

#include <iostream>
#include <ctime>
#include "GameSnake.hpp"

extern "C"
IGame    *initGame(IGraphix *glib)
{
  return new Snake(50, 50, glib);
}

extern "C"
void Play(void)
{
  Snake snake(20, 20, NULL);
  snake.readInput();
}

Snake::Snake(const uint16_t& width, const uint16_t& height, IGraphix *glib)
: AGame(width, height, glib)
{
  Grix::Position  pos;
  unsigned i = 0;

  _name = "Snake";
  getHScore();
  _colors[POWERUP] = (Grix::Color){5, 5, 220, 255};
  _pos.x = (_size.x >> 1) - 1;
  _pos.y = (_size.y >> 1) - 1;
  _positions.push_front((Grix::Position { (_size.x >> 1) - 4, (_size.y >> 1) - 1}));
  _positions.push_front((Grix::Position { (_size.x >> 1) - 3, (_size.y >> 1) - 1}));
  _positions.push_front((Grix::Position { (_size.x >> 1) - 2, (_size.y >> 1) - 1}));
  _positions.push_front((Grix::Position { (_size.x >> 1) - 1, (_size.y >> 1) - 1}));
  pos.x = std::rand() % (_size.x - 2) + 1;
  pos.y = std::rand() % (_size.y - 2) + 1;
  _tiles[CONVERT(pos.x, pos.y)] = POWERUP;
  _applePos = pos;
  _snakeSize = 4;
  for (auto& it : _tiles)
  {
    if ((i > width && i < ((_size.y - 1) * width) && i % _size.y != 0 && i % (_size.y) != _size.y - 1) == false)
      it = BLOCK;
    ++i;
  }
  _colors[BLOCK] = (Grix::Color){120, 120, 120, 255};
  for (unsigned i=0; i<3; ++i)
  {
    pos.x = std::rand() % _size.x;
    pos.y = std::rand() % _size.y;
    if (_tiles[CONVERT(pos.x, pos.y)] != EMPTY)
      --i;
    else
      _tiles[CONVERT(pos.x, pos.y)] = OTHER;
  }
}

Snake::~Snake() {}

void  Snake::whereAmI(void)
{
  arcade::WhereAmI  test;

  test.type = arcade::CommandType::WHERE_AM_I;
  test.lenght = _snakeSize;
  std::cout.write(reinterpret_cast<char *>(&test), sizeof(arcade::WhereAmI));
  for (auto& it : _positions)
  {
    std::cout.write(reinterpret_cast<char *>(&it.x), 2);
    std::cout.write(reinterpret_cast<char *>(&it.y), 2);
  }
}

void  Snake::printMap(void)
{
  arcade::GetMap test;

  test.type = arcade::CommandType::GET_MAP;
  test.width = _size.x;
  test.height = _size.y;
  std::cout.write(reinterpret_cast<char *>(&test), sizeof(arcade::GetMap));
  for (auto& it : _tiles)
  {
    std::cout.write(reinterpret_cast<char *>(&it), 2);
  }
}

void    Snake::levelUp(void)
{
  Grix::Position  pos;

  for (unsigned i=0; i<1; ++i)
  {
    pos.x = std::rand() % _size.x;
    pos.y = std::rand() % _size.y;
    if (_tiles[CONVERT(pos.x, pos.y)] != EMPTY)
      --i;
    else
      _tiles[CONVERT(pos.x, pos.y)] = OTHER;
  }
  _gameFPS += 4;
}

bool  Snake::checkPos(const Grix::Position& pos) const
{
  for (auto& it : _positions)
  {
    if (it.x == pos.x && it.y == pos.y)
      return false;
  }
  return true;
}

void    Snake::addPowerUp(void)
{
  Grix::Position  pos;

  ++_snakeSize;
  for (unsigned i=0; i<1; ++i)
  {
    pos.x = std::rand() % _size.x;
    pos.y = std::rand() % _size.y;
    _applePos = pos;
    if (!checkPos(pos))
      --i;
    else if (_tiles[CONVERT(pos.x, pos.y)] != EMPTY)
      --i;
    else
      _tiles[CONVERT(pos.x, pos.y)] = POWERUP;
  }
  if (_snakeSize % 4 == 0)
    levelUp();
}

void  Snake::blitGuy(void) const
{
  for (auto& it : _positions)
    drawTile(it, _colors[PLAYER]);
}

void Snake::addPos(void)
{
  _positions.push_front(_pos);
  if (_snakeSize < _positions.size())
    _positions.pop_back();
  if (_tiles[_pos.x + _pos.y * _size.x] == POWERUP)
  {
    _score += 100;
    _tiles[_pos.x + _pos.y * _size.x] = EMPTY;
    addPowerUp();
  }
  else if (_tiles[_pos.x + _pos.y * _size.x] == OTHER || _tiles[_pos.x + _pos.y * _size.x] == BLOCK)
  {
    refresh();
    return ;
  }
  for(std::deque<Grix::Position>::iterator it = _positions.begin() + 1; it != _positions.end(); ++it)
  {
    if (_pos.x == it->x && _pos.y == it->y)
    {
      refresh();
      return ;
    }
  }
}

void    Snake::refresh(void)
{
  Grix::Position  pos;

  Defeat();
  _t0 = Clock::now();
  _score = 0;
  _positions.clear();
  pos.x = std::rand() % _size.x;
  pos.y = std::rand() % _size.y;
  _snakeSize = 4;
  _positions.push_front((Grix::Position { (_size.x >> 1) - 4, (_size.y >> 1) - 1}));
  _positions.push_front((Grix::Position { (_size.x >> 1) - 3, (_size.y >> 1) - 1}));
  _positions.push_front((Grix::Position { (_size.x >> 1) - 2, (_size.y >> 1) - 1}));
  _positions.push_front((Grix::Position { (_size.x >> 1) - 1, (_size.y >> 1) - 1}));
  for (auto& it : _tiles)
    it = EMPTY;
  _applePos = pos;
  _gameFPS = 18;
  _tiles[CONVERT(pos.x, pos.y)] = POWERUP;
  _last = 0;
  _pos.x = (_size.x >> 1) - 1;
  _pos.y = (_size.y >> 1) - 1;
  for (unsigned i=0; i<3; ++i)
  {
    pos.x = std::rand() % _size.x;
    pos.y = std::rand() % _size.y;
    _tiles[CONVERT(pos.x, pos.y)] = OTHER;
  }
  _glib->setFPS(18);
}

void Snake::goUp(void)      { if (_pos.y > 0) { --_pos.y; addPos();} else { refresh();} }

void Snake::goDown(void)    { if (_pos.y < _size.y-1) { ++_pos.y; addPos();} else { refresh();} }

void Snake::goLeft(void)    { if (_pos.x > 0) { --_pos.x; addPos();} else { refresh();} }

void Snake::goRight(void)   { if (_pos.x < _size.x-1) { ++_pos.x; addPos();} else { refresh();} }

void Snake::goForward(void) { if (_last) { _functions[_last]();} }

void Snake::compute(void)
{
  if (_glib != NULL)
    _glib->setFPS(_gameFPS);
}
