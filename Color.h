#ifndef Color_H
#define Color_H

struct Color
{
  unsigned char r,g,b;
  unsigned char red() const {return r;}
  unsigned char green() const {return g;}
  unsigned char blue() const {return b;}
};

#endif
