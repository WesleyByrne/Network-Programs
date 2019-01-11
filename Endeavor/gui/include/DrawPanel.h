#ifndef DRAW_PANEL
#define DRAW_PANEL

#include "Drawable.h"
#include "Rect.h"
#include "wx/wx.h"
#include "wx/dcbuffer.h"

class DrawPanel : public wxPanel
{
	
	private:
		Drawable* drawable;
 
	public:
		DrawPanel(wxFrame* parent);
		virtual ~DrawPanel();
	
		void setDrawable(Drawable* d);
	
		void mouseLeftDown(wxMouseEvent& event);
	
		void keyPressed(wxKeyEvent& event);
 
		void paintEvent(wxPaintEvent& evt);
		//void paintNow();
 
		void render(wxDC& dc);
 
		// some useful events
		/*
		void mouseMoved(wxMouseEvent& event);
		void mouseDown(wxMouseEvent& event);
		void mouseWheelMoved(wxMouseEvent& event);
		void mouseReleased(wxMouseEvent& event);
		void rightClick(wxMouseEvent& event);
		void mouseLeftWindow(wxMouseEvent& event);
     
		void keyReleased(wxKeyEvent& event);
		*/
 
		DECLARE_EVENT_TABLE()
};

#endif
