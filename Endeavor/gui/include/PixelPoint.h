#if !defined PIXEL_POINT_H
#define PIXEL_POINT_H

#include "GUIHeader.h"

class PixelPoint
{
	private:
		uint32 x_loc;
		uint32 y_loc;
	
	public:
		PixelPoint(uint32 x, uint32 y);
		virtual ~PixelPoint();
		
		uint32 getX();
		uint32 getY();
};

#endif
