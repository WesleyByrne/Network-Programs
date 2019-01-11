#if !defined ENDEAVOR_GAME
#define ENDEAVOR_GAME

#include "wx/wx.h"
#include "tinyxml.h"

#include "Drawable.h"
#include "BasicGUI.h"
#include "ListArray.h"
#include "QueueArray.h"
#include "HashTableAVL.h"

#include "EndeavorHeader.h"

#include "Token.h"
#include "Connections.h"
#include "Buildings.h"
#include "Players.h"
#include "Board.h"

#include "EndeavorState.h"
#include "EndeavorAI.h"

//basic states
#include "BuildState.h"
#include "PaymentState.h"
#include "ActionState.h"
#include "DiscardState.h"

//various possible action states
#include "OccupyState.h"
#include "ShipState.h"
#include "AttackState.h"
#include "DrawCardState.h"
#include "ShipOrDrawState.h"
#include "OccupyOrDrawState.h"
#include "OccupyOrAttackState.h"
#include "ShipAndOccupyState.h"
#include "ShipAndShipState.h"
#include "DrawAndDrawState.h"
#include "PaymentActionState.h"

#include "GameOverState.h"

class EndeavorGame : public Drawable
{
   private:
		BasicGUI* endeavor_gui;
		wxBitmap** token_images;
		EndeavorAI** endeavor_ais;
		
		uint8 num_players;
		uint8 num_ais;
		bool networked;
		
		Connections* connections;
		Buildings* buildings;
		Players* players;
		Board* board;
		
		CSC1310::HashTableAVL<EndeavorState>* endeavor_state_hash_table;
		
		EndeavorState* current_state;
		
		BuildState* build_state;
		PaymentState* payment_state;
		ActionState* action_state;
		DiscardState* discard_state;
		GameOverState* game_over_state;
		
		//place these states in a hash table
		OccupyState* occupy_state;
		ShipState* ship_state;
		AttackState* attack_state;
		DrawCardState* draw_card_state;
		ShipOrDrawState* ship_or_draw_state;
		OccupyOrDrawState* occupy_or_draw_state;
		OccupyOrAttackState* occupy_or_attack_state;
		ShipAndOccupyState* ship_and_occupy_state;
		ShipAndShipState* ship_and_ship_state;
		DrawAndDrawState* draw_and_draw_state;
		PaymentActionState* payment_action_state;
		
		CSC1310::QueueArray<EndeavorState>* state_queue;
		void processOccupyAttackTokens(uint8 player_id, uint8 city_id, CSC1310::ListArray<CSC1310::Integer>* tokens);
		
   public:
   
		virtual CSC1310::String getGameState();
		virtual void setGameState(CSC1310::String& xml_str);
		
		virtual int getPlayerID();
		virtual void repaint();
	    virtual bool isGameOver();
		virtual void disableGame();
		
		virtual void checkForAITurn();
		
		void showGUI();
		void setTitle(std::string title_str);
			
		EndeavorGame(int screen_width, int screen_height, uint8 num_players, bool networked);
		virtual ~EndeavorGame();

		virtual void draw(wxDC&  dc, int width, int height);
		virtual void mouseClicked(int x, int y);
		virtual void keyPressed(int key_code);
		
		CSC1310::ListArray<Connection>* getAllConnectionsContainingCityID(uint8 city_id);
		uint8 getPlayerIDInCity(uint8 city_id);
		
		void computeTotalGlory(uint8 player_id);
		
		bool canOccupyInRegion(uint8 player_id, EndeavorRegionType region_type);
		EndeavorRegionType getRegionWithCity(uint8 city_id);
		
		uint8 getNumCardsOnPlayerBoard(uint8 player_id);
		void discard(uint8 player_id, uint8 card_id);
		bool mustDiscard(uint8 player_id);
		uint8 findSelectedCardToDiscard(uint8 player_id, uint32 x, uint32 y);
		uint8 getDefaultCardToDiscard(uint8 player_id);
		
		void changeToState(const char* key);
		
		void changeToActionState();
		void changeToDiscardState();
		void changeToGameOverState();
		
		//methods for board (regions)
		void getPossibleCitiesToOccupy(CSC1310::ListArray<City>* possible_cities, uint8 player_id);
		void getNextShippingToOccupy(CSC1310::ListArray<Ship>* possible_shipping, uint8 player_id);
		void getPossibleCitiesToAttack(CSC1310::ListArray<City>* possible_cities, uint8 player_id);
		void getPossibleCardsToDraw(CSC1310::ListArray<Card>* cards_to_draw, uint8 player_id);
		
		void moveGovernorCardToPlayer(uint8 player_id, EndeavorRegionType region_type);
		bool canAssignGovernorCard(EndeavorRegionType region_type);
	    uint8 assignGovernorCard(EndeavorRegionType region_type);
		void ship(uint8 player_id, EndeavorRegionType region_type);
		EndeavorRegionType findSelectedShip(uint32 x, uint32 y);
		bool canShipInAnyRegion(uint8 player_id);
		bool canAttackInAnyRegion(uint8 player_id);
		bool canAttackCity(uint8 player_id, uint8 city_id);
		bool canOccupyCity(uint8 player_id, uint8 city_id);
		bool canOccupyInAnyRegion(uint8 player_id);
		void attackCity(uint8 player_id, uint8 city_id);
		void occupyCity(uint8 player_id, uint8 city_id);
		
		bool canDrawFromAnyRegion(uint8 player_id);
		void takeSelectedCard(uint8 player_id, EndeavorRegionType card_id);
		bool canTakeSelectedCard(uint8 player_id, EndeavorRegionType card_id);
		EndeavorRegionType findSelectedCard(uint32 x, uint32 y);
		uint8 findSelectedCity(uint32 x, uint32 y);
		
		uint8 getActivePlayerShippingPresence(EndeavorRegionType region_type);
		uint8 getNumOpenRegularLocations(EndeavorRegionType region_type);
		
		//methods for players
		void useActionToken(uint8 player_id, EndeavorBuildingType action_type);
		uint8 getNumActionTokens(uint8 player_id, EndeavorBuildingType action_type);
	  
		bool mustDiscardIfCardTaken(Card* card, uint8 player_id);
		
		void occupyCity(uint8 player_id, CSC1310::ListArray<CSC1310::Integer>* tokens, uint8 worker_cost);
		
		bool canMakePaymentAction(uint8 player_id, EndeavorBuildingType building_type);
		bool canTakePaymentAction(uint8 player_id);
		bool canMakeAnyPayments(uint8 player_id);
		uint8 getNumPayments(uint8 player_id);
		uint8 getNumActivatedBuildings(uint8 player_id);
		uint8 getNumUnactivatedBuildings(uint8 player_id);
		void makePayment(uint8 player_id, EndeavorBuildingType building_type);
		bool canMakePayment(uint8 player_id, EndeavorBuildingType building_type);
		void activateBuilding(uint8 player_id, EndeavorBuildingType building_type);
		bool canActivateBuilding(uint8 player_id, EndeavorBuildingType building_type);
		EndeavorBuildingType findSelectedBuildingPlayerBoard(uint8 player_id, uint32 x, uint32 y);
		uint8 getNumWorkers(uint8 player_id);
		void populationGrowth(uint8 player_id);
		bool doesPlayerPass(uint32 x, uint32 y);
		uint8 getActivePlayer();
		bool canTakeBuilding(uint8 active_player, EndeavorBuildingType building_type, uint8 lowest_level_available);
		void takeBuilding(uint8 active_player, Building* selected_building);
		void nextPlayer();
		void nextPlayerAfterPass();
		
		int getIndustryLevel(uint8 player_id);
		int getCultureLevel(uint8 player_id);
		int getFinanceLevel(uint8 player_id);
		int getPoliticsLevel(uint8 player_id);
		
		bool hasLevelFiveBuilding(uint8 player_id);
		void getActivatedBuildings(CSC1310::ListArray<Building>* activated_buildings, uint8 player_id);
		uint8* getUnactivatedBuildings(uint8 player_id);
		
		//methods for buildings
		uint8 getLowestLevelAvailable();
		EndeavorBuildingType findSelectedBuilding(uint32 x, uint32 y);
		Building* removeBuilding(EndeavorBuildingType building_type);
		
		uint8* getAvailableBuildings(uint8 industry_level);
		
		void saveGame();
		void loadGame();
		
		static int integerFromXMLElement(TiXmlElement* integer_element);
		static TiXmlElement* xmlElementFromInteger(const char* element_tag, int integer_to_insert);
		
		Building* getSpecificBuilding(uint8 unique_building_id);
		Card* getCard(EndeavorRegionType card_region_type, uint8 card_level);
		TiXmlElement* writeXML();
        void readXML(TiXmlElement* game_element);
};

#endif 
