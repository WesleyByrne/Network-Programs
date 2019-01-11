#if !defined ENDEAVOR_DRAW_CARD_STATE
#define ENDEAVOR_DRAW_CARD_STATE

#include "EndeavorState.h"
class EndeavorGame;

class DrawCardState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;

   public:
      DrawCardState(EndeavorGame* endeavor_game, CSC1310::String* key);
      virtual ~DrawCardState();

      virtual void mouseClicked(uint32 x, uint32 y);
	  virtual void aiTakeTurn(EndeavorAI* ai, uint8 ai_id);
};

#endif
