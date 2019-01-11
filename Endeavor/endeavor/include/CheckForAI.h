//Poco includes must be first
#include "Poco/Runnable.h"
#include "Poco/Thread.h"

#include "EndeavorGame.h"

class CheckForAI : public Poco::Runnable
{
   private:
		Poco::Thread* thread;
		EndeavorGame* game;
	
   public:
		CheckForAI(EndeavorGame* game);
		void run();
		void start();
};