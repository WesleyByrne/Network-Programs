#if !defined DRAW_IMAGE
#define DRAW_IMAGE

#include "GUIHeader.h"
#include <string>

class PixelPoint;
class PixelDimension;
class HotSpot;

class wxBitmap;
class wxDC;

class DrawImage
{
	private:
		HotSpot* hot_spot;
		bool visible;
		wxBitmap* image;
	
	public:
		DrawImage(wxBitmap* img, uint8 img_id, PixelDimension& dim);
		virtual ~DrawImage();
		
		PixelPoint getDrawImageCenter();
		PixelDimension getDrawImageDimension();
		
		uint8 getDrawImageID();
		void setDrawImageID(uint8 img_id);
		
		void setImage(wxBitmap* img);
		
		bool isVisible();
		bool isSelectedDrawImage(uint32 x_click, uint32 y_click);
		void showImage(PixelPoint& image_location);
		void hideImage();
		void draw(wxDC& dc);
};

#endif
