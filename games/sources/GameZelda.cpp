//
// GameZelda.cpp for GameZelda in /home/bachinblack/work/cpp/lol/cpp_arcade/games/sources/GameZelda
//
// Made by Philippe Bouttereux
// Login   <bachinblack@epitech.eu>
//
// Started on  Tue Mar 28 01:49:54 2017 Philippe Bouttereux
// Last update Sat Apr  8 17:10:55 2017 Philippe Bouttereux
//

#include <iostream>
#include "GameZelda.hpp"

extern "C"
IGame    *initGame(IGraphix *glib)
{
  return new Zelda(40, 40, glib);
}

extern "C"
void Play(void)
{
  Zelda zelda(50, 50, NULL);
  zelda.readInput();
}

Zelda::Zelda(const uint16_t& width, const uint16_t& height, IGraphix *glib)
: AGame(width, height, glib)
{
  std::string s;
  
  _invu = 0;
  _name = "zelda";
  getHScore();;
  _precPos.x = 5;
  _precPos.y = 5;
  _lives = 4;
  _fs.open("./res/zelda.map");
  if (_fs.is_open())
  {
    _fs >> s;
    if (s == "!zelda>")
      updateMap("./res/zelda.map", "!zelda>");
  }
  else
    std::cout << "couldn't open [./res/zelda.map]." << std::endl;
  if (glib != NULL)
  {
    _sprite = glib->newPA("./res/ztextures.bmp");
    if (_sprite->isValid())
      _sprite->setSize((Grix::Size) { _tileSize.x * NBSPRITES, _tileSize.y * 4});
    _char[0] = glib->newPA("./res/zchar.bmp");
    if (_char[0]->isValid())
      _char[0]->setSize((Grix::Size) { _tileSize.x * (LINKFRAMES+1), _tileSize.y * 16});
    _char[1] = glib->newPA("./res/zstatue.bmp");
    if (_char[1]->isValid())
      _char[1]->setSize((Grix::Size) { _tileSize.x * (EVILFRAMES+1), _tileSize.y * 8});
  }
  _chars.push_back(Character(_size, _tiles, 0));
  _chars.push_back(Character(_size, _tiles));
  _chars.push_back(Character(_size, _tiles));
  _chars.push_back(Character(_size, _tiles));
  _chars[0]._pos.x = 1;
  _chars[0]._pos.y = 1;
}

void  Zelda::refresh()
{
  std::string s;

  _invu = 10;
  _chars.clear();
  _fs.close();
  _lives = 4;
  _precPos.x = 5;
  _precPos.y = 5;
  _fs.open("./res/zelda.map");
  if (_fs.is_open())
  {
    _fs >> s;
    if (s == "!zelda>")
      updateMap("./res/zelda.map", "!zelda>");
  }
  if (_glib != NULL)
  {
    _sprite = _glib->newPA("./res/ztextures.bmp");
    if (_sprite->isValid())
      _sprite->setSize((Grix::Size) { _tileSize.x * NBSPRITES, _tileSize.y * 4});
    _char[0] = _glib->newPA("./res/zchar.bmp");
    if (_char[0]->isValid())
      _char[0]->setSize((Grix::Size) { _tileSize.x * (LINKFRAMES+1), _tileSize.y * 16});
    _char[1] = _glib->newPA("./res/zstatue.bmp");
    if (_char[1]->isValid())
      _char[1]->setSize((Grix::Size) { _tileSize.x * (EVILFRAMES+1), _tileSize.y * 8});
  }
  _chars.push_back(Character(_size, _tiles, 0));
  _chars.push_back(Character(_size, _tiles));
  _chars.push_back(Character(_size, _tiles));
  _chars.push_back(Character(_size, _tiles));
  _chars[0]._pos.x = 1;
  _chars[0]._pos.y = 1;
}

Character::Character(const Grix::Size& size, const std::vector<uint16_t>& tiles, const uint16_t& pixA)
{
  _pos.x = rand() % size.x;
  _pos.y = rand() % size.y;
  while (tiles[size.x * _pos.y + _pos.x] == FENCE)
  {
    _pos.x = rand() % size.x;
    _pos.y = rand() % size.y;    
  }
  _look = DOWN;
  _frame = 0;
  _pixA = pixA;
}

Zelda::~Zelda() {
  delete _sprite;
  delete _char[0];
  delete _char[1];
  _fs.close();
}

void  Zelda::goForward(void) { }

void    Zelda::blitMap(void) const
{
  unsigned    x = 0;
  unsigned    y = 0;

  for (auto& it : _tiles)
  {
    drawTile((Grix::Position){x, y}, it);
    ++x;
    if (x >= _size.x)
    {
      x = 0;
      ++y;
    }
  }
  for (auto& it : _chars)
  {
    blitGuy(it, _invu % 2 == 1 && it._pixA == 0 ? true : false);
  }
}

void    Zelda::drawTile(const Grix::Position& cpos, const uint16_t& it, const Grix::Position& offset, const uint16_t& h) const
{
  Grix::Position  pos = { cpos.x * _tileSize.x + offset.x, cpos.y * _tileSize.y + offset.y};

  for (unsigned x=it*_tileSize.x; x<(it+1)*_tileSize.x; ++x)
  {
    for (unsigned y=h*_tileSize.y; y<(h+1)*_tileSize.y; ++y)
    {
      _glib->getPA()->setPixel((Grix::Position){pos.x, pos.y}, _sprite->getPixel((Grix::Position){ x, y}));
      ++pos.y;
    }
    ++pos.x;
    pos.y -= _tileSize.y;
  }
}

void  Zelda::blitGuy(const Character& c, const bool& offset) const
{
  Grix::Position  pos = { c._pos.x * _tileSize.x + c._precPos.x, (c._pos.y-1) * _tileSize.y + c._precPos.y};
  Grix::Color     keep;
  
  for (unsigned x=c._frame*_tileSize.x; x<(c._frame+1)*_tileSize.x; ++x)
  {
    for (unsigned y=(c._look-1)*_tileSize.y; y<(c._look)*_tileSize.y; ++y)
    {
      keep = _char[c._pixA]->getPixel((Grix::Position){ x, y});
      if (offset == true)
        keep.argb[Grix::Color_bytes::RED] = 255;
      _glib->getPA()->setPixel((Grix::Position){pos.x, pos.y}, keep);
      ++pos.y;
    }
    ++pos.x;
    pos.y -= _tileSize.y;
  }
  pos = { c._pos.x * _tileSize.x + c._precPos.x, c._pos.y * _tileSize.y + c._precPos.y};
  for (unsigned x=c._frame*_tileSize.x; x<(c._frame+1)*_tileSize.x; ++x)
  {
    for (unsigned y=c._look*_tileSize.y; y<(c._look+1)*_tileSize.y; ++y)
    {
      keep = _char[c._pixA]->getPixel((Grix::Position){ x, y});
      if (offset == true)
        keep.argb[Grix::Color_bytes::RED] = 255;
      _glib->getPA()->setPixel((Grix::Position){pos.x, pos.y}, keep);
      ++pos.y;
    }
    ++pos.x;
    pos.y -= _tileSize.y;
  }
}

void Zelda::goUp(void)      { _chars[0]._look = UP; if (_chars[0]._pos.y > 0 && _tiles[CONVERT((_chars[0]._pos.x + (_chars[0]._precPos.x >= _tileSize.x >> 1 ? 1 : 0)), (_chars[0]._pos.y + (_chars[0]._precPos.y-(_tileSize.y>>2) >= _tileSize.y >> 1 ? 1 : 0)))] != FENCE) { if ((static_cast<int>(_chars[0]._precPos.y -= _tileSize.y >> 2)) <= 0) { _chars[0]._precPos.y = _tileSize.y; --_chars[0]._pos.y;} ++_chars[0]._frame;} }

void Zelda::goDown(void)    { _chars[0]._look = DOWN; if (_chars[0]._pos.y < _size.y-1 && _tiles[CONVERT((_chars[0]._pos.x + (_chars[0]._precPos.x >= _tileSize.x >> 1 ? 1 : 0)), (_chars[0]._pos.y + (_chars[0]._precPos.y+(_tileSize.y>>2) >= _tileSize.y >> 1 ? 1 : 0)))] != FENCE) { if ((_chars[0]._precPos.y +=  _tileSize.y >> 2) >= _tileSize.y) { _chars[0]._precPos.y = 0; ++_chars[0]._pos.y;} ++_chars[0]._frame;} }

void Zelda::goLeft(void)    { _chars[0]._look = LEFT; if (_chars[0]._pos.x > 0 && _tiles[CONVERT((_chars[0]._pos.x + (_chars[0]._precPos.x-(_tileSize.x>>2) >= _tileSize.x >> 1 ? 1 : 0)), (_chars[0]._pos.y + (_chars[0]._precPos.y >= _tileSize.y >> 1 ? 1 : 0)))] != FENCE) { if ((static_cast<int>(_chars[0]._precPos.x -=  _tileSize.x >> 2)) <= 0) { _chars[0]._precPos.x = _tileSize.x; --_chars[0]._pos.x;} ++_chars[0]._frame;} }

void Zelda::goRight(void)   { _chars[0]._look = RIGHT; if (_chars[0]._pos.x < _size.x-1 && _tiles[CONVERT((_chars[0]._pos.x + (_chars[0]._precPos.x+(_tileSize.x>>2) >= _tileSize.x >> 1 ? 1 : 0)), (_chars[0]._pos.y + (_chars[0]._precPos.y >= _tileSize.y >> 1 ? 1 : 0)))] != FENCE) { if ((_chars[0]._precPos.x +=  _tileSize.x >> 2) >= _tileSize.x) { _chars[0]._precPos.x = 0; ++_chars[0]._pos.x;} ++_chars[0]._frame;} }

void  Zelda::decrlives(void)
{
  _invu = 50;
  if (--_lives == 0)
  {
    Defeat();
    refresh();
  }
}

void  Zelda::lookAtMe(Character& c)
{
  if (ABS(static_cast<int>(_chars[0]._pos.x - c._pos.x)) < ABS(static_cast<int>(_chars[0]._pos.y - c._pos.y)))
  {
    if (_chars[0]._pos.y > c._pos.y)
    {
      c._look = DOWN;  
      if (c._pos.y < _size.y-1 && _tiles[CONVERT((c._pos.x + (c._precPos.x >= _tileSize.x >> 1 ? 1 : 0)), (c._pos.y + (c._precPos.y+(_tileSize.y>>2) >= _tileSize.y >> 1 ? 1 : 0)))] != FENCE) { if ((c._precPos.y +=  _tileSize.y >> 2) >= _tileSize.y) { c._precPos.y = 0; ++c._pos.y;} ++c._frame; }
    }
    else
    {
      c._look = UP;
      if (_tiles[CONVERT((c._pos.x + (c._precPos.x >= _tileSize.x >> 1 ? 1 : 0)), (c._pos.y + (c._precPos.y-(_tileSize.y>>2) >= _tileSize.y >> 1 ? 1 : 0)))] != FENCE) { if ((static_cast<int>(c._precPos.y -= _tileSize.y >> 2)) <= 0) { c._precPos.y = _tileSize.y; --c._pos.y;} ++c._frame;}
    }
  }
  else
  {
    if (_chars[0]._pos.x > c._pos.x)
    {  
      c._look = RIGHT;
      if (c._pos.x < _size.x-1 && _tiles[CONVERT((c._pos.x + (c._precPos.x+(_tileSize.x>>2) >= _tileSize.x >> 1 ? 1 : 0)), (c._pos.y + (c._precPos.y >= _tileSize.y >> 1 ? 1 : 0)))] != FENCE) { if ((c._precPos.x +=  _tileSize.x >> 2) >= _tileSize.x) { c._precPos.x = 0; ++c._pos.x;} ++c._frame;}
    }
    else
    {
      c._look = LEFT;
      if (c._pos.x > 0  && _tiles[CONVERT((c._pos.x + (c._precPos.x-(_tileSize.x>>2) >= _tileSize.x >> 1 ? 1 : 0)), (c._pos.y + (c._precPos.y >= _tileSize.y >> 1 ? 1 : 0)))] != FENCE) { if ((static_cast<int>(c._precPos.x -=  _tileSize.x >> 2)) <= 0) { c._precPos.x = _tileSize.x; --c._pos.x;} ++c._frame;}
    }
  }
}

void    Zelda::compute(void)
{
  bool  no = false;
  Clock::time_point   t1 = Clock::now();

  _glib->setFPS(20);
  for (auto& it : _chars)
  {
    if (no == false)
      no = true;
    else
    {
      if (std::chrono::duration_cast<std::chrono::milliseconds>(t1-_t0).count() % 3 == 0)
        lookAtMe(it);
      if (_invu == 0)
      {
       if (it._pos.x + (it._precPos.x-(_tileSize.x>>2) >= _tileSize.x >> 1 ? 0 : 0) == _chars[0]._pos.x + (_chars[0]._precPos.x-(_tileSize.x>>2) >= _tileSize.x >> 1 ? 0 : 0))
       {
        if (it._pos.y + (it._precPos.y-(_tileSize.x>>2) >= _tileSize.y >> 1 ? 0 : 0) == _chars[0]._pos.y + (_chars[0]._precPos.y-(_tileSize.y>>2) >= _tileSize.y >> 1 ? 0 : 0))
          decrlives();
      }
    }
    else
     --_invu;
 }
 if (it._frame >= MAXFRAME)
  it._frame = 0;
else if (it._frame > 0)
  ++it._frame;
}
if (_tiles[CONVERT(_chars[0]._pos.x, _chars[0]._pos.y)] == EXIT)
{
  updateMap("./res/zelda.map", "!zelda>");
  levelUp();
}
_score = std::chrono::duration_cast<std::chrono::seconds>(t1-_t0).count() * 100;
}

void      Zelda::levelUp(void)
{
  for(std::vector<Character>::iterator it = _chars.begin() + 1; it != _chars.end(); ++it)
  {
    it->_precPos.x = 0;
    it->_precPos.y = 0;
    it->_pos.x = rand() % _size.x;
    it->_pos.y = rand() % _size.y;
    while (_tiles[_size.x * it->_pos.y + it->_pos.x] == FENCE)
    {
      it->_pos.x = rand() % _size.x;
      it->_pos.y = rand() % _size.y;    
    }
  }
  _chars.push_back(Character(_size, _tiles));
  if (_sprite->isValid())
    _sprite->setSize((Grix::Size) { _tileSize.x * NBSPRITES, _tileSize.y * 4});
  _char[0] = _glib->newPA("./res/zchar.bmp");
  if (_char[0]->isValid())
    _char[0]->setSize((Grix::Size) { _tileSize.x * (LINKFRAMES+1), _tileSize.y * 16});
  _char[1] = _glib->newPA("./res/zstatue.bmp");
  if (_char[1]->isValid())
    _char[1]->setSize((Grix::Size) { _tileSize.x * (EVILFRAMES+1), _tileSize.y * 8});
  _chars[0]._pos.x = 1;
  _chars[0]._pos.y = 1;
  _chars[0]._precPos.x = 1;
  _chars[0]._precPos.y = 1;
}

void      Zelda::Shoot(void)
{
  if (_last) { _functions[_last]();}
  if (_last) { _functions[_last]();}
}
