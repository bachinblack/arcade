//
// GameQix.cpp for GameQix in /home/bachinblack/work/cpp/lol/cpp_arcade/games/include/GameQix
//
// Made by Philippe Bouttereux
// Login   <bachinblack@epitech.eu>
//
// Started on  Tue Mar 21 16:36:21 2017 Philippe Bouttereux
// Last update Sun Apr  9 18:50:14 2017 Philippe Bouttereux
//

#include <iostream>
#include "GameQix.hpp"

extern "C"
IGame    *initGame(IGraphix *glib)
{
  return new Qix(100, 100, glib);
}

extern "C"
void Play(void)
{
  Qix qix(20, 20, NULL);
  qix.readInput();
}

Qix::Qix(const uint16_t& width, const uint16_t& height, IGraphix *glib)
: AGame(width, height, glib)
{
  uint16_t i = 0;

  _name = "Qix";
  getHScore();
  _evils.push_back((Grix::Position) {static_cast<uint32_t>(width) / 3, static_cast<uint32_t>(_size.y) >> 1});
  _evils.push_back((Grix::Position) {0, static_cast<uint32_t>(_size.y) - 1});
  _evils.push_back((Grix::Position) {static_cast<uint32_t>(width) - 1, 0});
  _lpos.x = 2;
  _lpos.y = 2;
  _max = width * _size.y * 0.75;
  _pos.x = (width >> 1) - 1;
  _pos.y = _size.y - 1;
  for (auto& it : _tiles)
  {
    if (i > width && i < ((_size.y - 1) * width) && i % _size.y != 0 && i % (_size.y) != _size.y - 1)
      it = BLOCK;
    ++i;
  }
}

Qix::~Qix() { }

void    Qix::refresh(void)
{
  uint16_t i = 0;

  Defeat();
  _t0 = Clock::now();
  _score = 0;
  _tiles[CONVERT(_evils[1].x, _evils[1].y)] = EMPTY;
  _tiles[CONVERT(_evils[2].x, _evils[2].y)] = EMPTY;
  _evils[0] = (Grix::Position) {static_cast<uint32_t>(_size.x) >> 1, static_cast<uint32_t>(_size.y) >> 1};
  _evils[1] = (Grix::Position) {0, 2};
  _evils[2] = (Grix::Position) {static_cast<uint32_t>(_size.x) - 1, 2};
  _pos.x = (_size.x >> 1) - 1;
  _pos.y = _size.y - 1;
  for (auto& it : _tiles)
  {
    if (i > _size.x && i < ((_size.y - 1) * _size.x) && i % _size.y != 0 && i % (_size.y) != _size.y - 1)
      it = BLOCK;
    ++i;
  }  
}

bool    Qix::check(Grix::Position pos)
{
  bool  ret = true;
  if (_tiles[CONVERT(pos.x, pos.y)] == EVIL_DUDE)
    return false;
  if (_tiles[CONVERT(pos.x, pos.y)] == BLOCK)
  {
    _tiles[CONVERT(pos.x, pos.y)] = MY_SHOOT;
    --pos.x;
    if (check(pos) == false)
      ret = false;
    --pos.y;
    ++pos.x;
    if (check(pos) == false)
      ret = false;
    pos.y += 2;
    if (check(pos) == false)
      ret = false;
    --pos.y;
    ++pos.x;
    if (check(pos) == false)
      ret = false;
  }
  return ret;
}

void    Qix::unfill(Grix::Position pos)
{
  if (_tiles[CONVERT(pos.x, pos.y)] == MY_SHOOT)
  {
    _tiles[CONVERT(pos.x, pos.y)] = BLOCK;
    --pos.x;
    unfill(pos);
    --pos.y;
    ++pos.x;
    unfill(pos);
    pos.y += 2;
    unfill(pos);
    --pos.y;
    ++pos.x;
    unfill(pos);
  }
}

void  Qix::Erase(void)
{
  _score = 0;
  for (auto& it : _tiles)
  {
    switch(it)
    {
      case OBSTACLE: { it = EMPTY; break;}
      case MY_SHOOT: { ++_score; break;}
      case EMPTY: { ++_score;}
    }
  }
  if (_score > _max)
    Victory();
}

void    Qix::goDown(void)
{
  if (_pos.y < _size.y-1 && _tiles[CONVERT(_pos.x, (_pos.y+1))] != MY_SHOOT)
  {
    if (_tiles[CONVERT(_pos.x, (_pos.y + 1))] == EMPTY && _pos.y > 0 && _pos.x > 0 && _pos.x < _size.x-1)
    {
      Grix::Position  pos = { _pos.x - 1, _pos.y};

      if (check(pos) == false)
      {
        unfill(pos);
        pos.x += 2;
        check(pos);
      }
      Erase();
    }
    ++_pos.y;
  }
}

void    Qix::goLeft(void)
{
  if (_pos.x > 0 && _tiles[CONVERT((_pos.x-1), _pos.y)] != MY_SHOOT)
  {
    if (_tiles[CONVERT((_pos.x-1), _pos.y)] == EMPTY && _pos.x < _size.x-1 && _pos.y > 0 && _pos.y < _size.y-1)
    {
      Grix::Position  pos = { _pos.x, _pos.y - 1};

      if (check(pos) == false)
      {
        unfill(pos);
        pos.y += 2;
        check(pos);
      }
      Erase();
    }
    --_pos.x;
  }
}

void    Qix::goRight(void)
{
  if (_pos.x < _size.x-1 && _tiles[CONVERT((_pos.x+1), _pos.y)] != MY_SHOOT)
  {
    if (_tiles[CONVERT((_pos.x+1), _pos.y)] == EMPTY && _pos.x < _size.x-1 && _pos.y > 0 && _pos.y < _size.y-1)
    {
      Grix::Position  pos = { _pos.x, _pos.y - 1};

      if (check(pos) == false)
      {
        unfill(pos);
        pos.y += 2;
        check(pos);
      }
      Erase();
    }
    ++_pos.x;
  }
}

void    Qix::goUp(void)
{
  if (_pos.y > 0 && _tiles[CONVERT(_pos.x, (_pos.y-1))] != MY_SHOOT)
  {
    if (_tiles[CONVERT(_pos.x, (_pos.y-1))] == EMPTY && _pos.y < _size.y-1 && _pos.x > 0 && _pos.x < _size.x-1)
    {
      Grix::Position  pos = { _pos.x-1, _pos.y};

      if (check(pos) == false)
      {
        unfill(pos);
        pos.x += 2;
        check(pos);
      }
      Erase();
    }
    --_pos.y;
  }
}

void  Qix::moveEvilsCW(Grix::Position& pos)
{
  if      (getTile(pos.x-1, pos.y) == (BLOCK || OBSTACLE) && getTile(pos.x, pos.y+1) == EMPTY){++pos.y;}
  else if (getTile(pos.x+1, pos.y) == (BLOCK || OBSTACLE) && getTile(pos.x, pos.y-1) == EMPTY){--pos.y;}
  else if (getTile(pos.x, pos.y+1) == (BLOCK || OBSTACLE) && getTile(pos.x+1, pos.y) == EMPTY){++pos.x;}
  else if (getTile(pos.x, pos.y-1) == (BLOCK || OBSTACLE) && getTile(pos.x-1, pos.y) == EMPTY){--pos.x;}

  else if (getTile(pos.x-1, pos.y+1) == (BLOCK || OBSTACLE) && getTile(pos.x, pos.y+1) == EMPTY) {++pos.y;}
  else if (getTile(pos.x+1, pos.y+1) == (BLOCK || OBSTACLE) && getTile(pos.x+1, pos.y) == EMPTY) {++pos.x;}
  else if (getTile(pos.x-1, pos.y-1) == (BLOCK || OBSTACLE) && getTile(pos.x-1, pos.y) == EMPTY) {--pos.x;}
  else if (getTile(pos.x+1, pos.y-1) == (BLOCK || OBSTACLE) && getTile(pos.x, pos.y-1) == EMPTY) {--pos.y;}
}

void  Qix::moveEvilsRand(void)
{
  Grix::Position  rpos;
  unsigned        i = 0;

  rpos.x = std::rand() % 3 - 1;
  rpos.y = std::rand() % 3 - 1;
  while (_tiles[CONVERT((_evils[0].x+rpos.x), (_evils[0].y+rpos.y))] != BLOCK || (rpos.x == _lpos.x && rpos.y == _lpos.y))
  {
    ++i;
    rpos.x = std::rand() % 3 - 1;
    rpos.y = std::rand() % 3 - 1;
    if (_tiles[CONVERT((_evils[0].x+rpos.x), (_evils[0].y+rpos.y))] == OBSTACLE || i >= 10000)
    {
      refresh();
      break;
    }
  }
  _evils[0].x += rpos.x;
  _evils[0].y += rpos.y;
  _lpos.x = -rpos.x;
  _lpos.y = -rpos.y;
}

void Qix::compute()
{
  _glib->setFPS(20);
  _tiles[CONVERT(_evils[0].x, _evils[0].y)] = BLOCK;
  _tiles[CONVERT(_evils[1].x, _evils[1].y)] = EMPTY;
  _tiles[CONVERT(_evils[2].x, _evils[2].y)] = EMPTY;
  moveEvilsCW(_evils[1]);
  moveEvilsCW(_evils[2]);
  moveEvilsRand();
  for (auto& it : _evils)
    { _tiles[CONVERT(it.x, it.y)] = EVIL_DUDE;}
  switch (_tiles[CONVERT(_pos.x, _pos.y)])
  {
    case BLOCK:     { _tiles[CONVERT(_pos.x, _pos.y)] = OBSTACLE; break;}
    case OBSTACLE:  { if (_last != 0) {refresh(); } break; }
    case EVIL_DUDE: { refresh(); break; }
  }
  _last = 0;
}