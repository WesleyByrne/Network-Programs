#if !defined ENDEAVOR_CARDS
#define ENDEAVOR_CARDS

#include "wx/wx.h"
#include "tinyxml.h"

#include "ListArray.h"
#include "StackLinked.h"
#include "PQHeap.h"

#include "PixelPoint.h"
#include "PixelDimension.h"
#include "ImageLoader.h"

#include "EndeavorHeader.h"
#include "Card.h"
#include "Token.h"

class Cards
{
	private:
		//CSC1310::StackLinked<Card>* cards;
		CSC1310::PQHeap<Card>* pq_cards;
		CSC1310::ListArray<Card>* all_cards;

		wxBitmap** card_images;
		PixelPoint card_region_loc;

	public:
		Cards(EndeavorRegionType region_type, ImageLoader* image_loader, PixelPoint& card_center, PixelDimension& card_dim, PixelDimension& card_rot_dim);
		virtual ~Cards();
		
		Card* lookAtTopCard();
		Card* takeSelectedCard(uint8 player_id);
		Card* moveGovernorCardToPlayer();
		uint8 getCardLevel();
		void returnCardToRegion(Card* card);
		
		EndeavorRegionType findSelectedCard(uint32 x, uint32 y);
		void draw(wxDC&  dc);
		
		Card* getCard(uint8 card_level);
		TiXmlElement* writeXML();
        void readXML(TiXmlElement* cards_element);
};	

#endif
