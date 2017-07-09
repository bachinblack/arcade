//
// AGraphix.hpp for lol in /home/tetra/rendu/cpp/cpp_arcade/libs
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Thu Mar  9 19:00:29 2017 Arthur Josso
// Last update Thu Mar 23 20:38:05 2017 Arthur Josso
//

#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "AGraphix.hpp"

class GraphixGL : public AGraphix
{
public:
  GraphixGL();
  ~GraphixGL();

public:
  bool processFrame(GameLoop, void*);
  const uint8_t* getKbSate();
  void flush();

private:
  SDL_Window *_context;
  SDL_GLContext _GLcontext;
};
