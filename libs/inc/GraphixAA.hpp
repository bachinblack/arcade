//
// AGraphix.hpp for lol in /home/tetra/rendu/cpp/cpp_arcade/libs
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Thu Mar  9 19:00:29 2017 Arthur Josso
// Last update Tue Mar 21 20:56:12 2017 Arthur Josso
//

#pragma once

#include <aalib.h>
#include <unordered_map>
#include "AGraphix.hpp"

class GraphixAA : public AGraphix
{
public:
  GraphixAA();
  ~GraphixAA();

public:
  bool processFrame(GameLoop, void*);
  const uint8_t* getKbSate();
  void flush();

private:
  aa_context *_context;

private:
  std::unordered_map<unsigned int, int > _keyTab;
};
