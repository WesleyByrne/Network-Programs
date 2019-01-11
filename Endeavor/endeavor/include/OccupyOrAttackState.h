#if !defined ENDEAVOR_OCCUPY_OR_ATTACK_STATE
#define ENDEAVOR_OCCUPY_OR_ATTACK_STATE

#include "EndeavorState.h"
class EndeavorGame;

class OccupyOrAttackState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;

   public:
      OccupyOrAttackState(EndeavorGame* endeavor_game, CSC1310::String* key);
      virtual ~OccupyOrAttackState();

      virtual void mouseClicked(uint32 x, uint32 y);
	  virtual void aiTakeTurn(EndeavorAI* ai, uint8 ai_id);
};

#endif
