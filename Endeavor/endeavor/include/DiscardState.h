#if !defined ENDEAVOR_DISCARD_STATE
#define ENDEAVOR_DISCARD_STATE

#include "EndeavorState.h"
class EndeavorGame;

class DiscardState : public EndeavorState
{
	private:
		EndeavorGame* endeavor_game;

	public:
		DiscardState(EndeavorGame* endeavor_game, CSC1310::String* key);
		virtual ~DiscardState();

		virtual void mouseClicked(uint32 x, uint32 y);
		virtual void aiTakeTurn(EndeavorAI* ai, uint8 ai_id);
};

#endif
