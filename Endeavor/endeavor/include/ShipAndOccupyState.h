#if !defined ENDEAVOR_SHIP_AND_OCCUPY_STATE
#define ENDEAVOR_SHIP_AND_OCCUPY_STATE

#include "EndeavorState.h"
class EndeavorGame;

class ShipAndOccupyState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;
	  
	  EndeavorRegionType action_region;
	  bool ship;
	  bool occupy;

   public:
      ShipAndOccupyState(EndeavorGame* endeavor_game, CSC1310::String* key);
      virtual ~ShipAndOccupyState();

      virtual void mouseClicked(uint32 x, uint32 y);
	  virtual void aiTakeTurn(EndeavorAI* ai, uint8 ai_id);
};

#endif
