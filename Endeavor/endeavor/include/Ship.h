#if !defined ENDEAVOR_SHIP
#define ENDEAVOR_SHIP

#include "wx/wx.h"
#include "tinyxml.h"

#include "EndeavorHeader.h"

#include "PixelPoint.h"
#include "PixelDimension.h"
#include "DrawImage.h"

class Ship
{
	private:
		DrawImage* ship_draw_img;
		
		EndeavorTokenType token_type;
		EndeavorRegionType region_type;
		uint8 player_id;

		bool occupied;
		PixelPoint ship_img_center;

   public:
      Ship(uint8 s_id, EndeavorTokenType t_id, wxBitmap* t_img, PixelPoint* pixel_center, PixelDimension& pixel_dim);
      //additional shipping constructor
	  Ship(uint8 s_id, PixelPoint* pixel_center, PixelDimension& pixel_dim);
	  virtual ~Ship();
	  
	  void setRegionType(EndeavorRegionType r_type){ region_type = r_type; }
	  EndeavorRegionType getRegionType(){ return region_type; }

      uint8 getShipID();
      uint8 getPlayerID();
      EndeavorTokenType getTokenID();
      bool isOccupied();
      EndeavorTokenType occupyShip(uint8 p_id, wxBitmap* p_img);

      bool isSelectedShip(uint32 x, uint32 y);
      void draw(wxDC&  dc);
	  
	  TiXmlElement* writeXML();
      void readXML(TiXmlElement* ship_element, wxBitmap** player_images, wxBitmap** token_images);
};	

#endif
