#if !defined ENDEAVOR_CONNECTION
#define ENDEAVOR_CONNECTION

#include "wx/wx.h"
#include "tinyxml.h"

#include "String_.h"
using CSC1310::String;

#include "DrawImage.h"

#include "EndeavorHeader.h"

class Connection
{
	private:
		DrawImage* connection_draw_img;
		
		String connection_key_1;
		String connection_key_2;
   
		uint8 city_1_id;
		uint8 city_2_id;
		
		uint8 control_id;
		EndeavorTokenType token_type;

	public:
		Connection(uint8 c_1_id, uint8 c_2_id, EndeavorTokenType token_id, wxBitmap* token_img, PixelPoint* pixel_center, PixelDimension& pixel_dim);
		virtual ~Connection();
		
		void breakControlOfConnection();
		EndeavorTokenType takeControlOfConnection(uint8 player_id, wxBitmap* player_circle_img);
		
		String* getConnectionKey1();
		String* getConnectionKey2();

		uint8 getCity1ID();
		uint8 getCity2ID();
	  
		uint8 getControlID();

		void draw(wxDC&  dc);
		
		static int compareConnectionsByFirstCity(Connection* connection_1, Connection* connection_2);
		static int compareConnectionsBySecondCity(Connection* connection_1, Connection* connection_2);
		static int compareConnectionsByKeyAndFirstCity(String* connection_key, Connection* connection);
		static int compareConnectionsByKeyAndSecondCity(String* connection_key, Connection* connection);

		TiXmlElement* writeXML();
        void readXML(TiXmlElement* connection_element, wxBitmap** player_images, wxBitmap** token_images);
};

#endif
