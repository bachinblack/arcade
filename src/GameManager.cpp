//
// GameManager.cpp for lol in /home/tetra/rendu/cpp/cpp_arcade
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Thu Mar  9 20:30:41 2017 Arthur Josso
// Last update Mon Mar 27 15:01:42 2017 Arthur Josso
//

#include <iostream>
#include <dlfcn.h>
#include "GameManager.hpp"
#include "Errors.hpp"

GameManager::GameManager() :
  _ctor(NULL), _dtor(NULL), _loop(NULL), _instance(NULL), _handle(NULL) {}

GameManager::~GameManager()
{
  _deletePreviousLib();
}

void GameManager::_deletePreviousLib()
{
  if (_handle)
    {
      if (_dtor)
	(*_dtor)(_instance);
      dlclose(_handle);
      _instance = NULL;
      _handle = NULL;
      _ctor = NULL;
      _dtor = NULL;
      _loop = NULL;
    }
}

void *GameManager::_loadSym(const char *symName)
{
  const char *dlsym_error;
  void *sym;

  sym = dlsym(_handle, symName);
  dlsym_error = dlerror();
  if (dlsym_error)
    throw (GameError(std::string("Cannot load symbol create: ") + dlsym_error));
  return (sym);
}

void GameManager::newGrixLib(IGraphix *glib)
{
  _instance->setGrixLib(glib);
}

void GameManager::switchLib(const char *path_name, IGraphix *glib)
{
  _deletePreviousLib();
  _handle = dlopen(path_name, RTLD_LAZY);
  if (!_handle)
    throw (GameError(std::string("Cannot load library: ") + dlerror()));
  dlerror();

  _ctor = (FuncInitLib)_loadSym("initGame");
  _dtor = (FuncFiniLib)_loadSym("finiGame");
  _loop = (GameLoop)_loadSym("loopGame");

  _instance = (*_ctor)(glib);
}

GameManager::GameLoop GameManager::getLoop() const {return(_loop);}
IGame *GameManager::getGame() const {return(_instance);}
