#if !defined (COMPARECARDSBYLEVEL_H)
#define COMPARECARDSBYLEVEL_H

#include "Comparator.h"
#include "Card.h"

class CompareCardsByLevel : public Comparator<Card>
{ 
   private:
      bool asc;

   public:
      CompareCardsByLevel(bool asc);
      virtual ~CompareCardsByLevel();

      virtual int compare(Card* card_1, Card* card_2);
};

#endif
