#include "DrawFont.h"

DrawFont::DrawFont(const char* font_name, uint32 size) : draw_pen(wxColour(0,0,0), 5), draw_font(font_name)
{
	font_size = size;
}

DrawFont::~DrawFont() 
{}

void DrawFont::draw(wxDC& dc, std::string text, uint32 left, uint32 top)
{
	dc.SetPen(draw_pen);
	
	draw_font.SetPointSize(font_size);
	draw_font.MakeBold();
	dc.SetFont(draw_font);
	
	wxString draw_str(text);
	dc.DrawText(draw_str, left, top);
}
