#ifndef NULLDRAWABLE_H
#define NULLDRAWABLE_H

#include "Drawable.h"
#include "wx/wx.h"

class NullDrawable : public Drawable
{
   private:

   public:
      NullDrawable() {};
      virtual ~NullDrawable() {};
	  
      virtual void draw(wxDC&  dc, int width, int height);
      virtual void mouseClicked(int x, int y);
	  void keyPressed(int key_code);
};

#endif
