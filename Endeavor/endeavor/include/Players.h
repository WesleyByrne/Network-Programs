#if !defined ENDEAVOR_PLAYERS
#define ENDEAVOR_PLAYERS

#include "wx/wx.h"
#include "tinyxml.h"

#include "ListArray.h"
#include "Integer.h"

#include "ImageLoader.h"
#include "PixelXML.h"
#include "PixelPoint.h"
#include "PixelDimension.h"
#include "HotSpot.h"

#include "Player.h"
#include "Building.h"
#include "Buildings.h"

class Players
{
   private:
      CSC1310::ListArray<Player>* players;
	  CSC1310::ListArray<PixelPoint>* player_building_locations;
	  CSC1310::ListArray<PixelPoint>* player_track_locations;
	  CSC1310::ListArray<PixelPoint>* player_info_locations;
	  CSC1310::ListArray<PixelPoint>* player_card_locations;
	  
	  CSC1310::ListArray<HotSpot>* player_view_hot_spots;
	  CSC1310::ListArray<HotSpot>* action_token_hot_spots;
	  
	  HotSpot* player_pass_hot_spot;
	  
      uint8 active_player;
      uint8 start_player;  //rotates clockwise at the start of a new turn
	  uint8 view_player;
	  uint8 player_pass_count;
	  
	  uint8 game_round;

      wxBitmap* start_player_img;
      wxBitmap* active_player_img;
	  
	  wxBitmap** player_square_images;
	  wxBitmap** player_circle_images;

   public:
      Players(PixelXML& pixel_xml, ImageLoader* image_loader, Buildings* buildings);
      virtual ~Players();
	  
	  wxBitmap** getPlayerCircleImages() { return player_circle_images; }
	  
	  void placeCardsOnPlayerBoard();
	  void abolishSlavery();
	  
	  Card* discard(uint8 player_id, uint8 card_id);
	  uint8 findSelectedCardToDiscard(uint8 player_id, uint32 x, uint32 y);
	  bool mustDiscard(uint8 player_id);
	  bool mustDiscardIfCardTaken(Card* card, uint8 player_id);
	  uint8 getNumCardsOnPlayerBoard(uint8 player_id);
	  uint8 getDefaultCardToDiscard(uint8 player_id);
	  
	  void ship(uint8 player_id, EndeavorTokenType token_type);
	  void takeSelectedCard(uint8 player_id, Card* card);
	  void occupyCity(uint8 player_id, CSC1310::ListArray<CSC1310::Integer>* token_types, uint8 worker_cost);
	  
	  void populationGrowth(uint8 active_player);
	  void nextPlayer();  //skips players that have passed
	  bool nextPlayerAfterPass();  //mark the player as having passed
	  bool nextPlayerAfterPassCheckForNewRound();  //might go back to build phase
	  bool doesPlayerPass(uint32 x, uint32 y);

	  uint8 findSelectedPlayer(uint32 x, uint32 y);
	  void selectPlayer(uint8 player_id);
	  uint8 getViewPlayer();
	  
      uint8 getActivePlayer();
      uint8 getStartPlayer();
	  uint8 getGameRound();

      void takeBuilding(uint8 player_id, Building* b);
      bool canTakeBuilding(uint8 player_id, EndeavorBuildingType building_id, uint8 lowest_level_available);
      bool hasLevelFiveBuilding(uint8 player_id);
      uint8 getNumWorkers(uint8 player_id);

      wxBitmap* getPlayerImage(uint8 player_id);
	  
	  void useActionToken(uint8 player_id, EndeavorBuildingType action_type);
	  uint8 getNumActionTokens(uint8 player_id, EndeavorBuildingType action_type);

	  EndeavorBuildingType findSelectedActionToken(uint8 player_id, uint32 x, uint32 y);
      EndeavorBuildingType findSelectedBuilding(uint8 player_id, uint32 x, uint32 y);
      void activateBuilding(uint8 player_id, EndeavorBuildingType building_id);
      bool canActivateBuilding(uint8 player_id, EndeavorBuildingType building_id);

      bool canMakePayment(uint8 player_id, EndeavorBuildingType building_id);
      void makePayment(uint8 player_id, EndeavorBuildingType building_id);
      uint8 getNumPayments(uint8 player_id);

      bool canMakePaymentAction(uint8 player_id, EndeavorBuildingType building_id);
      void makePaymentAction(uint8 player_id, EndeavorBuildingType building_id);

      void draw(wxDC&  dc);

      uint8 getIndustryLevel(uint8 player_id);
      uint8 getCultureLevel(uint8 player_id);
      uint8 getFinanceLevel(uint8 player_id);
      uint8 getPoliticsLevel(uint8 player_id);

      uint8 getNumActivatedBuildings(uint8 player_id);
      void getActivatedBuildings(CSC1310::ListArray<Building>* activated_buildings, uint8 player_id);
      uint8 getNumUnactivatedBuildings(uint8 player_id);
      uint8* getUnactivatedBuildings(uint8 player_id);
	  
	  void computeTotalGlory(uint8 player_id, uint8 board_and_connection_glory);
	  
	  TiXmlElement* writeXML();
      void readXML(TiXmlElement* players_element, EndeavorGame* game);
	
};

#endif
