#if !defined ENDEAVOR_AI
#define ENDEAVOR_AI

#include "EndeavorHeader.h"

class EndeavorAI
{
   private:

   public:
      EndeavorAI();
      virtual ~EndeavorAI();

      virtual uint8 selectBuilding(uint8 player_id) = 0;  //returns the building_id of the desired building
      virtual uint8* makePayments(uint8& num_payments, uint8 player_id) = 0; //returns the building_ids of the buildings to be cleared by payments
      virtual uint8* selectAction(uint8 player_id) = 0; //returns the id of the desired action (a building or an action token is used, or pass is selected)
 
      //virtual uint8 discard(uint8 player_id) = 0; //returns the id of the card to discard
};

#endif
