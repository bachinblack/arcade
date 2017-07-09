//
// AGame.cpp for AGame in /home/bachinblack/work/cpp/cpp_arcade/games/sources/AGame
//
// Made by Philippe Bouttereux
// Login   <bachinblack@epitech.eu>
//
// Started on  Wed Mar 15 00:24:37 2017 Philippe Bouttereux
// Last update Sat Apr  8 17:02:03 2017 Philippe Bouttereux
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include "AGame.hpp"
#include "Protocol.hpp"

AGame::AGame(const uint16_t& width, const uint16_t& height, IGraphix *&glib)
{
  _t0 = Clock::now();
  _name = "none";
  _lives = 0;
  _glib = glib;
  _gameFPS = 18;
  _last = 0;
  _score = 0;
  _hscore = 0;
  _size.x = width;
  _size.y = height;
  if (width < 15 || (_size.y) < 15)
    _size.x = _size.y = 50;
  else if (width > 200 || (_size.y) > 200)
    _size.x = _size.y = 50;
  _tiles.assign(width*(_size.y), EMPTY);
  if (glib == NULL)
  {
    input = std::bind(&AGame::readInput, this);
    output = std::bind(&AGame::printMap, this);
    _functions =
    {
      { In::WHERE_AM_I, std::bind(&AGame::whereAmI, this)},
      { In::GET_MAP, std::bind(&AGame::sendOutput, this)},
      { In::GO_UP, std::bind(&AGame::setUp, this)},
      { In::GO_DOWN, std::bind(&AGame::setDown, this)},
      { In::GO_LEFT, std::bind(&AGame::setLeft, this)},
      { In::GO_RIGHT, std::bind(&AGame::setRight, this)},
      { In::GO_FORWARD, std::bind(&AGame::setForward, this)},
      { In::SHOOT, std::bind(&AGame::Shoot, this)},
      { In::ILLEGAL, std::bind(&AGame::end, this)},
      { In::PLAY, std::bind(&AGame::playRound, this)}
    };
  }
  else
  {
    _glib->setFPS(18);
    _infospos = glib->getPA()->getSize();
    _infospos.y -= 75;
    _tileSize.x = _infospos.x / width;
    _tileSize.y = _infospos.y / _size.y;
    input = std::bind(&AGame::readKeyboard, this);
    output = std::bind(&AGame::blitMap, this);
    _functions =
    {
      { Key::_ESCAPE, std::bind(&AGame::end, this) },
      { Key::_q, std::bind(&AGame::goLeft, this) },
      { Key::_d, std::bind(&AGame::goRight, this) },
      { Key::_s, std::bind(&AGame::goDown, this) },
      { Key::_z, std::bind(&AGame::goUp, this) },
      { Key::_SPACE, std::bind(&AGame::Shoot, this) },
      { Key::_p, std::bind(&AGame::Pause, this) },
    };
  }
  _colors.push_back((Grix::Color){30, 30, 30, 255});
  _colors.push_back((Grix::Color){200, 5, 5, 255});
  _colors.push_back((Grix::Color){90, 90, 90, 255});
  _colors.push_back((Grix::Color){5, 5, 220, 255});
  _colors.push_back((Grix::Color){5, 5, 220, 255});
  _colors.push_back((Grix::Color){5, 220, 5, 255});
  _colors.push_back((Grix::Color){200, 20, 200, 255});
  _colors.push_back((Grix::Color){120, 120, 120, 255});
  _colors.push_back((Grix::Color){1, 100, 220, 255});
  _colors.push_back((Grix::Color){0, 0, 0, 0});
  if (glib != NULL)
    std::srand(std::time(NULL));
  else
    std::srand(1);
}

void    AGame::printInfos(void)
{
  Grix::Position      pos = _infospos;
  Grix::Color         col = (Grix::Color){20, 205, 205, 255};
  std::ostringstream  ss;
  Clock::time_point   t1 = Clock::now();

  if (_score > _hscore)
    _hscore = _score;
  pos.y += 10;
  pos.x = 20;
  _glib->putText(_name, pos, col, 3, false);
  pos.x += 216;
  ss << std::setfill('0') << std::setw(2) << std::chrono::duration_cast<std::chrono::seconds>(t1 - _t0).count() / 60 << ":" \
  << std::setfill('0') << std::setw(2) << std::chrono::duration_cast<std::chrono::seconds>(t1 - _t0).count() % 60;
  _glib->putText(ss.str(), pos, col, 3, false);
  ss.str(std::string());
  ss << std::setfill('0') << std::setw(5) << _score << "   |   " << std::setfill('0') << std::setw(5) << _hscore;
  pos.x -= 216;
  pos.y += 30;
  _glib->putText(ss.str(), pos, col, 3, false);
  pos.x = _size.x * _tileSize.x - 60;
  pos.y = _infospos.y + 10;
  for (unsigned i=0; i<_lives; ++i)
  {
    for (unsigned x=0; x<50; ++x)
    {
      for (unsigned y=0; y<50; ++y)
        _glib->getPA()->setPixel((Grix::Position){pos.x + x, pos.y + y}, col);
    }
    pos.x -= 75;
  }
}

AGame::~AGame(void)
{
  std::ostringstream  ss;
  std::ofstream  fs;

  ss << "./res/" << _name << ".score";
  fs.open(ss.str());
  if (!fs.is_open())
    std::cout << "failed to open scores file\n";
  else
  {
    fs << _hscore;
    fs.close();
  }
}

void  AGame::getHScore()
{
  std::ifstream  fs;

  fs.open("./res/zelda.score");
  if (!fs.is_open())
    std::cout << "failed to open scores file\n";
  else
  {
    fs >> _hscore;
    fs.close();
  }
}

/* functions to point on */

/* -- without Grix -- */

void  AGame::readInput()
{
  char c;
  int  action;

  _last = Key::_d;
  while (!std::cin.read(&c, 1).eof())
  {
    std::cerr << "Action "<< (int)c << '\n';
    action = c;
    if (action < 10)
      _functions[action]();
    std::cin.read(&c, 1);
  }
}

void  AGame::whereAmI(void)
{
  arcade::WhereAmI  test;

  test.type = arcade::CommandType::WHERE_AM_I;
  test.lenght = 1;
  std::cout.write(reinterpret_cast<char *>(&test), sizeof(arcade::WhereAmI));
  std::cout.write(reinterpret_cast<char *>(&_pos.x), 2);
  std::cout.write(reinterpret_cast<char *>(&_pos.y), 2);
}

void  AGame::printMap(void)
{
  arcade::GetMap test;

  test.type = arcade::CommandType::GET_MAP;
  test.width = _size.x;
  test.height = _size.y;
  std::cerr << "width "<< test.width << "length "<< test.height << '\n';
  std::cout.write(reinterpret_cast<char *>(&test), sizeof(arcade::GetMap));
  for (auto& it : _tiles)
  {
    std::cout.write(reinterpret_cast<char *>(&it), 2);
  }
}

void AGame::setUp(void)      {_last = Key::_z;}
void AGame::setDown(void)      {_last = Key::_s; }
void AGame::setLeft(void)      {_last = Key::_q; }
void AGame::setRight(void)      {_last = Key::_d; }
void AGame::setForward(void)      {}
void AGame::playRound(void)
{
  if (_last == Key::_z)
    goUp();
  if (_last == Key::_s)
    goDown();
  if (_last == Key::_q)
    goLeft();
  if (_last == Key::_d)
    goRight();
  compute();
}

/* -- with Grix -- */

void  AGame::readKeyboard()
{
  const uint8_t   *kb = _glib->getKbSate();

  for (auto& it : _functions)
  {
    if (kb[it.first] == true)
    {
      if (it.first != Key::_SPACE && it.first != Key::_p && it.first != Key::_RETURN && it.first != Key::_ESCAPE)
        _last = it.first;
      it.second();
      if (_name != "zelda")
        return ;
    }
  }
  if (_functions.size() > 3)
    goForward();
}

void  AGame::blitGuy(void) const
{
  drawTile(_pos, _colors[PLAYER]);
}

void  AGame::blitMap(void) const
{
  unsigned    x = 0;
  unsigned    y = 0;

  for (auto& it : _tiles)
  {
    drawTile((Grix::Position){x, y}, _colors[it]);
    ++x;
    if (x >= _size.x)
    {
      x = 0;
      ++y;
    }
  }
  blitGuy();
}

/* -- three mMY_SHOOTain functions of a game -- */

void    AGame::compute(void) {}

void  AGame::getInput()
{
  this->input();
}

void  AGame::sendOutput()
{
  this->output();
}

/* -- two misc functions -- */

void  AGame::updateMap(const std::string& name, const std::string& code)
{
  uint16_t  til;

  if (_fs.is_open())
  {
    if (_fs.eof())
    {
      std::string s;

      _fs.close();
      _fs.open(name);
      if (!_fs.is_open())
        return ;
      _fs >> s;
      if (s != code)
        return ;
    }
    _tiles.clear();
    _fs >> _size.x;
    _fs >> _size.y;
    for (unsigned i=0; i<_size.x*_size.y; ++i)
    {
      _fs >> til;
      _tiles.push_back(til != 4 ? til : (rand() % 3) + 4);
    }
    _tileSize.x = _infospos.x / _size.x;
    _tileSize.y = _infospos.y / _size.y;
    _pos.x = _size.x >> 1;
    _pos.y = _size.y >> 1;
  }
}

void AGame::setGrixLib(IGraphix *lib) { _glib = lib;}

/* Functions defined by "action" pointer */

void AGame::goUp(void)      { if (_pos.y > 0) { --_pos.y;} }

void AGame::goDown(void)    { if (_pos.y < _size.y-1) { ++_pos.y;} }

void AGame::goLeft(void)    { if (_pos.x > 0) { --_pos.x;} }

void AGame::goRight(void)   { if (_pos.x < _size.x-1) { ++_pos.x;} }

void AGame::goForward(void) { if (_last) { _functions[_last]();} }

void AGame::Shoot(void)     { }

void AGame::end(void)       {}

void AGame::Pause(void)
{
  _pstr = "pause";
  output = std::bind(&AGame::dispPause, this);
  _functions = {{ Key::_RETURN, std::bind(&AGame::Play, this) }};
}

void    AGame::Victory(void)
{
  _pstr = "Victory";
  _last = 0;
  output = std::bind(&AGame::dispPause, this);
  _functions = {{ Key::_RETURN, std::bind(&AGame::Play, this) }};
}

void    AGame::Defeat(void)
{
  _pstr = "Game Over";
  _last = 0;
  output = std::bind(&AGame::dispPause, this);
  _functions = {{ Key::_RETURN, std::bind(&AGame::Play, this) }};
}

void    AGame::LvlUp(const unsigned& i)
{
  std::ostringstream ss;

  ss << "Level complete: " << i;
  _pstr = ss.str();
  _last = 0;
  output = std::bind(&AGame::dispPause, this);
  _functions = {{ Key::_RETURN, std::bind(&AGame::Play, this) }};
}

void AGame::Play(void)
{
  output = std::bind(&AGame::blitMap, this);
  _functions =
  {
    { Key::_ESCAPE, std::bind(&AGame::end, this) },
    { Key::_q, std::bind(&AGame::goLeft, this) },
    { Key::_d, std::bind(&AGame::goRight, this) },
    { Key::_s, std::bind(&AGame::goDown, this) },
    { Key::_z, std::bind(&AGame::goUp, this) },
    { Key::_SPACE, std::bind(&AGame::Shoot, this) },
    { Key::_p, std::bind(&AGame::Pause, this) },
  };
}

void  AGame::dispPause(void) const
{
  _glib->putText(_pstr, (Grix::Position) { (_size.x * _tileSize.x) >> 1, (_size.y * _tileSize.y) >> 1}, (Grix::Color) { 150, 150, 150, 255}, 6, true);
  _glib->putText("press enter to continue", (Grix::Position) { (_size.x * _tileSize.x) >> 1, ((_size.y * _tileSize.y) >> 1) + 50}, (Grix::Color) { 120, 120, 120, 255}, 2, true);
}

void AGame::drawTile(const Grix::Position& cpos, const Grix::Color& col) const
{
  Grix::Position  pos = { cpos.x * _tileSize.x, cpos.y * _tileSize.y };

  for (unsigned x=0; x<_tileSize.x; ++x)
  {
    for (unsigned y=0; y<_tileSize.y; ++y)
    {
      _glib->getPA()->setPixel((Grix::Position){pos.x + x, pos.y + y}, col);
    }
  }
}

uint16_t        AGame::getTile(const int& x, const int& y) const
{
  if (x < 0 || y < 0 || static_cast<uint32_t>(x) >= _size.x || static_cast<uint32_t>(y) >= _size.y)
    return (NONE);
  return (_tiles[CONVERT(x, y)]);
}
