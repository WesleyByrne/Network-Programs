#if !defined ENDEAVOR_SHIPPING_LANE
#define ENDEAVOR_SHIPPING_LANE

#include "wx/wx.h"
#include "tinyxml.h"

#include "ListDoublyLinked.h"
#include "ListArray.h"
#include "Permutation.h"

#include "PixelPoint.h"
#include "PixelDimension.h"

#include "EndeavorHeader.h"
#include "Ship.h"
#include "Token.h"

class ShippingLane
{
	private:
		CSC1310::ListDoublyLinked<Ship>* shipping_lane;
		uint8 ship_cursor;
		uint8 num_regular_shipping_locations;
		
	public:
		ShippingLane(EndeavorRegionType region_type, CSC1310::ListArray<Token>* tokens, CSC1310::Permutation& permute, CSC1310::ListArray<PixelPoint>* pixel_centers, PixelDimension& pixel_dim);
		virtual ~ShippingLane();
		
		void getNextShippingToOccupy(CSC1310::ListArray<Ship>* possible_shipping, uint8 player_id);
		
		bool isRegionOpen();
		uint8 getPlayerPresence(uint8 player_id);
		uint8 getNumOpenRegularLocations();
		uint8 assignGovernorCard();
		bool canAssignGovernorCard();

		EndeavorTokenType ship(uint8 player_id, wxBitmap* player_img);
		
		uint8 findSelectedShip(uint32 x, uint32 y);
		void draw(wxDC&  dc);
		
		TiXmlElement* writeXML();
        void readXML(TiXmlElement* ship_element, wxBitmap** player_images, wxBitmap** token_images);
};	

#endif
