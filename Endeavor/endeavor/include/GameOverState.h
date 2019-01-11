#if !defined ENDEAVOR_GAME_OVER_STATE
#define ENDEAVOR_GAME_OVER_STATE

#include "EndeavorState.h"
class EndeavorGame;

class GameOverState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;

   public:
      GameOverState(EndeavorGame* endeavor_game, CSC1310::String* key);
      virtual ~GameOverState();

      virtual void mouseClicked(uint32 x, uint32 y);
	  virtual void aiTakeTurn(EndeavorAI* ai, uint8 ai_id);
};

#endif
