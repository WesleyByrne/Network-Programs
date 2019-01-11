#include "CheckForAI.h"

void CheckForAI::run()
{
	Sleep(2000);
	game->checkForAITurn();
}

void CheckForAI::start()
{
	thread = new Poco::Thread();
	thread->start(*this);
}

CheckForAI::CheckForAI(EndeavorGame* game)
{
	this->game = game;
}
