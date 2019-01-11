#if !defined DRAW_FONT_H
#define DRAW_FONT_H

#include "GUIHeader.h"
#include "wx/wx.h"

class DrawFont
{
	private:
		wxPen draw_pen;
		wxFont draw_font;
		uint32 font_size;
		
	public:
		DrawFont(const char* font_name, uint32 font_size);
		virtual ~DrawFont();
		
		void draw(wxDC& dc, std::string text, uint32 left, uint32 top);
};

#endif
