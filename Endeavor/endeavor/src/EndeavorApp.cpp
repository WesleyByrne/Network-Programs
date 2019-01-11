#include "wx/wx.h"
#include "wx/sizer.h"

#include "ReadFile.h"
#include "String_.h"

#include "EndeavorGame.h"

class EndeavorApp : public wxApp
{
	public:
		bool OnInit();
};

IMPLEMENT_APP(EndeavorApp)

bool EndeavorApp::OnInit()
{
	uint8 num_players = 1;
	
	if (wxApp::argc >= 2)
	{
		char* num_players_c_str = (char*) wxApp::argv[1].ToStdString().c_str();
		
		uint8 n_p = (uint8) atoi(num_players_c_str);
		if (n_p >= 0 && n_p <= 5)
		{
			num_players = n_p;
		}
	}
	
	//make sure auto display scaling is disabled!
	int screen_width = wxSystemSettings::GetMetric (wxSYS_SCREEN_X);
	int screen_height = wxSystemSettings::GetMetric (wxSYS_SCREEN_Y);

	EndeavorGame* endeavor_game = new EndeavorGame(screen_width, screen_height, num_players, false);
	
	CSC1310::String title_str("Endeavor");
	std::string title_std_str(title_str.get_std_str());
	endeavor_game->setTitle(title_std_str);
	endeavor_game->showGUI();
	
    return true;
} 
