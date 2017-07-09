//
// Menu.hpp for lol in /home/tetra/rendu/cpp/cpp_arcade
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Tue Mar 21 20:24:34 2017 Arthur Josso
// Last update Sun Apr  9 19:07:00 2017 Arthur Josso
//

#pragma once

#include <vector>
#include "IGraphix.hpp"
#include "Arcade.hpp"

#define TITLE_COLOR ((Grix::Color){0x2A, 0x2A, 0xA5, 0xFF})

class Arcade;

class Menu
{
public:
  Menu(Arcade *arcade, IGraphix * & glib);
  ~Menu();

public:
  void run();
  bool isLibSelected() const;
  void refreshScore();
  IGraphix *updateLibs(GraphixManager *grixManager,
		       GameManager *gameManager) const;

private:
  Arcade *_arcade;
  IGraphix * & _glib;
  Grix::IPixArray *_bg;
  struct Preview
  {
    Grix::IPixArray *img;
    std::string path;
    std::string name;
    std::string scorePath;
    std::string score;
  };
  std::vector<Preview> _prevGrix;
  std::vector<Preview>::iterator _itGrix;
  std::vector<Preview> _prevGame;
  std::vector<Preview>::iterator _itGame;

private:
  Preview getPreview(std::string const & path) const;
  void drawPrevGrix();
  void drawPrevGame();
  void keyCallback();
};
