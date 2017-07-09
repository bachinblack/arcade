//
// Arcade.hpp for lol in /home/tetra/rendu/cpp/cpp_arcade
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Wed Mar 15 16:09:25 2017 Arthur Josso
// Last update Fri Mar 24 16:09:07 2017 Arthur Josso
//

#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include "IGraphix.hpp"
#include "GraphixManager.hpp"
#include "GameManager.hpp"
#include "Menu.hpp"

class Menu;

class Arcade
{
public:
  Arcade(const char *dfltGLib);
  ~Arcade();

public:
  void runMenu();
  int runGame();

private:
  void getFilesInDir(const char *dirPath,
		     std::vector<std::string> & fileList);

private: // core
  IGraphix *_gLib;
  GraphixManager *_grixManager;
  GameManager *_gameManager;
  Menu *_menu;

public: // KB management
  bool isKeyPressed(Key::Key key);
private:
  bool *_isKeyPressed;
  std::unordered_map<unsigned int, std::function<int()> > _keyCallback;
  int setPrevGlib();
  int setNextGlib();
  int setPrevGame();
  int setNextGame();
  int restartGame();
  int exitGame();
  int exitArcade();

public: // lib chooser
  std::vector<std::string> _grixPath;
  std::vector<std::string>::iterator _grixIt;
  std::vector<std::string> _gamePath;
  std::vector<std::string>::iterator _gameIt;
};
