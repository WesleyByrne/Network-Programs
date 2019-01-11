#if !defined PIXEL_DIMENSION_H
#define PIXEL_DIMENSION_H

#include "GUIHeader.h"

class PixelDimension
{
	private:
		uint32 width;
		uint32 height;
	
	public:
		PixelDimension(uint32 w, uint32 h);
		virtual ~PixelDimension();
		
		uint32 getWidth();
		uint32 getHeight();
};

#endif
