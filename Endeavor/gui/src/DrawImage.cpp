#include "DrawImage.h"
#include "HotSpot.h"
#include "PixelPoint.h"
#include "PixelDimension.h"

#include "wx/wx.h"
	
DrawImage::DrawImage(wxBitmap* img, uint8 img_id, PixelDimension& pixel_dim)
{
	image = img;
	PixelPoint pixel_point(0, 0);
	hot_spot = new HotSpot(img_id, pixel_point, pixel_dim);
	visible = false;
}

DrawImage::~DrawImage()
{
	delete hot_spot;
}

void DrawImage::setImage(wxBitmap* img)
{
	image = img;
}

PixelPoint DrawImage::getDrawImageCenter()
{
	return hot_spot->getHotSpotCenter();
}

PixelDimension DrawImage::getDrawImageDimension()
{
	return hot_spot->getHotSpotDimension();
}

uint8 DrawImage::getDrawImageID()
{
	return hot_spot->getHotSpotID();
}

void DrawImage::setDrawImageID(uint8 img_id)
{
	return hot_spot->setHotSpotID(img_id);
}
	
bool DrawImage::isVisible()
{
	return visible;
}

bool DrawImage::isSelectedDrawImage(uint32 x_click, uint32 y_click)
{
	if (!visible) return false;
	return hot_spot->isSelectedHotSpot(x_click, y_click);
}

void DrawImage::showImage(PixelPoint& image_location)
{
	hot_spot->setHotSpotLocation(image_location);
	visible = true;
}
	
void DrawImage::hideImage()
{
	visible = false;
}

void DrawImage::draw(wxDC& dc)
{
	if (visible)
	{
		dc.DrawBitmap(*image, hot_spot->getHotSpotLeft(), hot_spot->getHotSpotTop());
	}
}
