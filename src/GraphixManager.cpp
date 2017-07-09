//
// GraphixManager.cpp for lol in /home/tetra/rendu/cpp/cpp_arcade
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Thu Mar  9 20:30:41 2017 Arthur Josso
// Last update Mon Mar 27 15:02:23 2017 Arthur Josso
//

#include <iostream>
#include <dlfcn.h>
#include "Errors.hpp"
#include "GraphixManager.hpp"

GraphixManager::GraphixManager() :
  _curLib(_lib.end()) {}

GraphixManager::~GraphixManager()
{
  (*_curLib->second.dtor)(_curLib->second.instance);
  for (auto it = _lib.begin(); it != _lib.end(); it++)
    dlclose(it->second.handle);
}

void *GraphixManager::_loadSym(const char *symName)
{
  const char *dlsym_error;
  void *sym;

  sym = dlsym(_curLib->second.handle, symName);
  dlsym_error = dlerror();
  if (dlsym_error)
    throw (GraphicError(std::string("Cannot load symbol create: ") + dlsym_error));
  return (sym);
}

IGraphix *GraphixManager::switchLib(const char *path_name)
{
  std::unordered_map<std::string, Glib>::iterator it = _lib.find(path_name);
  if (_curLib!= _lib.end())
    (*_curLib->second.dtor)(_curLib->second.instance);
  if (it != _lib.end())
    _curLib = it;
  else
    {
      _lib[path_name];
      _curLib = _lib.find(path_name);
      _curLib->second.handle = dlopen(path_name, RTLD_LAZY);
      if (!_curLib->second.handle)
	throw (GraphicError(std::string("Cannot load library: ") + dlerror()));
      dlerror();
      _curLib->second.ctor = (FuncInitLib)_loadSym("create");
      _curLib->second.dtor = (FuncFiniLib)_loadSym("destroy");
    }
  _curLib->second.instance = (*_curLib->second.ctor)();
  return (_curLib->second.instance);
}
