#if !defined ENDEAVOR_PAYMENT_STATE
#define ENDEAVOR_PAYMENT_STATE

#include "EndeavorState.h"
class EndeavorGame;

class PaymentState : public EndeavorState
{
	private:
		EndeavorGame* endeavor_game;

	public:
		PaymentState(EndeavorGame* endeavor_game, CSC1310::String* key);
		virtual ~PaymentState();

		virtual void mouseClicked(uint32 x, uint32 y);
		virtual void aiTakeTurn(EndeavorAI* ai, uint8 ai_id);
};

#endif
