#if !defined ENDEAVOR_ACTION_STATE
#define ENDEAVOR_ACTION_STATE

#include "EndeavorState.h"
class EndeavorGame;

class ActionState : public EndeavorState
{
	private:
		EndeavorGame* endeavor_game;

	public:
		ActionState(EndeavorGame* endeavor_game, CSC1310::String* key);
		virtual ~ActionState();

		virtual void mouseClicked(uint32 x, uint32 y);
		virtual void aiTakeTurn(EndeavorAI* ai, uint8 ai_id);
};

#endif
