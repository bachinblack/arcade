//
// GameQix.hpp for GameQix in /home/bachinblack/work/cpp/lol/cpp_arcade/games/include/GameQix
//
// Made by Philippe Bouttereux
// Login   <bachinblack@epitech.eu>
//
// Started on  Tue Mar 21 16:33:52 2017 Philippe Bouttereux
// Last update Sat Apr  8 17:00:49 2017 Philippe Bouttereux
//

#ifndef __QIX_HPP__
# define __QIX_HPP__

# define ABS(x) (x < 0 ? -x : x)
# define TOONE(x) (x < 0 ? x = -1 : x = 1)

#include "AGame.hpp"

// note for check and unfill
// the parameter is neither const nor reference because the position need to be kept under control due to recursivity

class Qix : public AGame
{
public:
  Qix(const uint16_t& width, const uint16_t& height, IGraphix *glib);
  ~Qix();
  void compute();
  void setSpawn(const Grix::Position &);

private:
  void      goDown(void);
  void      goLeft(void);
  void      goRight(void);
  void      goUp(void);
  void      refresh(void);

private:
  bool      check(Grix::Position pos);
  void      unfill(Grix::Position pos);
  void      Erase(void);
  void      moveEvilsCW(Grix::Position& pos);
  void      moveEvilsRand(void);

private:
  unsigned                    _max;
  std::vector<Grix::Position> _evils;
  Grix::Position              _lpos;
};

extern "C"
void play();

#endif /* __QIX_HPP__ */
