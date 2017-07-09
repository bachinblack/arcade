//
// Menu.cpp for lol in /home/tetra/rendu/cpp/cpp_arcade
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Tue Mar 21 20:46:56 2017 Arthur Josso
// Last update Sun Apr  9 19:41:31 2017 Arthur Josso
//

#include <iostream>
#include <fstream>
#include "Menu.hpp"

Menu::Menu(Arcade *arcade, IGraphix * & glib)
  : _arcade(arcade), _glib(glib)
{
  _bg = _glib->newPA("./res/menu_bg.bmp");
  _bg->setSize(_glib->getPA()->getSize());
  for (auto it : _arcade->_grixPath)
    _prevGrix.push_back(getPreview(it));
  for (auto it : _arcade->_gamePath)
    _prevGame.push_back(getPreview(it));
  refreshScore();
  _itGrix = _prevGrix.begin();
  _itGame = _prevGame.begin();
}

Menu::~Menu()
{
  delete _bg;
  for (auto it : _prevGrix)
    delete it.img;
  for (auto it : _prevGame)
    delete it.img;
}

void Menu::refreshScore()
{
  std::ifstream file;

  for (size_t i = 0; i < _prevGame.size(); i++)
    {
      file.open(_prevGame[i].scorePath);
      if (!file.is_open())
	_prevGame[i].score = "0";
      else
	{
	  std::string content((std::istreambuf_iterator<char>(file)),
			      (std::istreambuf_iterator<char>()));
	  _prevGame[i].score = content;
	  file.close();
	}
    }
}

Menu::Preview Menu::getPreview(std::string const & path) const
{
  Preview newP;
  std::string name(path.substr(path.rfind("/") + 1));
  std::string nameEpur(name.substr(0, name.rfind(".so")));
  std::string bmpPath("./res/" + nameEpur + ".bmp");
  std::string scorePath("./res/" + nameEpur + ".score");

  newP.path = path;
  newP.img = _glib->newPA(bmpPath);
  newP.img->setSize((Grix::Size){_glib->getPA()->getSize().x / 3,
	    _glib->getPA()->getSize().y / 3});
  newP.scorePath = scorePath;
  newP.score = "0";
  newP.name = nameEpur;
  return (newP);
}

void Menu::run()
{
  keyCallback();
  _glib->blitPA(_bg);
  drawPrevGrix();
  drawPrevGame();
  _glib->flush();
}

void Menu::drawPrevGrix()
{
  Grix::Position center =
    {
      _glib->getPA()->getSize().x / 2 - _itGrix->img->getSize().x / 2,
      _glib->getPA()->getSize().y / 4 - _itGrix->img->getSize().y / 2
    };
  Grix::Position text =
    {
      center.x + _itGrix->img->getSize().x / 2, center.y + _itGrix->img->getSize().y
    };
  _glib->blitPA(_itGrix->img, center);
  _glib->putText(_itGrix->name, text, TITLE_COLOR, 4, true);
}

void Menu::drawPrevGame()
{
  Grix::Position center =
    {
      _glib->getPA()->getSize().x / 2 - _itGame->img->getSize().x / 2,
      3 * _glib->getPA()->getSize().y / 4 - _itGame->img->getSize().y / 2
    };
  Grix::Position text =
    {
      center.x + _itGame->img->getSize().x / 2,
      center.y + _itGame->img->getSize().y
    };
  _glib->blitPA(_itGame->img, center);
  _glib->putText(_itGame->name, text, TITLE_COLOR, 4, true);
  text.y = center.y - _itGame->img->getSize().y / 4;
  _glib->putText("Score : " + _itGame->score, text, TITLE_COLOR, 4, true);
}

bool Menu::isLibSelected() const
{
  return (_glib->getKbSate()[Key::_RETURN]);
}

IGraphix *Menu::updateLibs(GraphixManager *grixManager,
			   GameManager *gameManager) const
{
  IGraphix *tmp;

  tmp = grixManager->switchLib(_itGrix->path.c_str());
  gameManager->switchLib(_itGame->path.c_str(), tmp);
  _arcade->_grixIt = _arcade->_grixPath.begin();
  for (auto it : _arcade->_grixPath)
    {
      if (it == _itGrix->path)
	break;
      _arcade->_grixIt++;
    }
  for (auto it : _arcade->_gamePath)
    {
      if (it == _itGame->path)
	break;
      _arcade->_gameIt++;
    }
  return (tmp);
}

void Menu::keyCallback()
{
  if (_arcade->isKeyPressed(Key::_z))
    {
      if (_itGrix == _prevGrix.begin())
	_itGrix = _prevGrix.end() - 1;
      else
	_itGrix--;
    }
  else if (_arcade->isKeyPressed(Key::_e))
    {
      _itGrix++;
      if (_itGrix == _prevGrix.end())
	_itGrix = _prevGrix.begin();
    }
  if (_arcade->isKeyPressed(Key::_s))
    {
      if (_itGame == _prevGame.begin())
	_itGame = _prevGame.end() - 1;
      else
	_itGame--;
    }
  else if (_arcade->isKeyPressed(Key::_d))
    {
      _itGame++;
      if (_itGame == _prevGame.end())
	_itGame = _prevGame.begin();
    }
}
