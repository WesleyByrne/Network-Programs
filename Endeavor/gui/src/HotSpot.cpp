#include "HotSpot.h"
#include <cmath>
#include <iostream>

HotSpot::HotSpot(uint8 id, PixelPoint& center, PixelDimension& dim) : hot_center(center), hot_dimension(dim)
{
	hot_spot_id = id;
}

HotSpot::~HotSpot() {}

PixelPoint HotSpot::getHotSpotCenter()
{
	return hot_center;
}

PixelDimension HotSpot::getHotSpotDimension()
{
	return hot_dimension;
}

uint8 HotSpot::getHotSpotID()
{
	return hot_spot_id;
}

void HotSpot::setHotSpotID(uint8 id)
{
	hot_spot_id = id;
}

void HotSpot::setHotSpotLocation(PixelPoint& center)
{
	hot_center = center;
}

uint32 HotSpot::getHotSpotLeft()
{
	return hot_center.getX() - hot_dimension.getWidth()/2;
}

uint32 HotSpot::getHotSpotTop()
{
	return hot_center.getY() - hot_dimension.getHeight()/2;
}

bool HotSpot::isSelectedHotSpot(uint32 x_click, uint32 y_click)
{
	uint32 x_hit = abs(x_click - hot_center.getX());
	uint32 y_hit = abs(y_click - hot_center.getY());
	
	if (x_hit < (hot_dimension.getWidth()/2) && y_hit < (hot_dimension.getHeight()/2))
	{
		return true;
	}

	return false;
}
