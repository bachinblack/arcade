//
// AGame.hpp for AGame$ in /home/bachinblack/work/cpp/cpp_arcade/games/include/AGame
//
// Made by Philippe Bouttereux
// Login   <bachinblack@epitech.eu>
//
// Started on  Wed Mar 15 00:24:51 2017 Philippe Bouttereux
// Last update Sat Apr  8 16:54:46 2017 Philippe Bouttereux
//

#ifndef __AGAME_HPP__
# define __AGAME_HPP__

#include <unordered_map>
#include <vector>
#include <chrono>
#include <deque>
#include <functional>
#include <fstream>
#include "IGame.hpp"
#include "IGraphix.hpp"
#include "Protocol.hpp"

class AGame : public IGame
{
public:
  typedef std::function<void()> InputFunc;
  typedef std::function<void()> my_out;
  AGame(const uint16_t& width, const uint16_t& height, IGraphix *&glib);
  ~AGame();


public:
  void            setGrixLib(IGraphix *lib);
  void            getInput(void);
  void            sendOutput(void);
  void            readInput();
  uint16_t        getTile(const int& x, const int& y) const;

protected:
  void    drawTile(const Grix::Position& pos, const Grix::Color& col) const;
  void    readKeyboard();
  void    gameOver(void);
  void    printInfos(void);
  void    Pause(void);
  void    Victory(void);
  void    Defeat(void);
  void    Play(void);
  void    LvlUp(const unsigned& i);
  void    end(void);
  void    dispPause(void) const;
  void    setForward(void);
  void    setUp(void);
  void    setDown(void);
  void    setLeft(void);
  void    setRight(void);
  void    playRound(void);
  void    getHScore();
  void    updateMap(const std::string& name, const std::string& code);
  virtual void    printMap(void);
  virtual void    whereAmI(void);
  virtual void    Shoot(void);
  virtual void    compute(void);
  virtual void    goForward(void);
  virtual void    goDown(void);
  virtual void    goLeft(void);
  virtual void    goRight(void);
  virtual void    goUp(void);
  virtual void    blitMap(void) const;
  virtual void    blitGuy(void) const;

protected:
  typedef std::chrono::high_resolution_clock Clock;
  Clock::time_point           _t0;
  uint16_t                    _lives;
  std::string                 _pstr;
  std::string                 _name;
  InputFunc                   input;
  my_out                      output;
  IGraphix                   *_glib;
  Grix::Size                  _size;
  Grix::Position              _pos;
  unsigned                    _last;
  std::vector<uint16_t>       _tiles;
  Grix::Size                  _tileSize;
  std::deque<Grix::Position>  _positions;
  unsigned long               _gameFPS;
  std::vector<Grix::Color>    _colors;
  unsigned int                _score;
  unsigned int                _hscore;
  Grix::Position              _infospos;
  std::ifstream               _fs;
  std::unordered_map<unsigned int, std::function<void()> > _functions;
};

#endif /* __AGAME_HPP__ */
