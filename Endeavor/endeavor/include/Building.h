#if !defined ENDEAVOR_BUILDING
#define ENDEAVOR_BUILDING

#include "wx/wx.h"
#include "tinyxml.h"

#include "DrawImage.h"

#include "EndeavorHeader.h"

class EndeavorGame;
class Building
{
	private:
		DrawImage* building_draw_img;
		DrawImage* activated_draw_img;

		bool can_activate;
		bool is_activated;

		uint8 industry;
		uint8 finance;
		uint8 culture;
		uint8 politics;
		uint8 glory;
	  
		uint8 player_id;
		uint8 unique_id;
 
	public:
		Building(uint8 b_id, uint8 unique_id, wxBitmap* building_img, PixelPoint* pixel_center, PixelDimension& pixel_dim, PixelDimension& worker_dim, bool activate, uint8 industry_, uint8 culture_, uint8 finance_, uint8 politics_, uint8 glory_);
		virtual ~Building();
	  
		void draw(wxDC&  dc);

		//to determine whether a building was selected from the general stock to move to a player board
		bool isSelectedBuilding(uint32 x, uint32 y);
		//to determine whether a building was selected on the player board to activate the building
		bool isSelectedActionCircle(uint32 x, uint32 y); 

		EndeavorBuildingType getBuildingID();
		uint8 getUniqueID();
		void setPlayerImage(uint8 player_id, wxBitmap* player_img);
		void activate();
		bool canActivate();
		bool isActivated();
		void makePayment();
	  
		void setBuildingLocation(PixelPoint& pixel_point);

		uint8 getIndustry();
		uint8 getFinance();
		uint8 getCulture();
		uint8 getPolitics();
		uint8 getGlory();
		
		TiXmlElement* writeXML();
        void readXML(TiXmlElement* building_element);
};

#endif
