#if !defined SOCKET_SERVER
#define SOCKET_SERVER

//Poco includes must be first
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"

#include "String_.h"
#include "EndeavorGame.h"

class SocketServer : public Poco::Runnable
{
   private:
		Poco::Net::StreamSocket client_connections[5]; 
		Poco::Net::ServerSocket* server_socket;
		Poco::Thread* server_thread;
		
		EndeavorGame* game;
		int num_players;
		int tcp_text_length;
		char* tcp_text;
		char * file_name = (char*) "resources/server/endeavor_game.xml";
		char * zipped = (char*) "resources/server/endeavorzipped";
	
		void receiveGameState(int pid);
		void zipItSendIt();
   public:
		SocketServer(std::string ip_address, int port_num, int num_p, EndeavorGame* game);
		virtual ~SocketServer();
		void startServer();
		void run();
};

#endif
