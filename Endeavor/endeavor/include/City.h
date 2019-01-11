#if !defined ENDEAVOR_CITY
#define ENDEAVOR_CITY

#include "wx/wx.h"
#include "tinyxml.h"

#include "DrawImage.h"

#include "EndeavorHeader.h"

class City
{
	private:
		DrawImage* city_draw_img;
   
		EndeavorTokenType token_type;
		uint8 player_id;

		bool occupied;

	public:
		City(uint8 city_id, EndeavorTokenType token_type, wxBitmap* token_img, PixelPoint* pixel_center, PixelDimension& pixel_dim);
		virtual ~City();

		uint8 getCityID();
		uint8 getPlayerID();
		uint8 getTokenID();
		bool isOccupied();
		EndeavorTokenType occupyCity(uint8 p_id, wxBitmap* p_img);
		bool isSelectedCity(uint32 x, uint32 y);

		void draw(wxDC&  dc);
		
		TiXmlElement* writeXML();
        void readXML(TiXmlElement* city_element, wxBitmap** player_images, wxBitmap** token_images);
};

#endif
