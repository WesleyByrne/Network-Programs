#if !defined ENDEAVOR_SHIP_STATE
#define ENDEAVOR_SHIP_STATE

#include "EndeavorState.h"
class EndeavorGame;

class ShipState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;

   public:
      ShipState(EndeavorGame* endeavor_game, CSC1310::String* key);
      virtual ~ShipState();

      virtual void mouseClicked(uint32 x, uint32 y);
	  virtual void aiTakeTurn(EndeavorAI* ai, uint8 ai_id);
};

#endif
