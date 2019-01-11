#if !defined ENDEAVOR_BUILD_STATE
#define ENDEAVOR_BUILD_STATE

#include "EndeavorState.h"
class EndeavorGame;

class BuildState : public EndeavorState
{
	private:
		EndeavorGame* endeavor_game;

	public:
		BuildState(EndeavorGame* endeavor_game, CSC1310::String* key);
		virtual ~BuildState();

		virtual void mouseClicked(uint32 x, uint32 y);
		virtual void aiTakeTurn(EndeavorAI* ai, uint8 ai_id);
};

#endif
