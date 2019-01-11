#if !defined ENDEAVOR_CITIES
#define ENDEAVOR_CITIES

#include "wx/wx.h"
#include "tinyxml.h"

#include "ListArray.h"
#include "Permutation.h"

#include "PixelPoint.h"
#include "PixelDimension.h"

#include "EndeavorHeader.h"
#include "City.h"
#include "Token.h"

class Cities
{
	private:
		uint8 first_city_id;
		uint8 num_cities_in_region;
		
		CSC1310::ListArray<City>* cities;

	public:
		Cities(CSC1310::ListArray<Token>* tokens, CSC1310::Permutation& permute, CSC1310::ListArray<PixelPoint>* pixel_centers, PixelDimension& pixel_dim, uint8 city_counter);
		virtual ~Cities();
		
		void getPossibleCitiesToOccupy(CSC1310::ListArray<City>* possible_cities, uint8 player_id);
		void getPossibleCitiesToAttack(CSC1310::ListArray<City>* possible_cities, uint8 player_id);
		
		uint8 computeCityGlory(uint8 player_id);
		
		uint8 getPlayerPresence(uint8 player_id);
		bool isCityInRegion(uint8 city_id);
		uint8 getPlayerIDInCity(uint8 city_id);
		
		bool canOccupyInRegion();
		bool canOccupyCity(uint8 city_id);

		EndeavorTokenType occupyCity(uint8 player_id, wxBitmap* player_img, uint8 city_id);
		
		bool canAttackCity(uint8 player_id, uint8 city_id);
		bool canAttackInRegion(uint8 player_id);
		bool attackCity(uint8 player_id, wxBitmap* p_img, uint8 city_id);
		
		uint8 findSelectedCity(uint32 x, uint32 y);
		void draw(wxDC&  dc);
		
		TiXmlElement* writeXML();
        void readXML(TiXmlElement* city_element, wxBitmap** player_images, wxBitmap** token_images);
};	

#endif
