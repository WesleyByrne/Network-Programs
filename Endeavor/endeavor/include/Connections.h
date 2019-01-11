#if !defined ENDEAVOR_CONNECTIONS
#define ENDEAVOR_CONNECTIONS

#include "wx/wx.h"
#include "tinyxml.h"

#include "PixelXML.h"
#include "Permutation.h"
#include "ListArray.h"
#include "BinarySearchTree.h"

#include "EndeavorHeader.h"
#include "Connection.h"
#include "Token.h"

class EndeavorGame;
class Connections
{
	private:
		//CSC1310::ListArray<Connection>* connections;
		CSC1310::BinarySearchTree<Connection>* connections_by_first_city;
		CSC1310::BinarySearchTree<Connection>* connections_by_second_city;
		
	public:
		Connections(PixelXML& pixel_xml, CSC1310::Permutation& permute, CSC1310::ListArray<Token>* tokens);
		virtual ~Connections();
		
		CSC1310::ListArray<Connection>* getAllConnectionsContainingCityID(uint8 city_id);
		uint8 computeConnectionsGlory(uint8 player_id);
		
		void draw(wxDC&  dc);
		
		TiXmlElement* writeXML();
        void readXML(TiXmlElement* connections_element, wxBitmap** player_images, wxBitmap** token_images);
};

#endif
