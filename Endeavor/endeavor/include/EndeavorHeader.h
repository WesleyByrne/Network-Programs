#if !defined ENDEAVOR_HEADER
#define ENDEAVOR_HEADER

	#if !defined NULL
		#define NULL 0
	#endif

	#include <iostream>
	
	typedef unsigned int uint32;
	typedef unsigned char uint8;
	
	enum EndeavorActionType { OCCUPY_ACTION = 1, SHIP_ACTION = 2, DRAW_ACTION = 3, ATTACK_ACTION = 4, PAYMENT_ACTION = 5, PASS_ACTION = 6, OCCUPY_TOKEN_ACTION = 7, SHIP_TOKEN_ACTION = 8, DRAW_TOKEN_ACTION = 9, ATTACK_TOKEN_ACTION = 10, PAYMENT_TOKEN_ACTION = 11, INVALID_ACTION = 12 };
	enum EndeavorRegionType { MEDITERRANEAN = 1, AFRICA = 2, SOUTH_AMERICA = 3, CARIBBEAN = 4, NORTH_AMERICA = 5, INDIA = 6, FAR_EAST = 7, SLAVERY = 8, INVALID_REGION_TYPE = 9 }; 
	enum EndeavorTokenType { INDUSTRY = 1, CULTURE = 2, FINANCE = 3, POLITICS = 4, SHIP_DRAW = 5, OCCUPY_DRAW = 6, PAYMENT = 7, ATTACK = 8, INVALID_TOKEN_TYPE = 9 }; 
	enum EndeavorBuildingType { COLONIAL_HOUSE = 0, MARKET = 1, SHIPYARD = 2, WORKSHOP = 3, BANK = 4, BARRACKS = 5, GUILD_HALL = 6, DOCKS = 7, FORTRESS = 8, THEATRE = 9, CARTOGRAPHER = 10, TRADE_OFFICE = 11, UNIVERSITY = 12, EXCHANGE = 13, MUSEUM = 14, PARLIAMENT = 15, SHIP_OR_DRAW_TOKEN = 16, OCCUPY_OR_DRAW_TOKEN = 17, ATTACK_TOKEN = 18, PAYMENT_TOKEN = 19, INVALID_BUILDING_TYPE = 20 };
	
	#if !defined PRINT
	#define PRINT(to_print)  \
		{ \
			std::cout << to_print << std::endl; \
		}
	#endif

#endif
