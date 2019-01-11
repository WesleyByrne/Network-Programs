#if !defined ENDEAVOR_REGION
#define ENDEAVOR_REGION

#include "wx/wx.h"
#include "tinyxml.h"

#include "ListArray.h"
#include "StackLinked.h"
#include "Permutation.h"
#include "String_.h"

#include "PixelXML.h"
#include "PixelDimension.h"
#include "PixelPoint.h"
#include "ImageLoader.h"

#include "Card.h"
#include "City.h"
#include "Token.h"
#include "ShippingLane.h"
#include "Cities.h"
#include "Cards.h"

class Region
{
	private:
		CSC1310::String start_key;
		EndeavorRegionType region_type;
	
		ShippingLane* shipping_lane;
		Cities* cities;
		Cards* cards;
		
	public:
		Region(EndeavorRegionType region_type, PixelXML& pixel_xml, ImageLoader* image_loader, CSC1310::ListArray<Token>* tokens, CSC1310::Permutation& permute, uint8 city_counter);
		virtual ~Region();
		
		void getPossibleCitiesToOccupy(CSC1310::ListArray<City>* possible_cities, uint8 player_id);
		void getNextShippingToOccupy(CSC1310::ListArray<Ship>* possible_shipping, uint8 player_id);
		void getPossibleCitiesToAttack(CSC1310::ListArray<City>* possible_cities, uint8 player_id);
		void getPossibleCardToDraw(CSC1310::ListArray<Card>* cards_to_draw, uint8 player_id);
		
		uint8 computeCityGlory(uint8 player_id);
		
		EndeavorRegionType getRegionWithCity(uint8 city_id);
		CSC1310::String* getRegionStartKey();
		//CSC1310::String* getRegionEndKey();
		EndeavorRegionType getRegionType();
		
		Card* moveGovernorCardToPlayer();
		bool canAssignGovernorCard();
		uint8 assignGovernorCard();
		EndeavorTokenType ship(uint8 player_id, wxBitmap* player_img);
		uint8 findSelectedShip(uint32 x, uint32 y);
		
		bool isCityInRegion(uint8 city_id);
		bool canAttackCity(uint8 player_id, uint8 city_id);
		bool canAttackInRegion(uint8 player_id);
		bool attackCity(uint8 player_id, wxBitmap* p_img, uint8 city_id);

		bool canOccupyInRegion(uint8 player_id);
		bool canOccupyCity(uint8 player_id, uint8 city_id);
		EndeavorTokenType occupyCity(uint8 player_id, wxBitmap* player_img, uint8 city_id);

		uint8 getPlayerPresence(uint8 player_id);
		uint8 getPlayerShippingPresence(uint8 player_id);
		uint8 getNumOpenRegularLocations();

		uint8 getPlayerIDInCity(uint8 city_id);
		uint8 findSelectedCity(uint32 x, uint32 y);

		EndeavorRegionType findSelectedCard(uint32 x, uint32 y);

		Card* takeSelectedCard(uint8 player_id);
		bool canDrawFromRegion(uint8 player_id);
		void returnCardToRegion(Card* card);

		void draw(wxDC&  dc);
		
		static int compareRegions(Region* region_1, Region* region_2);
		static int compareRegionsByKeyAndRegion(CSC1310::String* key, Region* region);
		
		Card* getCard(uint8 card_level);
		TiXmlElement* writeXML();
        void readXML(TiXmlElement* region_element, wxBitmap** player_images, wxBitmap** token_images);
};

#endif
