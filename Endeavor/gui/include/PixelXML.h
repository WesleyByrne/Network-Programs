#if !defined PIXEL_XML
#define PIXEL_XML

#include "tinyxml.h"
#include <string>
#include "GUIHeader.h"
#include "ListArray.h"

class PixelPoint;
class PixelDimension;

class PixelXML
{
	private:
		TiXmlDocument pixel_xml_document;
		
	public:
		PixelXML(const char* xml_file_name);
		virtual ~PixelXML();
		
		PixelDimension getPixelDimension(const char* image_element_name);
		PixelPoint getPixelCenter(const char* image_element_name);
		PixelPoint** getPixelCentersArray(const char* image_element_name);
		CSC1310::ListArray<PixelPoint>* getPixelCentersList(const char* image_element_name);
};

#endif
