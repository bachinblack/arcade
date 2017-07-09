//
// Errors.hpp for lol in /home/tetra/rendu/cpp/cpp_nanotekspice
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Fri Feb  3 14:36:59 2017 Arthur Josso
// Last update Tue Mar 21 20:06:37 2017 Arthur Josso
//

#pragma once

#include <string>
#include <exception>

class GraphicError : public std::exception
{
public:
  ~GraphicError() throw() {}
  GraphicError(std::string const &message) : _message(message) {}
  const char * what() const throw() {return (_message.c_str());}
private:
  std::string _message;
};

class GameError : public std::exception
{
public:
  ~GameError() throw() {}
  GameError(std::string const &message) : _message(message) {}
  const char * what() const throw() {return (_message.c_str());}
private:
  std::string _message;
};
