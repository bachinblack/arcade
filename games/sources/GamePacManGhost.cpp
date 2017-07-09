//
// GamePacManGhost.cpp for Pacman in /home/kotra/rendu/cpp_arcade/games/sources/
//
// Made by Kotra
// Login   <mathis.rousselot@epitech.eu@epitech.eu>
//
// Started on  Sat Mar 25 11:56:03 2017 Kotra
// Last update Sun Apr  9 20:47:38 2017 Kotra
//

#include <unistd.h>

#include <iostream>
#include <fstream>
#include <algorithm>
#include "GamePacMan.hpp"

Ghost::Ghost(const int &cmp, const int &pClock, const Grix::Position &pos)
{
  _home = pos;
  _type = cmp;
  _state = WAITING;
  _pClock = pClock;
  _dir = 0;
}

int   Ghost::checkAround(const std::vector<t_mapTile> &map, const Grix::Position &pos,
                        const Grix::Position &mazeMax, t_mapTile *tile,
                        const Grix::Position &prev, int dir)
{
  int tileMin = -1;
  std::unordered_map<int, int> no_dir =
  { {1, 2}, {2, 1}, {3, 4}, {4, 3} };

  tile[0] = map[pos.x + pos.y * mazeMax.x];
  if (tile[0].value != 0 && tile[0].value != -1)
    tileMin = tile[0].value;
  if (pos.x - 1 <= 0 || dir == 2)
  {
    tile[1].value = -1;
    tile[1].dir = -1;
  }
  else
  {
    tile[1].value = map[pos.x - 1 + pos.y * mazeMax.x].value;
    tile[1].dir = map[pos.x - 1 + pos.y * mazeMax.x].dir;
    if (tile[1].value > 0 && (tile[1].value < tileMin || tileMin == -1)
        && (prev.x != pos.x -1 || prev.y != pos.y)
        && no_dir[dir] != tile[1].dir)
      tileMin = tile[1].value;
  }
  if (pos.x + 1 >= mazeMax.x || dir ==  1)
  {
    tile[2].value = -1;
    tile[2].dir = -1;
  }
  else
  {
    tile[2].dir = map[pos.x + 1 + pos.y * mazeMax.x].dir;
    tile[2].value = map[pos.x + 1 + pos.y * mazeMax.x].value;
    if (tile[2].value > 0 && (tile[2].value < tileMin || tileMin == -1)
        && (prev.x != pos.x + 1 || prev.y != pos.y)
        && no_dir[dir] != tile[2].dir)
     tileMin = tile[2].value;
  }
  if (pos.y - 1 <= 0 || dir == 4)
  {
    tile[3].value = -1;
    tile[3].dir = -1;
  }
  else
  {
    tile[3].dir = map[pos.x + (pos.y - 1) * mazeMax.x].dir;
    tile[3].value = map[pos.x + (pos.y - 1) * mazeMax.x].value;
    if (tile[3].value > 0 && (tile[3].value < tileMin || tileMin == -1)
        && (prev.x != pos.x || prev.y != pos.y - 1)
        && no_dir[dir] != tile[3].dir)
     tileMin = tile[3].value;
  }
  if (pos.y + 1 >= mazeMax.y || dir == 3)
  {
    tile[4].value = -1;
    tile[4].dir = -1;
  }
  else
  {
    tile[4].dir = map[pos.x + (pos.y + 1) * mazeMax.x].dir;
    tile[4].value = map[pos.x + (pos.y + 1) * mazeMax.x].value;
    if (tile[4].value > 0 && (tile[4].value < tileMin || tileMin == -1)
        && (prev.x != pos.x || prev.y != pos.y + 1)
        && no_dir[dir] != tile[4].dir)
     tileMin = tile[4].value;
  }
  return (tileMin);
}


void  Ghost::goDeeper(std::vector<t_mapTile> &map, Grix::Position pos,
                        const Grix::Position &mazeMax, const Grix::Position &prev,
                        int dir)
{
  t_mapTile tile[5];
  int mini = checkAround(map, pos, mazeMax, tile, prev, dir);
  std::unordered_map<char, Grix::Position> correspond =
  {
    {1, (Grix::Position){pos.x - 1, pos.y}},
    {2, (Grix::Position){pos.x + 1, pos.y}},
    {3, (Grix::Position){pos.x, pos.y - 1}},
    {4, (Grix::Position){pos.x, pos.y + 1}},
  };
  if (mini < tile[0].value && mini != -1 && tile[0].dir != dir)
  {
    map[pos.x + pos.y * mazeMax.x].value = mini + 1;
    mini++;
  }
  for (size_t i = 1; i < 5; i++)
  {
    if (tile[i].value >= 0 && (tile[i].value > mini + 1 || tile[i].value == 0) &&
    (prev.x != correspond[i].x || prev.y != correspond[i].y))
    {
      map[correspond[i].x + correspond[i].y * mazeMax.x].value = mini + 1;
      map[correspond[i].x + correspond[i].y * mazeMax.x].dir = i;
      goDeeper(map, correspond[i], mazeMax, pos, i);
      goDeeper(map, pos, mazeMax, prev, dir);
    }
  }
}

void Ghost::choose(const std::vector<t_mapTile> &map, const Grix::Position &mazeMax)
{
  t_mapTile tile[5];
  int mini = map[_focus.x + _focus.y * mazeMax.x].value;
  Grix::Position pos = _focus;
  int escape = 0;
  int i;

  if (map[_focus.x + _focus.y * mazeMax.x].value == 1)
    mini = 3;
  while (mini < 1)
  {
    if (escape == 255)
    {
      _dir = 0;
      return;
    }
    i = std::rand() % 4;
    (i == 1 && pos.x > 0) ? (pos.x--) : 0;
    (i == 2 && pos.x < mazeMax.x) ? (pos.x++) : 0;
    (i == 3 && pos.y > 0) ? (pos.y--) : 0;
    (i == 4 && pos.y < mazeMax.y) ? (pos.y++) : 0;
    mini = map[pos.x + pos.y * mazeMax.x].value;
    escape++;
  }
  while (mini > 2)
  {
    mini--;
    checkAround(map, pos, mazeMax, tile, _focus, 0);
    for (size_t i = 1; i < 5; i++)
    {
      if (map[_focus.x + _focus.y * mazeMax.x].value == 1 && tile[i].value == mini)
      {
        (i == 1) ? (pos.x--, _dir = 1) : 0;
        (i == 2) ? (pos.x++, _dir = 2) : 0;
        (i == 3) ? (pos.y--, _dir = 3) : 0;
        (i == 4) ? (pos.y++, _dir = 4) : 0;
        if (mini == 2)
          _dir = tile[i].dir;
        break;
      }
      if (tile[i].value == mini)
      {
        (i == 1) ? (pos.x--, _dir = 2) : 0;
        (i == 2) ? (pos.x++, _dir = 1) : 0;
        (i == 3) ? (pos.y--, _dir = 4) : 0;
        (i == 4) ? (pos.y++, _dir = 3) : 0;
        if (mini == 2)
          _dir = tile[i].dir;
        break;
      }
    }
  }
  if (mini == 2)
    _pos = pos;
}

void Ghost::pathFinding(std::vector<t_mapTile> map,
                        const Grix::Position &mazeMax)
{
  if (_pos.x >= mazeMax.x || _pos.y >= mazeMax.y)
    return;
  if (_state != WAITING)
    for (auto& it : map)
    {
      if (it.value == -2)
        it.value = 0;
    }
  if (map[_pos.x + _pos.y * mazeMax.x].value == -1)
    return;
  map[_pos.x + _pos.y * mazeMax.x].value = 1;
  map[_pos.x + _pos.y * mazeMax.x].dir = _dir;
  goDeeper(map, _pos, mazeMax, _pos, _dir);
  choose(map, mazeMax);
}


int  Ghost::pinkyChoice(const std::vector<t_mapTile> &map,
                        const Grix::Position &mazeMax,
                        const Grix::Position &pPos,
                        const unsigned int &last)
{
  int absol;
  int rev;

  (last == Key::_z || last == Key::_q) ? (rev = 1) : (rev = -1);
  _focus = pPos;
  if (last == Key::_q || last == Key::_d)
  {
    for (int x = 3 * -rev; x < 3 * rev; x += rev)
    {
      (x < 0) ? (absol = -x) : (absol = x);
      for (int y = -3 + absol; y < 3 - absol; y++)
      {
        if (y == 0)
          continue;
        if ((int)pPos.x + x >= 0 && (int)pPos.x + x < (int)mazeMax.x &&
        (int)pPos.y + y >= 0 && (int)pPos.y + y < (int)mazeMax.y &&
        map[(pPos.x + x) + (pPos.y + y) * mazeMax.x].value == 0)
        {
          _focus = {pPos.x + x, pPos.y + y};
          return (0);
        }
      }
      if ((int)pPos.x + x >= 0 && (int)pPos.x + x < (int)mazeMax.x &&
      (int)pPos.y >= 0 && (int)pPos.y < (int)mazeMax.y &&
      map[(pPos.x + x) + pPos.y * mazeMax.x].value == 0)
      {
        _focus = {pPos.x + x, pPos.y};
        return (0);
      }
    }
  }
  if (last == Key::_z || last == Key::_s)
  {
    for (int y = 3 * -rev; y < 3 * rev; y += rev)
    {
      (y < 0) ? (absol = -y) : (absol = y);
      for (int x = -3 + absol; x < 3 - absol; x++)
      {
        if (x == 0)
          continue;
        if ((int)pPos.x + x >= 0 && (int)pPos.x + x < (int)mazeMax.x &&
        (int)pPos.y + y >= 0 && (int)pPos.y + y < (int)mazeMax.y &&
        map[(pPos.x + x) + (pPos.y + y) * mazeMax.x].value == 0)
        {
          _focus = {pPos.x + x, pPos.y + y};
          return (0);
        }
      }
      if ((int)pPos.x >= 0 && (int)pPos.x < (int)mazeMax.x &&
      (int)pPos.y + y >= 0 && (int)pPos.y + y < (int)mazeMax.y &&
      map[pPos.x + (pPos.y + y) * mazeMax.x].value == 0)
      {
        _focus = {pPos.x, pPos.y + y};
        return (0);
      }
    }
  }
  return (0);
}

int  Ghost::clydeChoice(const Grix::Position &pPos)
{
  int x;
  int y;

  x = (int)_pos.x - (int)pPos.x;
  y = (int)_pos.y - (int)pPos.y;
  (x < 0) ? (x = -x) : 0;
  (y < 0) ? (y = -y) : 0;
  if (x + y >= 8)
    _focus = pPos;
  else
    _focus = _home;
  return (0);
}

void Ghost::ChoosePoint(const std::vector<t_mapTile> &map,
                        const Grix::Position &mazeMax,
                        const Grix::Position &pPos,
                        const unsigned int &last,
                        const Grix::Position &spawn)
{
  _pClock--;
  if (_state == WAITING)
    (_pClock == 0) ? (_state = FLEE, _pClock = 60) : 0;
  if (_state == FLEE)
  {
    _focus = _home;
    (_pClock == 0) ? (_state = CHASING, _pClock = 180) : 0;
  }
  if (_state == DEAD)
  {
    _focus = spawn;
    (_pos == spawn) ? (_state = CHASING, _pClock = 1800) : 0;
  }
  if (_state == CHASING)
  {
    (_type == BLINKY) ? (_focus = pPos) : 0;
    (_type == PINKY) ? (pinkyChoice(map, mazeMax, pPos, last)) : 0;
    (_type == CLYDE) ? (clydeChoice(pPos)) : 0;
    (_type == INKY) ? (clydeChoice(pPos)) : 0;
    (_pClock == 0) ? (_state = FLEE, _pClock = 180) : 0;
  }
}

void Ghost::setSpawn(const Grix::Position &pos) {_pos = pos;}
void Ghost::setTime(int pClock) {_pClock = pClock;}
void Ghost::setState(char state) {_state = state;}
char const &Ghost::getState(void){return(_state);}
char const &Ghost::getType(void){return(_type);}
Grix::Position const &Ghost::getPos(void){return(_pos);}

Ghost::~Ghost()
{
}
