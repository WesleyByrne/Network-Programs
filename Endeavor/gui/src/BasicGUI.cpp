#include "BasicGUI.h"
#include "DrawPanel.h"

BEGIN_EVENT_TABLE (BasicGUI, wxFrame)
	//EVT_BUTTON (wxID_HIGHEST + 1, CLGUI::on_cl_button_click_event) 
END_EVENT_TABLE() 

BasicGUI::BasicGUI(int x_loc, int y_loc, int width, int height, Drawable* drawable) : wxFrame((wxFrame *)NULL, -1,  wxT("Draw"), wxPoint(x_loc, y_loc), wxSize(width, height))
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	//have to specify the draw_panel's parent
 	DrawPanel* draw_panel = new DrawPanel(this);
	draw_panel->setDrawable(drawable);
	
    sizer->Add(draw_panel, 10, wxEXPAND);
    SetSizer(sizer);
    SetAutoLayout(true);
}

void BasicGUI::show()
{
	Show();
}

void BasicGUI::setTitle(std::string title_str)
{
	SetLabel(wxString(title_str));
}

BasicGUI::~BasicGUI()
{
}
