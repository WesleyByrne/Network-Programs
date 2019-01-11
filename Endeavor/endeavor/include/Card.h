#if !defined ENDEAVOR_CARD
#define ENDEAVOR_CARD

#include "wx/wx.h"
#include "tinyxml.h"

#include "DrawImage.h"
#include "PixelDimension.h"
#include "PixelPoint.h"

#include "EndeavorHeader.h"

class Card
{
	private:
		DrawImage* card_draw_img;  
		DrawImage* card_draw_img_rotated;  //some regions display the card rotated
	
		uint8 player_id;
		uint8 card_level;

		uint8 industry;
		uint8 culture;
		uint8 finance;
		uint8 politics;
		uint8 glory;

		bool slavery;
		bool governor;
		
		uint8 player_board_loc;
		
		EndeavorRegionType region_type;

   public:
		Card(EndeavorRegionType region_type, uint8 card_level, wxBitmap* card_img, wxBitmap* card_rot_img, PixelPoint* pixel_center, PixelDimension& pixel_dim, PixelDimension& pixel_rot_dim, uint8 industry_, uint8 culture_, uint8 finance_, uint8 politics_, uint8 glory_, bool slavery_, bool governor_);
		virtual ~Card();
		
		uint8 getPlayerBoardLoc();
		void setPlayerBoardLoc(uint8 player_board_loc);

		EndeavorRegionType getCardID();
		uint8 getCardLevel();
		uint8 getPlayerID();
	  
		void setPlayerID(uint8 player_id, PixelPoint* pixel_center);
		void setPlayerID(uint8 player_id);
	  
		bool isGovernor();
		bool isSlavery();
	  
		uint8 getIndustry();
		uint8 getCulture();
		uint8 getFinance();
		uint8 getPolitics();
		uint8 getGlory();

		bool isSelectedCard(uint32 x, uint32 y);
		void draw(wxDC&  dc);
	  
		static int compareCardsByLevelAsc(Card* one, Card* two);
		static int compareCardsByLevelDesc(Card* one, Card* two);
		
		TiXmlElement* writeXML();
        void readXML(TiXmlElement* card_element, PixelPoint& card_region_loc);
		void readXML(TiXmlElement* card_element);
};

#endif
