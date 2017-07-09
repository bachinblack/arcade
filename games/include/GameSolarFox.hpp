//
// GameSolarFox.hpp for GameSolarFox in /home/bachinblack/work/cpp/lol/cpp_arcade/games/include/GameSolarFox
//
// Made by Philippe Bouttereux
// Login   <bachinblack@epitech.eu>
//
// Started on  Mon Mar 27 14:23:41 2017 Philippe Bouttereux
// Last update Sun Apr  9 19:33:31 2017 Philippe Bouttereux
//

#ifndef __SOLAR_FOX_HPP__
# define __SOLAR_FOX_HPP__

#include "AGame.hpp"

class SolarFox : public AGame
{
public:
  SolarFox(const uint16_t& width, const uint16_t& height, IGraphix *glib);
  ~SolarFox();

private:
  void    goForward(void);
  void    compute(void);
  void    decrlives(void);
  void    refresh(void);
  void    back(void);

private:
};

#endif /* __SOLAR_FOX_HPP__ */