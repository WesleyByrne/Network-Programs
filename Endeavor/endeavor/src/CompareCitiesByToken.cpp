#include "CompareCitiesByToken.h"
#include "EndeavorGame.h"

CompareCitiesByToken::CompareCitiesByToken(EndeavorGame* game, uint8 p_id, EndeavorTokenType* order)
{
   sort_order = order;
   endeavor_game = game;
   player_id = p_id;
}

CompareCitiesByToken::~CompareCitiesByToken()
{}

int CompareCitiesByToken::findRankFromTokenID(EndeavorTokenType token_id)
{
   for (int i = 0; i < 8; i++)
   {
      if (sort_order[i] == token_id)
      {
         return i + 1;
      }
   }

   return 9;  //should not make it here
}

int CompareCitiesByToken::countPlayerConnections(uint8 player_id, uint8 test_city_id, CSC1310::ListArray<Connection>* connections)
{
	int city_conn_count = 0;
	CSC1310::ListArrayIterator<Connection>* conn_count_iter = connections->iterator();
	while(conn_count_iter->hasNext())
	{
		Connection* conn = conn_count_iter->next();
		uint8 city_1_temp = conn->getCity1ID();
		uint8 city_2_temp = conn->getCity2ID();
		
		uint8 city_player_id = 0;
		if (city_1_temp == test_city_id) //does player already occupy city_2_temp?
		{
			city_player_id = endeavor_game->getPlayerIDInCity(city_2_temp);
		}
		else if (city_2_temp == test_city_id)  //does player already occupy city_1_temp?
		{
			city_player_id = endeavor_game->getPlayerIDInCity(city_1_temp);
		}
		
		//the player already occupies the other city in the connection!
		if (city_player_id == player_id)
		{
			city_conn_count++;
		}
	}
	delete conn_count_iter;
	
	return city_conn_count;
}

int CompareCitiesByToken::compare(City* city_1, City* city_2)
{
	//uint8 player_id = endeavor_game->getActivePlayer();
	
	uint8 city_1_id = city_1->getCityID();
	uint8 city_2_id = city_2->getCityID();
	
	CSC1310::ListArray<Connection>* city_1_conns = endeavor_game->getAllConnectionsContainingCityID(city_1_id);
	CSC1310::ListArray<Connection>* city_2_conns = endeavor_game->getAllConnectionsContainingCityID(city_2_id);
	
	int city_1_conn_count = countPlayerConnections(player_id, city_1_id, city_1_conns);
	int city_2_conn_count = countPlayerConnections(player_id, city_2_id, city_2_conns);
	
	delete city_1_conns;
	delete city_2_conns;
	
	//std::cout << "city1: " << (int) city_1_conn_count << std::endl;
	//std::cout << "city2: " << (int) city_2_conn_count << std::endl;
	if (city_1_conn_count != city_2_conn_count)
	{
		return city_2_conn_count - city_1_conn_count; //desc
	}

   EndeavorTokenType city_1_token = (EndeavorTokenType) city_1->getTokenID();
   EndeavorTokenType city_2_token = (EndeavorTokenType) city_2->getTokenID();

   int city_1_rank = findRankFromTokenID(city_1_token);
   int city_2_rank = findRankFromTokenID(city_2_token);

   return city_1_rank - city_2_rank;
}
