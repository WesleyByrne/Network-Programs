#ifndef DRAWABLE
#define DRAWABLE

#include "wx/wx.h"

class Drawable
{
   private:

   public:
      Drawable() {};
      virtual ~Drawable() {};
	  
      virtual void draw(wxDC&  dc, int width, int height) = 0;
      virtual void mouseClicked(int x, int y) = 0;
	  virtual void keyPressed(int key_code) = 0;
};

#endif
