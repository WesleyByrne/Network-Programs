#if !defined SOCKET_CLIENT
#define SOCKET_CLIENT

//Poco includes must be first
#include "Poco/Net/StreamSocket.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"

#include "String_.h"
#include "EndeavorGame.h"

class SocketClient : public Poco::Runnable
{
   private:
		Poco::Net::StreamSocket* connection; 
		Poco::Thread* client_thread;
		int player_ID;
		char* file_name;
		char* zipped;
		EndeavorGame* game;
		
		void receiveGameState();
		void zipItSendIt();
		
   public:
		SocketClient(std::string ip_address, int port_num, EndeavorGame* game);
		virtual ~SocketClient();
		void run();
		
};

#endif
