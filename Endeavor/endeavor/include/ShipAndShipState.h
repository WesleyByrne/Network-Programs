#if !defined ENDEAVOR_SHIP_AND_SHIP_STATE
#define ENDEAVOR_SHIP_AND_SHIP_STATE

#include "EndeavorState.h"
class EndeavorGame;

class ShipAndShipState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;
	  
	  EndeavorRegionType action_region;
	  bool first_ship;
	  bool second_ship;

   public:
      ShipAndShipState(EndeavorGame* endeavor_game, CSC1310::String* key);
      virtual ~ShipAndShipState();

      virtual void mouseClicked(uint32 x, uint32 y);
	  virtual void aiTakeTurn(EndeavorAI* ai, uint8 ai_id);
};

#endif
