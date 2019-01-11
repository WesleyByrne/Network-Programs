#include "PixelPoint.h"

PixelPoint::PixelPoint(uint32 x, uint32 y) 
{
	x_loc = x;
	y_loc = y;
}

PixelPoint::~PixelPoint() {}
		
uint32 PixelPoint::getX() 
{
	return x_loc;
}

uint32 PixelPoint::getY()
{
	return y_loc;
}
