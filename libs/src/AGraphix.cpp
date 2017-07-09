//
// AGraphix.cpp for lol in /home/tetra/rendu/cpp/cpp_arcade/libs
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Thu Mar  9 19:00:01 2017 Arthur Josso
// Last update Sun Mar 26 19:57:11 2017 Philippe Bouttereux
//

#include <thread>
#include <stddef.h>
#include "AGraphix.hpp"
#include "PixArray.hpp"

AGraphix::AGraphix() :
  _kbState(NULL), _frameDuration((1.0 / 30) * 1000)
{
  _PA = new Grix::PixArray((Grix::Size){800, 675});
  _font = new Grix::PixArray("./res/font.bmp");
  _kbState = new uint8_t[Key::LAST] ();
}

AGraphix::~AGraphix()
{
  delete _PA;
  delete _font;
  delete[] _kbState;
}

void AGraphix::_frameLimit()
{
  static Clock::time_point t0 = Clock::now();
  Clock::time_point t1;
  milliseconds maxDuration = milliseconds(_frameDuration);
  milliseconds actDuration;
  t1 = Clock::now();
  actDuration = std::chrono::duration_cast<milliseconds>(t1 - t0);
  if (actDuration < maxDuration)
    std::this_thread::sleep_for(maxDuration - actDuration);
  t0 = Clock::now();
}

void AGraphix::blitPA(Grix::IPixArray const * pixArray,
		      Grix::Position const & pos)
{
  Grix::Position rel;
  Grix::Position abs;

  for (rel.x = 0, abs.x = pos.x; rel.x < pixArray->getSize().x; abs.x++, rel.x++)
    for (rel.y = 0, abs.y = pos.y; rel.y < pixArray->getSize().y; abs.y++, rel.y++)
      _PA->setPixel(abs, pixArray->getPixel(rel));
}

void AGraphix::setFPS(uint16_t fps) { _frameDuration = (1.0 / fps) * 1000; }

Grix::IPixArray *AGraphix::newPA(Grix::Size const & size,
				Grix::Color const & color)
{
  return (new Grix::PixArray(size, color));
}

Grix::IPixArray *AGraphix::newPA(std::string const & bmpPath)
{
  return (new Grix::PixArray(bmpPath));
}

Grix::IPixArray *AGraphix::getPA() { return (_PA); }

extern "C"
void	destroy(IGraphix *graph)
{
  delete graph;
}
