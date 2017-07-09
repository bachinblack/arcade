//
// AGraphix.hpp for lol in /home/tetra/rendu/cpp/cpp_arcade/libs
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Thu Mar  9 19:00:29 2017 Arthur Josso
// Last update Sun Mar 26 19:53:32 2017 Philippe Bouttereux
//

#pragma once

#include <chrono>
#include "IGraphix.hpp"

class AGraphix : public IGraphix
{
public:
  AGraphix();
  virtual ~AGraphix();

public:
  virtual bool processFrame(GameLoop, void*) = 0;
  virtual const uint8_t * getKbSate() = 0;
  virtual void flush() = 0;

public:
  void setFPS(uint16_t fps);
  virtual void putText(std::string const & text, Grix::Position const & pos,
		       Grix::Color color, uint8_t size, bool centered);

public:
  Grix::IPixArray *getPA();
  Grix::IPixArray *newPA(Grix::Size const & size,
			 Grix::Color const & color = {});
  Grix::IPixArray *newPA(std::string const & bmpPath);
  void resizePA(Grix::IPixArray * pixArray,
		Grix::Size const & size);
  void blitPA(Grix::IPixArray const * pixArray,
	      Grix::Position const & pos = {});

protected:
  Grix::IPixArray *_PA;
  uint8_t *_kbState;
  long _frameDuration;
  Grix::IPixArray *_font;

protected:
  typedef std::chrono::high_resolution_clock Clock;
  typedef std::chrono::milliseconds milliseconds;
  void _frameLimit();

private:
  void putChar(char c, Grix::Position const & pos,
	       Grix::Color color, uint8_t size);
};
