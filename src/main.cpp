//
// main.cpp for lol in /home/tetra/rendu/cpp/cpp_arcade
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Thu Mar  9 19:13:13 2017 Arthur Josso
// Last update Thu Mar 23 20:26:54 2017 Arthur Josso
//

#include <iostream>
#include "Arcade.hpp"

int	main()
{
  Arcade arcade("libs/lib_arcade_sdl.so");

  arcade.runMenu();
  return (0);
}
