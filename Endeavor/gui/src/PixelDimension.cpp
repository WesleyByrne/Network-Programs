#include "PixelDimension.h"

PixelDimension::PixelDimension(uint32 w, uint32 h) 
{
	width = w;
	height = h;
}

PixelDimension::~PixelDimension() {}
		
uint32 PixelDimension::getWidth() 
{
	return width;
}

uint32 PixelDimension::getHeight()
{
	return height;
}
