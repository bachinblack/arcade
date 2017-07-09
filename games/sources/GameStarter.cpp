//
// snakeStarter.cpp for snakeStarter in /home/bachinblack/work/cpp/cpp_arcade/games/sources/snakeStarter
//
// Made by Philippe Bouttereux
// Login   <bachinblack@epitech.eu>
//
// Started on  Wed Mar 15 00:30:58 2017 Philippe Bouttereux
// Last update Sun Mar 26 18:34:14 2017 Philippe Bouttereux
//

#include <iostream>
#include "AGame.hpp"

extern "C"
void    finiGame(IGame *game)
{
  delete game;
}

extern "C"
bool    loopGame(void *data)
{
  IGame *game = static_cast<IGame *>(data);

  game->getInput();
  game->compute();
  game->sendOutput();
  game->printInfos();
  return true;
}

extern "C"
void  play(void)
{
  IGame *game = initGame(NULL);

  while (loopGame(game));
  finiGame(game);
}
