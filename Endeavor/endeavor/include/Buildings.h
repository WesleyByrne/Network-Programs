#if !defined ENDEAVOR_BUILDINGS
#define ENDEAVOR_BUILDINGS

#include "wx/wx.h"
#include "tinyxml.h"

#include "PixelXML.h"
#include "ImageLoader.h"
#include "ListArray.h"
#include "ListLinked.h"

#include "EndeavorHeader.h"
#include "Building.h"

class EndeavorGame;
class Buildings
{
	private:
		wxBitmap** building_images;
		CSC1310::ListLinked<Building>* buildings;
		CSC1310::ListArray<Building>* all_buildings;
		
		void getBuildingsAtSpecifiedLevel(uint8* available_buildings, uint8 level);

	public:
		Buildings(PixelXML& pixel_xml, ImageLoader* image_loader);
		virtual ~Buildings();

		uint8 getLowestLevelAvailable();
		EndeavorBuildingType findSelectedBuilding(uint32 x, uint32 y);
		Building* removeBuilding(EndeavorBuildingType building_id);
		void draw(wxDC&  dc);

		uint8* getAvailableBuildings(uint8 industry_level);
		
		Building* getSpecificBuilding(uint8 unique_id);
		Building* getBuilding(EndeavorBuildingType building_id);
		TiXmlElement* writeXML();
        void readXML(TiXmlElement* buildings_element);
};

#endif
