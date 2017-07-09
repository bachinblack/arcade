//
// GraphixManager.hpp for lol in /home/tetra/rendu/cpp/cpp_arcade
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Thu Mar  9 20:24:57 2017 Arthur Josso
// Last update Wed Mar 22 13:59:21 2017 Arthur Josso
//

#pragma once

#include <unordered_map>
#include <string>
#include "IGraphix.hpp"

class GraphixManager
{
public:
  GraphixManager();
  ~GraphixManager();

public:
  IGraphix *switchLib(const char *path_name);

private:
  void _deletePreviousLib();
  void *_loadSym(const char *symName);

private:
  typedef IGraphix *(*FuncInitLib)();
  typedef void (*FuncFiniLib)(IGraphix*);
  struct Glib
  {
    FuncInitLib ctor;
    FuncFiniLib dtor;
    IGraphix *instance;
    void *handle;
  };
  std::unordered_map<std::string, Glib> _lib;
  std::unordered_map<std::string, Glib>::iterator _curLib;
};
