//
// AGraphix.hpp for lol in /home/tetra/rendu/cpp/cpp_arcade/libs
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Thu Mar  9 19:00:29 2017 Arthur Josso
// Last update Tue Mar 21 20:56:03 2017 Arthur Josso
//

#pragma once

#include <SDL.h>
#include "AGraphix.hpp"

class GraphixSDL : public AGraphix
{
public:
  GraphixSDL();
  ~GraphixSDL();

public:
  bool processFrame(GameLoop, void*);
  const uint8_t* getKbSate();
  void flush();

private:
  SDL_Surface *_context;
};
