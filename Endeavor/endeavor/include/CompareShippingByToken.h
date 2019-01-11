#if !defined (COMPARESHIPPINGBYTOKEN_H)
#define COMPARESHIPPINGBYTOKEN_H

#include "Ship.h"
#include "Comparator.h"
class EndeavorGame;

class CompareShippingByToken : public Comparator<Ship>
{ 
   private:
      EndeavorTokenType* sort_order;
	  EndeavorGame* endeavor_game;

      int findRankFromTokenID(EndeavorTokenType token_id);

   public:
      CompareShippingByToken(EndeavorGame* game, EndeavorTokenType* sort_order);
      virtual ~CompareShippingByToken();

      virtual int compare(Ship* ship_1, Ship* ship_2);
};

#endif
