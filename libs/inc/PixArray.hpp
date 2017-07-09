//
// IGraphix.hpp for lol in /home/tetra/rendu/cpp/cpp_arcade/libs
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Thu Mar  9 17:59:06 2017 Arthur Josso
// Last update Fri Mar 24 13:16:16 2017 Arthur Josso
//

#pragma once

#include "IGraphix.hpp"

namespace Grix
{
  class PixArray : public IPixArray
  {
  public:
    PixArray(Size const & size, Color const & color = {});
    PixArray(std::string const & bmpPath);
    ~PixArray();

  public:
    void setPixel(Position const & pos, Color const & color);
    void setSize(Size const & size);
    Color const & getPixel(Position const & pos) const;
    Size const & getSize() const;
    void clear();
    bool isValid();
    
  private:
    Size _size;
    Color *_buffer;
  };
};
