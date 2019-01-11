#if !defined ENDEAVOR_PLAYER
#define ENDEAVOR_PLAYER

#include "wx/wx.h"
#include "tinyxml.h"

#include "ListArray.h"
#include "ListLinked.h"

#include "PixelPoint.h"
#include "PixelDimension.h"
#include "DrawFont.h"

#include "Building.h"
#include "Card.h"
#include "PlayerCardManager.h"

class EndeavorGame;
class Player
{
   private:
      uint8 player_id;
      wxBitmap* player_square_img;
      wxBitmap* player_circle_img;

      uint8 workers;
      uint8 payments;

      uint8 industry;
      uint8 culture;
      uint8 finance;
      uint8 politics;

      uint8 industry_tokens;
      uint8 culture_tokens;
      uint8 finance_tokens;
      uint8 politics_tokens;
	  
	  uint8 ship_or_draw_tokens;
	  uint8 occupy_or_draw_tokens;
	  uint8 attack_tokens;
	  uint8 payment_tokens;
	 
	  bool pass;

      CSC1310::ListLinked<Building>* buildings;
	  
      bool is_selected;

      uint8 trackFunction(uint8 track_loc);
      uint8 trackGlory(uint8 track_loc);
	  
	  int num_workers_loc_x;  //location of the player circle graphic on the player board
	  int num_workers_loc_y;
	  int player_marker_width;
	  int player_marker_height;
	  
	  uint8 glory;  //glory from buildings and cards
	  uint8 total_glory;  //total glory to be displayed for each player
	  
	  DrawFont draw_info_font;
	  PlayerCardManager* player_card_manager;

   public:
      Player(uint8 p_id, wxBitmap* p_s_img, wxBitmap* p_c_img, PixelPoint& num_workers_loc, PixelDimension& marker_dim);
      virtual ~Player();
	  
	  void placeCardsOnPlayerBoard(CSC1310::ListArray<PixelPoint>* player_board_card_locs);
	  
	  void abolishSlavery(CSC1310::ListArray<PixelPoint>* player_board_card_locs);
	  uint8 computePlayerBoardGlory();
	  void computeTotalGlory(uint8 board_and_connection_glory);
	  uint8 getDefaultCardToDiscard();
	  
	  Card* discard(uint8 card_id, CSC1310::ListArray<PixelPoint>* player_board_card_locs);
	  uint8 findSelectedCardToDiscard(uint32 x, uint32 y);
	  bool mustDiscard();
	  uint8 getNumCardsOnPlayerBoard();
	  
	  void workerCost(uint8 cost);
	  void occupyCity(EndeavorTokenType token_type);
	  void takeSelectedCard(Card* card, CSC1310::ListArray<PixelPoint>* player_board_card_locs);
	  
	  void setPass(bool pass);
	  bool getPass();

	  uint8 getNumBuildings();
      void populationGrowth();
      bool canTakeBuilding(EndeavorBuildingType building_id, uint8 lowest_level_available);
      bool hasLevelFiveBuilding();
      void takeBuilding(Building* b);
      bool isPlayerSelected();
      void selectPlayer(bool select);
      bool canActivateBuilding(EndeavorBuildingType building_id);
	  
	  bool mustDiscardIfCardTaken(Card* card);

      EndeavorBuildingType findSelectedBuilding(uint32 x, uint32 y);
      void activateBuilding(EndeavorBuildingType b_id);

      wxBitmap* getPlayerImage();
      uint8 getNumWorkers();

      bool canMakePayment(EndeavorBuildingType building_id);
      void makePayment(EndeavorBuildingType building_id);
      uint8 getNumPayments();

      bool canMakePaymentAction(EndeavorBuildingType building_id);
      void makePaymentAction(EndeavorBuildingType building_id);

      bool isSelectedPlayer(uint32 x, uint32 y);
      void draw(wxDC&  dc, uint8 active_player, CSC1310::ListArray<PixelPoint>* track_locations, CSC1310::ListArray<PixelPoint>* info_locations);

      uint8 getIndustryLevel();
      uint8 getCultureLevel();
      uint8 getFinanceLevel();
      uint8 getPoliticsLevel();
	  
	  void useActionToken(EndeavorBuildingType action_type);
	  uint8 getNumActionTokens(EndeavorBuildingType action_type);

      uint8 getNumActivatedBuildings();
      void getActivatedBuildings(CSC1310::ListArray<Building>* activated_buildings);
      uint8 getNumUnactivatedBuildings();
      uint8* getUnactivatedBuildings();
	  
	  TiXmlElement* writeXML();
      void readXML(TiXmlElement* player_element, EndeavorGame* game, CSC1310::ListArray<PixelPoint>* player_board_card_locs, CSC1310::ListArray<PixelPoint>* player_building_locations);
};

#endif
