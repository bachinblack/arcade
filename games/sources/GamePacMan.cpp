//
// GamePacMan.cpp for GamePacMan in /home/bachinblack/work/cpp/lol/cpp_arcade/games/sources/GamePacMan
//
// Made by Philippe Bouttereux
// Login   <bachinblack@epitech.eu>
//
// Started on  Sat Mar 18 17:36:03 2017 Philippe Bouttereux
// Last update Sun Apr  9 20:57:31 2017 Kotra
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include "GamePacMan.hpp"

extern "C"
IGame    *initGame(IGraphix *glib)
{
  return new Pacman(40, 30, glib);
}

extern "C"
void Play(void)
{
  Pacman Pacman(40, 30, NULL);
  Pacman.readInput();
}

void     Pacman::getMap()
{
  int posG = 0;
  Grix::Position  pos = {0, 0};
  std::fstream  fs;
  char c;
  int pClock = _fps * 7;

  _lives = 3;
  std::unordered_map<char, int> correspond =
  {
    {'S', 0}, {'0', 0}, {'G', 0},
    {'1', 1},
    {'E', 2},
    {'o', 6}, {'B', 6}, {'P', 6}, {'I', 6}, {'C', 6},
    {'O', 7}
  };

  std::unordered_map<char, t_mapTile> correspondG =
  {
    {'E', {-2, 0}},
    {'1', {-1, -1}},
    {'B', {0, 0}}, {'P', {0, 0}}, {'I', {0, 0}}, {'C', {0, 0}},
    {'S',{ 0, 0}}, {'0', {0, 0}}, {'o', {0, 0}}, {'O', {0, 0}}, {'G', {0, 0}}
  };

  _mazeMax = {0, 0};
  _pacSpawn = {0, 0};
  fs.open("./res/pc.map", std::iostream::in);
  if (!fs.is_open() || _glib == NULL)
  {
    std::cerr << "No file" << std::endl;
    _tiles = {
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,
      6, 6, 0, 6, 6,
      0, 0, 0, 0, 0,
      0, 0, 0, 0, 0
    };
    _size.x = 5;
    _size.y = 5;
    _mazeMax.x = 5;
    _mazeMax.y = 5;
    if (_glib == NULL)
      {
        _size.x = 0;
        _size.y = 0;
      }
    return;
  }
  for (uint32_t i = 0; i < _ghosts.size(); i++)
  {
      delete _ghosts[i];
  }
  _ghosts.clear();
  while (fs.get(c))
  {
    if (c == '\n')
    {
      if (_mazeMax.x < pos.x)
        _mazeMax.x = pos.x;
      pos.x = 0;
      pos.y++;
      continue;
    }
    (c == 'B') ? (_ghosts.push_back(new Ghost(BLINKY, pClock, pos)), pClock += _fps) : 0;
    (c == 'P') ? (_ghosts.push_back(new Ghost(PINKY, pClock, pos)), pClock += _fps) : 0;
    (c == 'I') ? (_ghosts.push_back(new Ghost(INKY, pClock, pos)), pClock += _fps) : 0;
    (c == 'C') ? (_ghosts.push_back(new Ghost(CLYDE, pClock, pos)), pClock += _fps) : 0;
    if (c == 'S' && pos.x < _size.x && pos.y < _size.y)
      _pacSpawn = pos;
    if (c == 'G' && pos.x < _size.x && pos.y < _size.y)
      _ghostSpawn = pos;
    if (pos.x < _size.x && pos.y < _size.y)
    {
      _tiles[CONVERT(pos.x, pos.y)] = correspond[c];
      _ghostMap.push_back(correspondG[c]);
    }
    pos.x++;
    posG++;
  }
  _mazeMax.y = pos.y;
  fs.close();
  if (_mazeMax.x >= _size.x)
    _mazeMax.x = _size.x - 1;
  if (_mazeMax.y >= _size.y)
    _mazeMax.y = _size.y - 1;
  for (auto it : _ghosts)
  {
    it->setSpawn(_ghostSpawn);
  }
  _pos = _pacSpawn;
}

void Pacman::loseLife(void)
{
  int pClock;

  pClock = _fps * 10;
  _lives--;
  if (_lives == 0)
  {
    Defeat();
    _powerLoop = 0;
    _score = 0;
    _lastFunc = Key::_q;
    _ghostSpawn = {0,0};
    _sens = 1;
    _anim = 0;
    _fps = 10;
    getMap();
    return;
  }
  for (auto it : _ghosts)
  {
    it->setSpawn(_ghostSpawn);
    it->setState(WAITING);
    it->setTime(pClock);
    pClock += _fps;
  }
  _pos = _pacSpawn;
}

Pacman::Pacman(const uint16_t& width, const uint16_t& height, IGraphix *glib)
: AGame(width, height, glib)
{
  _ghostSpawn = {0,0};
  _sens = 1;
  _anim = 0;
  _fps = 10;
  _name = "Pacman";
  getHScore();
  _powerLoop = 0;
  _score = 0;
  _lastFunc = Key::_q;
  getMap();
  if (glib != NULL)
  {
    _sprite = glib->newPA("./res/pacman.bmp");
    if (_sprite->isValid())
      _sprite->setSize((Grix::Size) { _tileSize.x * 3, _tileSize.y * 3});
  }
  _colors[POWERUP] = (Grix::Color){255, 255, 255, 0};
  _colors[EMPTY] = (Grix::Color){30, 30, 0, 0};
  _colors[BLOCK] = (Grix::Color){255, 30, 0, 0};
  _colors[OTHER] = (Grix::Color){120, 120, 120, 0};
  _colors[PLAYER] = (Grix::Color){1, 100, 220, 0};
  if (!_sprite->isValid())
  {
    _colors[POWERUP].argb[3] = 255;
    _colors[EMPTY].argb[3] = 255;
    _colors[BLOCK].argb[3] = 255;
    _colors[OTHER].argb[3] = 255;
    _colors[PLAYER].argb[3] = 255;
  }
}

Pacman::~Pacman()
{
  for (uint32_t i = 0; i < _ghosts.size(); i++)
  {
      delete _ghosts[i];
  }
  _ghosts.clear();
}

void Pacman::continueAct()
{
  const uint8_t   *kb = _glib->getKbSate();

  if (_last == _lastFunc)
    return;
  for (auto& it : _functions)
  {
    if (kb[it.first] == true)
    {
      if (_lastFunc == it.first)
        return;
    }
  }
  _last = _lastFunc;
  goForward();
}

void  Pacman::collision(uint16_t tile, uint32_t *nb, int value)
{
  if (tile == EMPTY || tile == POWERUP || tile == OTHER)
  {
    (*nb) = value;
    if (_last != _lastFunc)
      _lastFunc = _last;
    _anim += 1 * _sens;
    if (_anim == 2)
      _sens = -1;
    if (_anim == 0)
      _sens = 1;
  }
  else
   continueAct();
}

void  Pacman::goUp(void)
{
  uint16_t tile;

  if (_pos.y <= 0)
  {
    tile = _tiles[_pos.x + (_mazeMax.y - 1) * _size.x];
    collision(tile, &_pos.y, _mazeMax.y - 1);
    return;
  }
  tile = _tiles[_pos.x + (_pos.y - 1) * _size.x];
  collision(tile, &_pos.y, _pos.y - 1);
}

void  Pacman::goDown(void)
{
  uint16_t tile;

  if (_pos.y >= _mazeMax.y -1)
  {
    tile = _tiles[_pos.x];
    collision(tile, &_pos.y, 0);
    return;
  }
  tile = _tiles[_pos.x + (_pos.y + 1) * _size.x];
  collision(tile, &_pos.y, _pos.y + 1);
}

void  Pacman::goLeft(void)
{
  uint16_t tile;

  if (_pos.x <= 0)
  {
    tile = _tiles[_mazeMax.x - 1+ (_pos.y) * _size.x];
    collision(tile, &_pos.x, _mazeMax.x - 1);
    return;
  }
  tile = _tiles[_pos.x - 1 + _pos.y * _size.x];
  collision(tile, &_pos.x, _pos.x - 1);
}

void  Pacman::goRight(void)
{
  uint16_t tile;

  if (_pos.x >= _mazeMax.x -1)
  {
    tile = _tiles[_pos.y * _size.y];
    collision(tile, &_pos.x, 0);
    return;
  }
  tile = _tiles[_pos.x + 1 + _pos.y * _size.x];
  collision(tile, &_pos.x, _pos.x + 1);
}

int Pacman::checkContact()
{
  for (auto it : _ghosts)
  {
    if (it->getPos().x == _pos.x && it->getPos().y == _pos.y)
    {
      if (_powerLoop > 0 && it->getState() == FLEE)
      {
        _score += 800;
        it->setState(DEAD);
      }
      else if (it->getState() != DEAD)
      {
        loseLife();
        return (1);
      }
    }
  }
  return (0);
}

void Pacman::compute()
{
  _glib->setFPS(_fps);
  if (checkContact() == 1)
    return;
  for (auto it : _ghosts)
  {
    it->ChoosePoint(_ghostMap, _mazeMax, _pos, _lastFunc, _ghostSpawn);
    it->pathFinding(_ghostMap, _mazeMax);
  }
  if (checkContact() == 1)
    return;
  _powerLoop == 0 ? 0 : _powerLoop--;
  if (_sprite == NULL)
    _tiles[_pos.x + _pos.y * _size.x] = PLAYER;
  if (_tiles[_pos.x + _pos.y * _size.x] == 6)
  {
    _score += 100;
    _tiles[_pos.x + _pos.y * _size.x] = EMPTY;
  }
  if (_tiles[_pos.x + _pos.y * _size.x] == 7)
  {
    _score += 300;
    _tiles[_pos.x + _pos.y * _size.x] = EMPTY;
    _powerLoop = 75;
    for (auto it : _ghosts)
    {
      if (it->getState() != WAITING && it->getState() != DEAD)
        it->setState(FLEE);
    }
  }
  if (std::find(_tiles.begin(), _tiles.end(), 6) == _tiles.end())
  {
    if (std::find(_tiles.begin(), _tiles.end(), 7) == _tiles.end())
    {
      _fps++;
      getMap();
    }
  }
}

void  Pacman::blitGhost(Grix::Position pos, Grix::Position spos, char type) const
{
  Grix::Color col;
  for (unsigned x=0; x<_tileSize.x; ++x)
  {
    for (unsigned y=0; y<_tileSize.y; ++y)
    {
      col  = _sprite->getPixel((Grix::Position){ spos.x + x,
        spos.y + y});
      if (col.full == COLORHOLDER)
      {
        (type == CLYDE) ? (col.argb[Grix::BLUE] = 0, col.argb[Grix::GREEN] = 160) : 0;
        (type == BLINKY) ? (col.argb[Grix::BLUE] = 0) : 0;
        (type == INKY) ? (col.argb[Grix::RED] = 50, col.argb[Grix::GREEN] = 50) : 0;
      }
      _glib->getPA()->setPixel((Grix::Position){pos.x + x, pos.y + y}, col);
    }
  }
}

void  Pacman::blitSprite(Grix::Position pos, Grix::Position spos, Grix::Position rev) const
{
  int rev_inv_x = 1;
  (rev.x == 0) ? 0 : rev_inv_x = -1;
  for (unsigned x=0; x<_tileSize.x; ++x)
  {
    if (rev.y == 1)
    {
      for (unsigned y=0; y<_tileSize.y; ++y)
      {
        _glib->getPA()->setPixel((Grix::Position){pos.x + x, pos.y + y},
          _sprite->getPixel((Grix::Position){ spos.x + y * rev_inv_x + _tileSize.x * rev.x,
            spos.y + x}));
      }
    }
    else
    {
      for (unsigned y=0; y<_tileSize.y; ++y)
      {
        _glib->getPA()->setPixel((Grix::Position){pos.x + x, pos.y + y},
          _sprite->getPixel((Grix::Position){ spos.x + x * rev_inv_x + _tileSize.x * rev.x,
            spos.y + y}));
      }
    }
  }
}

void  Pacman::blitGuy(void) const
{
  if (_sprite->isValid() == false)
    return;
  uint16_t tile_id;
  Grix::Position  rev;
  if (_lastFunc == Key::_q)
    rev = {1, 0};
  else if (_lastFunc == Key::_s)
    rev = {0, 1};
  else if (_lastFunc == Key::_z)
    rev = {1, 1};
  else
    rev = {0, 0};
  Grix::Position  tile = {0, 0};
  Grix::Position  pos = { _pos.x * _tileSize.x, _pos.y * _tileSize.y };
  Grix::Position  spos = {_anim * _tileSize.x, _tileSize.y};
  blitSprite(pos, spos, rev);
  rev = {0, 0};

  spos = {0, _tileSize.y * 2};
  for (auto it : _ghosts)
  {
    pos = it->getPos();
    pos = {pos.x * _tileSize.x, pos.y * _tileSize.y};
    if (it->getState() == DEAD)
      blitGhost(pos, {_tileSize.x * 2, _tileSize.y * 2}, it->getType());
    else if (it->getState() == FLEE && _powerLoop > 0)
      blitGhost(pos, {_tileSize.x, _tileSize.y * 2}, it->getType());
    else
      blitGhost(pos, spos, it->getType());
  }
  while (tile.y != _mazeMax.y)
  {
    tile.x = 0;
    while (tile.x != _mazeMax.x)
    {
      tile_id = _tiles[tile.x + tile.y * _size.x];
      (tile_id == POWERUP) ? (spos.y = 0, spos.x = _tileSize.x) : 0;
      (tile_id == 7) ? (spos.y = 0, spos.x = _tileSize.x * 2) : 0;
      (tile_id == BLOCK) ? (spos.y = 0, spos.x = 0) : 0;
      pos = {tile.x * _tileSize.x, tile.y * _tileSize.y};
      if (tile_id == POWERUP || tile_id == BLOCK || tile_id == 7)
        blitSprite(pos, spos, rev);
      tile.x++;
    }
    tile.y++;
  }
}
