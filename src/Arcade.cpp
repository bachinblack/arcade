//
// Arcade.cpp for lol in /home/tetra/rendu/cpp/cpp_arcade
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Wed Mar 15 16:10:40 2017 Arthur Josso
// Last update Fri Mar 24 16:10:11 2017 Arthur Josso
//

#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include "Arcade.hpp"
#include "Errors.hpp"

Arcade::Arcade(const char *dfltGrixLib)
{
  _grixManager = new GraphixManager;
  _gLib = _grixManager->switchLib(dfltGrixLib);
  _gameManager = new GameManager;
  getFilesInDir("./lib/", _grixPath);
  getFilesInDir("./games/", _gamePath);
  _grixIt = _grixPath.begin();
  _gameIt = _gamePath.begin();
  _isKeyPressed = new bool [Key::LAST] ();
  _keyCallback =
    {
      {Key::_QUOTEDBL, std::bind(&Arcade::setPrevGlib, this)},
      {Key::_QUOTE, std::bind(&Arcade::setNextGlib, this)},
      {Key::_AMPERSAND, std::bind(&Arcade::exitGame, this)},
      {Key::_ESCAPE, std::bind(&Arcade::exitArcade, this)},
      {Key::_LEFTPAREN, std::bind(&Arcade::setPrevGame, this)},
      {Key::_MINUS, std::bind(&Arcade::setNextGame, this)},
      {Key::_UNDERSCORE, std::bind(&Arcade::restartGame, this)}
    };
  _menu = new Menu(this, _gLib);
}

Arcade::~Arcade()
{
  if (_gameManager)
    delete _gameManager;
  delete [] _isKeyPressed;
  delete _menu;
  delete _grixManager;
}

bool Arcade::isKeyPressed(Key::Key key)
{
  const uint8_t *kbState = _gLib->getKbSate();

  if (!kbState[key])
    _isKeyPressed[key] = false;
  else if (!_isKeyPressed[key])
    {
      _isKeyPressed[key] = true;
      return (true);
    }
  return (false);
}

int Arcade::runGame()
{
  int returnType;
  
  while (1)
    {
      if (!_gLib->processFrame(_gameManager->getLoop(),
			       _gameManager->getGame()))
	return (2);
      for (auto& it : _keyCallback)
	if (isKeyPressed(static_cast<Key::Key>(it.first)))
	  if ((returnType = it.second()) != 0)
	    return (returnType);
    }
}

void Arcade::runMenu()
{
  if (_gameIt == _gamePath.end())
    {
      std::cerr << "No games found" << std::endl;
      return;
    }
  while (1)
    {
      _menu->run();
      if (_menu->isLibSelected())
	{
	  _gLib = _menu->updateLibs(_grixManager, _gameManager);
	  _menu->refreshScore();
	  if (runGame() == 2)
	    return;
	}
      if (isKeyPressed(Key::_ESCAPE))
	return;
    }
}

void Arcade::getFilesInDir(const char *dirPath,
			   std::vector<std::string> & fileList)
{
  std::string tmp;
  DIR *dir;
  struct dirent *file;

  if ((dir = opendir(dirPath)) != NULL)
    {
      while ((file = readdir(dir)) != NULL)
	{
	  tmp = dirPath;
	  tmp += file->d_name;
	  if (tmp.substr(tmp.size() - 3) == ".so")
	    fileList.push_back(tmp);
	}
      closedir(dir);
    }
  else
    throw (GameError("ERROR: \"" + std::string(dirPath) + "\" unavailable"));
}

int Arcade::setPrevGlib()
{
  if (_grixIt == _grixPath.begin())
    _grixIt = _grixPath.end() - 1;
  else
    _grixIt--;
  _gLib = _grixManager->switchLib(_grixIt->c_str());
  _gameManager->newGrixLib(_gLib);
  return (0);
}

int Arcade::setNextGlib()
{
  _grixIt++;
  if (_grixIt == _grixPath.end())
    _grixIt = _grixPath.begin();
  _gLib = _grixManager->switchLib(_grixIt->c_str());
  _gameManager->newGrixLib(_gLib);
  return (0);
}

int Arcade::setPrevGame()
{
  if (_gameIt == _gamePath.begin())
    _gameIt = _gamePath.end() - 1;
  else
    _gameIt--;
  _gameManager->switchLib(_gameIt->c_str(), _gLib);
  return (0);
}

int Arcade::setNextGame()
{
  _gameIt++;
  if (_gameIt == _gamePath.end())
    _gameIt = _gamePath.begin();
  _gameManager->switchLib(_gameIt->c_str(), _gLib);
  return (0);
}

int Arcade::restartGame()
{
  _gameManager->switchLib(_gameIt->c_str(), _gLib);
  return (0);
}

int Arcade::exitGame() {return (1);}
int Arcade::exitArcade() {return (2);}
