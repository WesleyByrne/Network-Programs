#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/NetException.h"
#include "Poco/Exception.h"

#include "wx/wx.h"
#include "wx/sizer.h"

#include "ReadFile.h"
#include "String_.h"

#include "EndeavorGame.h"
#include "SocketClient.h"

class EndeavorClientApp : public wxApp
{
	public:
		bool OnInit();
};

IMPLEMENT_APP(EndeavorClientApp)

bool EndeavorClientApp::OnInit()
{
	
	std::string ip_address = "127.0.0.1"; //default values set
	int port_num = 6789;
	
	for (int i=0; i<argc; i++) //read values from command line arguments, if available
	{
		switch(i)
		{
			case 1: ip_address = wxApp::argv[i];
			case 2: port_num = (int) atoi((char*) wxApp::argv[i].ToStdString().c_str());
		}
	}
	
	//make sure auto display scaling is disabled!
	int screen_width = wxSystemSettings::GetMetric (wxSYS_SCREEN_X);
	int screen_height = wxSystemSettings::GetMetric (wxSYS_SCREEN_Y);

	EndeavorGame* endeavor_game = new EndeavorGame(screen_width, screen_height, 5, true);
	
	//title set in client
	SocketClient* socket_client = new SocketClient(ip_address, port_num, endeavor_game);
	
    return true;
} 
