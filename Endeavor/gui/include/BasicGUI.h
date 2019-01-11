#ifndef BASIC_GUI
#define BASIC_GUI

#include "wx/wx.h"
#include "Drawable.h"

class BasicGUI : public wxFrame
{
   private:

   public:
      BasicGUI(int x_loc, int y_loc, int width, int height, Drawable* drawable);
      virtual ~BasicGUI();
	  
	  void show();
	  void setTitle(std::string);
	  
	  DECLARE_EVENT_TABLE()
};

#endif 
