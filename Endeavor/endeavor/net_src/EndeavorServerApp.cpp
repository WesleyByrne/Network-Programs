#include "wx/wx.h"
#include "wx/sizer.h"

#include "ReadFile.h"
#include "String_.h"
#include "Zip.h"

#include "EndeavorGame.h"
#include "SocketServer.h"

class EndeavorServerApp : public wxApp
{
	public:
		bool OnInit();
		void beep();
	private:
		
};


IMPLEMENT_APP(EndeavorServerApp)

void EndeavorServerApp::beep(){std::cout<<"beep"<<endl;}

bool EndeavorServerApp::OnInit()
{
	std::string ip_address = "127.0.0.1"; //default values set
	int port_num = 6789;
	int num_players = 1;
	int new_game = 0;
	
	for (int i=0; i<argc; i++) //read values from command line arguments, if available
	{
		switch(i)
		{
			case 1: ip_address = wxApp::argv[i]; break;
			case 2: port_num = (int) atoi((char*) wxApp::argv[i].ToStdString().c_str()); break;
			case 3: num_players = (uint8) atoi((char*) wxApp::argv[i].ToStdString().c_str()); break;
			case 4: new_game = (uint8) atoi((char*) wxApp::argv[i].ToStdString().c_str()); break;
		}
		
	}
	
	if (num_players > 5 || num_players < 1) {
		std::cout << "err: invalid # of players" << std::endl;
		return false;
	}
	
	EndeavorGame* endeavor_game = new EndeavorGame(wxSystemSettings::GetMetric (wxSYS_SCREEN_X), wxSystemSettings::GetMetric (wxSYS_SCREEN_Y), num_players, true);
	
	SocketServer* socket_server = new SocketServer(ip_address, port_num, num_players, endeavor_game);
	socket_server->startServer();
	
    return true;
} 
