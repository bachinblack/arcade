//
// GameSolarFox.cpp for GameSolarFox in /home/bachinblack/work/cpp/lol/cpp_arcade/games/sources/GameSolarFox
//
// Made by Philippe Bouttereux
// Login   <bachinblack@epitech.eu>
//
// Started on  Mon Mar 27 14:23:37 2017 Philippe Bouttereux
// Last update Sun Apr  9 18:55:28 2017 Philippe Bouttereux
//

#include <iostream>
#include "GameSolarFox.hpp"

extern "C"
IGame    *initGame(IGraphix *glib)
{
  return new SolarFox(40, 40, glib);
}

extern "C"
void Play(void)
{
  SolarFox sol(5, 5, NULL);
  sol.readInput();
}

SolarFox::SolarFox(const uint16_t& width, const uint16_t& height, IGraphix *glib)
: AGame(width, height, glib)
{
  std::string s;

  _lives = 3;
  _name = "solarfox";
  getHScore();
  _fs.open("./res/solarfox.map");
  if (_fs.is_open() && glib != NULL)
  {
    _fs >> s;
    if (s == "!solarfox>")
      updateMap("./res/solarfox.map", "!solarfox>");
  }
  else
  {
    _tiles = {
      0, 0, 3, 0, 0,
      0, 0, 0, 0, 0,
      6, 6, 0, 6, 6,
      0, 0, 0, 0, 0,
      0, 0, 3, 0, 0
    };
    _size.x = 5;
    _size.y = 5;
    if (glib == NULL)
      {
        _size.x = 0;
        _size.y = 0;
      }
  }
  _pos.x = _size.x >> 1;
  _pos.y = _size.y >> 1;
}

void  SolarFox::refresh(void)
{
  std::string s;

  _score = 0;
  _lives = 3;
  _fs.close();
  _fs.open("./res/solarfox.map");
  _fs >> s;
  if (s == "!solarfox>")
    updateMap("./res/solarfox.map", "!solarfox>");
}

SolarFox::~SolarFox()
{
  _fs.close();
}

void  SolarFox::goForward(void) { }

void  SolarFox::decrlives(void)
{
  if (--_lives == 0)
  {
    Defeat();
    refresh();
  }
}

void  SolarFox::back()
{
  switch(_last)
  {
    case Key::_z: { ++_pos.y; break;}
    case Key::_s: { --_pos.y; break;}
    case Key::_d: { --_pos.x; break;}
    case Key::_q: { ++_pos.x;}
  }
}

void  SolarFox::compute(void)
{
  bool  check = false;

  _glib->setFPS(10);

  switch(_tiles[CONVERT(_pos.x, _pos.y)])
  {
    case POWERUP:  { _tiles[CONVERT(_pos.x, _pos.y)] = EMPTY; _score += 100; break;}
    case EVIL_DUDE: { back(); decrlives(); break;}
    case EVIL_SHOOT: { _tiles[CONVERT(_pos.x, _pos.y)] = EMPTY; decrlives();}
  }
  for (auto& it : _tiles)
  {
    if (it == POWERUP)
      check = true;
  }
  if (check == false)
  {
    Victory();
    updateMap("./res/solarfox.map", "!solarfox>");
  }
}
