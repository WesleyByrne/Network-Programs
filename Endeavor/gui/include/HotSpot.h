#if !defined HOT_SPOT_H
#define HOT_SPOT_H

#include "GUIHeader.h"

#include "PixelPoint.h"
#include "PixelDimension.h"

class HotSpot
{
	private:
		uint8 hot_spot_id;
		PixelPoint hot_center;
		PixelDimension hot_dimension;

	public:
		HotSpot(uint8 hot_id, PixelPoint& center, PixelDimension& dim);
		virtual ~HotSpot();
		
		PixelPoint getHotSpotCenter();
		PixelDimension getHotSpotDimension();
		
		uint32 getHotSpotLeft();
		uint32 getHotSpotTop();
		
		uint8 getHotSpotID();
		void setHotSpotID(uint8 hot_id);
		
		void setHotSpotLocation(PixelPoint& center);
		bool isSelectedHotSpot(uint32 x_loc, uint32 y_loc);
};

#endif
