#if !defined COMPARE_CITIES_BY_TOKEN
#define COMPARE_CITIES_BY_TOKEN

#include "City.h"
#include "Comparator.h"
#include "Connection.h"
#include "ListArray.h"

class EndeavorGame;

class CompareCitiesByToken : public Comparator<City>
{ 
   private:
      EndeavorTokenType* sort_order;
	  EndeavorGame* endeavor_game;
	  uint8 player_id;

      int findRankFromTokenID(EndeavorTokenType token_id);
	  int countPlayerConnections(uint8 player_id, uint8 test_city_id, CSC1310::ListArray<Connection>* connections);

   public:
      CompareCitiesByToken(EndeavorGame* game, uint8 player_id, EndeavorTokenType* sort_order);
      virtual ~CompareCitiesByToken();

      virtual int compare(City* city_1, City* city_2);
};

#endif
