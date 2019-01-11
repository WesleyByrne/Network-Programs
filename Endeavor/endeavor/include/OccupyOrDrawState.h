#if !defined ENDEAVOR_OCCUPY_OR_DRAW_STATE
#define ENDEAVOR_OCCUPY_OR_DRAW_STATE

#include "EndeavorState.h"
class EndeavorGame;

class OccupyOrDrawState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;

   public:
      OccupyOrDrawState(EndeavorGame* endeavor_game, CSC1310::String* key);
      virtual ~OccupyOrDrawState();

      virtual void mouseClicked(uint32 x, uint32 y);
	  virtual void aiTakeTurn(EndeavorAI* ai, uint8 ai_id);
};

#endif
