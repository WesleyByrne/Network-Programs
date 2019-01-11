#include "CompareCardsByLevel.h"

CompareCardsByLevel::CompareCardsByLevel(bool a)
{
   asc = a;
}

CompareCardsByLevel::~CompareCardsByLevel()
{}

int CompareCardsByLevel::compare(Card* card_1, Card* card_2)
{
   int level_1 = card_1->getCardLevel();
   int level_2 = card_2->getCardLevel();

   if (asc)
   {
      return level_1 - level_2;
   }
   else
   {
      return level_2 - level_1;
   }
}
