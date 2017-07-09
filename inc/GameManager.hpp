//
// GameManager.hpp for lol in /home/tetra/rendu/cpp/cpp_arcade
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Thu Mar  9 20:24:57 2017 Arthur Josso
// Last update Thu Mar 16 22:06:39 2017 Arthur Josso
//

#pragma once

#include "IGraphix.hpp"
#include "IGame.hpp"

class GameManager
{
public:
  GameManager();
  ~GameManager();

public:
  void switchLib(const char *path_name, IGraphix *glib);
  void newGrixLib(IGraphix *glib);  

private:
  void _deletePreviousLib();
  void *_loadSym(const char *symName);

private:
  typedef IGame *(*FuncInitLib)(IGraphix*);
  typedef void (*FuncFiniLib)(IGame*);
  typedef bool (*GameLoop)(void*);
  FuncInitLib _ctor;
  FuncFiniLib _dtor;
  GameLoop _loop;
  IGame *_instance;
  void *_handle;

public:
  GameLoop getLoop() const;
  IGame *getGame() const;
};
