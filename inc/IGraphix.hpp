//
// IGraphix.hpp for lol in /home/tetra/rendu/cpp/cpp_arcade/libs
// 
// Made by Arthur Josso
// Login   <arthur.josso@epitech.eu>
// 
// Started on  Thu Mar  9 17:59:06 2017 Arthur Josso
// Last update Sun Mar 26 18:41:54 2017 Philippe Bouttereux
//

#pragma once

#include <stdint.h>
#include <string>

#define MAP(x, ba, ea, bb, eb) ((uint32_t)(((((float)ba - (float)x) / \
					     ((float)ba - (float)ea)) * \
					    ((float)eb - (float)bb)) + (float)bb))
#define MAP0(x, mx, m) ((uint32_t)((float)(x) * (float)(m) / (float)(mx)))
#define FCOLOR(x) ((float)(x) / 255.0)
#define FMAP(x, mx, m) ((float)(x) * (float)(m) / (float)(mx))

namespace Grix
{
  struct Position
  {
    Position(uint32_t tx = 0, uint32_t ty = 0)
      : x(tx), y(ty) {}
    bool operator==(Position const & other)
    {return other.x == x && other.y == y ? true : false;}
    bool operator!=(Position const & other)
    {return other.x == x && other.y == y ? false : true;}

    uint32_t x;
    uint32_t y;
  };

  typedef Position Size;

  union Color
  {
    uint8_t	argb[4];
    uint32_t	full;
  };
  
  enum Color_bytes
    {
      BLUE = 0,
      GREEN,
      RED,
      ALPHA
    };

  class IPixArray
  {
  public:
    virtual ~IPixArray() {}

  public:
    virtual void setPixel(Position const & pos, Color const & color) = 0;
    virtual void setSize(Size const & size) = 0;
    virtual Color const & getPixel(Position const & pos) const = 0;
    virtual Size const & getSize() const = 0;
    virtual void clear() = 0;
    virtual bool isValid() = 0;
  };
};

class IGraphix
{
public:
  virtual ~IGraphix() {}

public:
  virtual void setFPS(uint16_t fps) = 0;
  virtual const uint8_t* getKbSate() = 0;
  typedef bool (*GameLoop)(void*);
  virtual bool processFrame(GameLoop, void *) = 0;
  virtual void flush() = 0;
  virtual void putText(std::string const & text, Grix::Position const & pos,
		       Grix::Color color, uint8_t size, bool centered) = 0;

public:
  virtual Grix::IPixArray *newPA(Grix::Size const & size,
				 Grix::Color const & color = {}) = 0;
  virtual Grix::IPixArray *newPA(std::string const & bmpPath) = 0;
  virtual void blitPA(Grix::IPixArray const * pixArray,
		      Grix::Position const & pos = {}) = 0;
  virtual Grix::IPixArray *getPA() = 0;
};

namespace Key
{
  typedef enum
    {
      _UNKNOWN= 0,
      _FIRST= 0,
      _BACKSPACE= 8,
      _TAB= 9,
      _CLEAR= 12,
      _RETURN= 13,
      _PAUSE= 19,
      _ESCAPE= 27,
      _SPACE= 32,
      _EXCLAIM= 33,
      _QUOTEDBL= 34,
      _HASH= 35,
      _DOLLAR= 36,
      _AMPERSAND= 38,
      _QUOTE= 39,
      _LEFTPAREN= 40,
      _RIGHTPAREN= 41,
      _ASTERISK= 42,
      _PLUS= 43,
      _COMMA= 44,
      _MINUS= 45,
      _PERIOD= 46,
      _SLASH= 47,
      _0= 48,
      _1= 49,
      _2= 50,
      _3= 51,
      _4= 52,
      _5= 53,
      _6= 54,
      _7= 55,
      _8= 56,
      _9= 57,
      _COLON= 58,
      _SEMICOLON= 59,
      _LESS= 60,
      _EQUALS= 61,
      _GREATER= 62,
      _QUESTION= 63,
      _AT= 64,

      _LEFTBRACKET= 91,
      _BACKSLASH= 92,
      _RIGHTBRACKET= 93,
      _CARET= 94,
      _UNDERSCORE= 95,
      _BACKQUOTE= 96,
      _a= 97,
      _b= 98,
      _c= 99,
      _d= 100,
      _e= 101,
      _f= 102,
      _g= 103,
      _h= 104,
      _i= 105,
      _j= 106,
      _k= 107,
      _l= 108,
      _m= 109,
      _n= 110,
      _o= 111,
      _p= 112,
      _q= 113,
      _r= 114,
      _s= 115,
      _t= 116,
      _u= 117,
      _v= 118,
      _w= 119,
      _x= 120,
      _y= 121,
      _z= 122,
      _DELETE= 127,

      _UP= 273,
      _DOWN= 274,
      _RIGHT= 275,
      _LEFT= 276,
      _INSERT= 277,
      _HOME= 278,
      _END= 279,
      _PAGEUP= 280,
      _PAGEDOWN= 281,

      _F1= 282,
      _F2= 283,
      _F3= 284,
      _F4= 285,
      _F5= 286,
      _F6= 287,
      _F7= 288,
      _F8= 289,
      _F9= 290,
      _F10= 291,
      _F11= 292,
      _F12= 293,
      _F13= 294,
      _F14= 295,
      _F15= 296,

      _NUMLOCK= 300,
      _CAPSLOCK= 301,
      _SCROLLOCK= 302,
      _RSHIFT= 303,
      _LSHIFT= 304,
      _RCTRL= 305,
      _LCTRL= 306,
      _RALT= 307,
      _LALT= 308,
      _RMETA= 309,
      _LMETA= 310,
      _LSUPER= 311,
      _RSUPER= 312,
      _MODE= 313,
      _COMPOSE= 314,

      _HELP= 315,
      _PRINT= 316,
      _SYSREQ= 317,
      _BREAK= 318,
      _MENU= 319,
      _POWER= 320,
    
      LAST
    } Key;
}
