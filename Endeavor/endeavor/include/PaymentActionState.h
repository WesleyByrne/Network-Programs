#if !defined ENDEAVOR_PAYMENT_ACTION_STATE
#define ENDEAVOR_PAYMENT_ACTION_STATE

#include "EndeavorState.h"
class EndeavorGame;

class PaymentActionState : public EndeavorState
{
   private:
      EndeavorGame* endeavor_game;

   public:
      PaymentActionState(EndeavorGame* endeavor_game, CSC1310::String* key);
      virtual ~PaymentActionState();

      virtual void mouseClicked(uint32 x, uint32 y);
	  virtual void aiTakeTurn(EndeavorAI* ai, uint8 ai_id);
};

#endif
