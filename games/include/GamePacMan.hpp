//
// GamePacMan.hpp for GamePacMan in /home/bachinblack/work/cpp/lol/cpp_arcade/games/include/GamePacMan
//
// Made by Philippe Bouttereux
// Login   <bachinblack@epitech.eu>
//
// Started on  Sat Mar 18 17:36:14 2017 Philippe Bouttereux
// Last update Sun Apr  9 20:59:12 2017 Kotra
//

#ifndef __PACMAN_HPP__
# define __PACMAN_HPP__

#include "IGraphix.hpp"
#include "AGame.hpp"

enum  State
{
  DEAD,
  WAITING,
  FLEE,
  CHASING
};

enum ghostId
{
  BLINKY = 0,
  PINKY,
  INKY,
  CLYDE
};

enum Guy
{
  WALL,
  PACMAN,
  GHOST
};

typedef struct
{
  int       value;
  int       dir;
}           t_mapTile;

# define VALID(x, max) ((x) >= 0 && (x) < (max)) ? (1) : (0)
# define ABS(x) ((x) < 0) ? (-(x)) : (x)
# define COLORHOLDER 4294902015
class Ghost
{
public:
  Ghost(const int &cmp, const int &pClock, const Grix::Position &pos);
  ~Ghost();
  std::function<void()> _pattern;
  void            setPos(const Grix::Position&);
  Grix::Position  getPos(void) const;
  void            setID(const char &id);
  void            setSpawn(Grix::Position const &);
  void            setTime(int);
  void            setState(char);
  void            action();
  void            pathFinding(std::vector<t_mapTile>, const Grix::Position &);
  Grix::Position const &getPos(void);
  char           const &getState(void);
  char           const &getType(void);
  void            ChoosePoint(const std::vector<t_mapTile> &map,
                          const Grix::Position &mazeMax,
                          const Grix::Position &pPos,
                          const unsigned int &last,
                          const Grix::Position &);
protected:
  void  goDeeper(std::vector<t_mapTile> &, Grix::Position,
                        const Grix::Position &, const Grix::Position &, int);

private:
  int             clydeChoice(const Grix::Position &pPos);
  int             pinkyChoice(const std::vector<t_mapTile> &map,
                              const Grix::Position &mazeMax,
                              const Grix::Position &pPos,
                              const unsigned int &last);
  int             checkAround(const std::vector<t_mapTile> &,
                              const Grix::Position &,
                              const Grix::Position &,
                              t_mapTile *, const Grix::Position &, int);
  void            choose(const std::vector<t_mapTile> &,
                        const Grix::Position &);

private:
  Grix::Position    _pos;
  Grix::Position    _home;
  Grix::Position    _focus;
  char              _state;
  uint16_t          _target;
  char              _type;
  int               _pClock;
  int               _dir;
};

class Pacman : public AGame
{
public:
  Pacman(const uint16_t& width, const uint16_t& height, IGraphix *glib);
  ~Pacman();
  void compute();

private:
  void  getMap(void);
  void  collision(uint16_t tile, uint32_t *nb, int value);
  void  continueAct();
  void  blitSprite(Grix::Position pos, Grix::Position spos, Grix::Position) const;
  void  blitGhost(Grix::Position pos, Grix::Position spos, char) const;
  void  loseLife(void);
  int   checkContact();
protected:
  void  goDown(void);
  void  goLeft(void);
  void  goRight(void);
  void  goUp(void);
private:
  void              blitGuy(void) const;
  Grix::IPixArray         *_sprite;
  Grix::Position          _mazeMax;
  unsigned int            _powerLoop;
  unsigned                _lastFunc;
  std::vector<Ghost *>    _ghosts;
  std::vector<t_mapTile>  _ghostMap;
  Grix::Position          _ghostSpawn;
  Grix::Position          _pacSpawn;
  int                     _fps;
  int                     _anim;
  int                     _sens;
};

extern "C"
void play();

#endif /* __PACMAN_HPP__ */
