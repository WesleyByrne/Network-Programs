#include "GameOverState.h"
#include "EndeavorGame.h"

void GameOverState::aiTakeTurn(EndeavorAI* ai, uint8 ai_id)
{
}

GameOverState::GameOverState(EndeavorGame* game, CSC1310::String* key) : EndeavorState(key)
{
	endeavor_game = game;
}

GameOverState::~GameOverState()
{}

void GameOverState::mouseClicked(uint32 x, uint32 y)
{

}
