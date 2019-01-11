#if !defined ENDEAVOR_ATTACK_STATE
#define ENDEAVOR_ATTACK_STATE

#include "EndeavorState.h"
class EndeavorGame;

class AttackState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;

   public:
      AttackState(EndeavorGame* endeavor_game, CSC1310::String* key);
      virtual ~AttackState();

      virtual void mouseClicked(uint32 x, uint32 y);
	  virtual void aiTakeTurn(EndeavorAI* ai, uint8 ai_id);
};

#endif
