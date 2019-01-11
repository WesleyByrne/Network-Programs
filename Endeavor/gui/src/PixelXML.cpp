#include "PixelXML.h"
#include "PixelDimension.h"
#include "PixelPoint.h"

#include <stdexcept>
//#include <cstdlib>  //atoi, atof (actual include not needed?)
#include <iostream>

PixelXML::PixelXML(const char* xml_file_name) : pixel_xml_document(xml_file_name)
{
	bool success = pixel_xml_document.LoadFile();
	if (!success)
	{
		throw std::runtime_error("Error Parsing XML File");
	}
}

PixelXML::~PixelXML()
{}

PixelDimension PixelXML::getPixelDimension(const char* image_element_name)
{
	TiXmlElement* root_element = pixel_xml_document.RootElement();
	TiXmlElement* image_element = root_element->FirstChildElement(image_element_name);
	
	TiXmlElement* dimensions_element = image_element->FirstChildElement("dimensions");
	TiXmlElement* width_element = dimensions_element->FirstChildElement("width");
	TiXmlElement* height_element = dimensions_element->FirstChildElement("height");
	  
	uint32 w = atoi(width_element->GetText());
	uint32 h = atoi(height_element->GetText());
	
	PixelDimension pixel_dim(w, h);
	return pixel_dim;
}

PixelPoint PixelXML::getPixelCenter(const char* image_element_name)
{
	TiXmlElement* root_element = pixel_xml_document.RootElement();
	TiXmlElement* image_element = root_element->FirstChildElement(image_element_name);
	
	TiXmlElement* center_element = image_element->FirstChildElement("center");
	TiXmlElement* x_center_element = center_element->FirstChildElement("x");
	TiXmlElement* y_center_element = center_element->FirstChildElement("y");
	  
	uint32 x_center = atoi(x_center_element->GetText());
	uint32 y_center = atoi(y_center_element->GetText());
	
	PixelPoint pixel_center(x_center, y_center);
	return pixel_center;
}

PixelPoint** PixelXML::getPixelCentersArray(const char* image_element_name)
{
	TiXmlElement* root_element = pixel_xml_document.RootElement();
	TiXmlElement* image_element = root_element->FirstChildElement(image_element_name);
	
	TiXmlElement* start_element = image_element->FirstChildElement("center");
	TiXmlElement* center_element = start_element;
	int element_count = 0;
	while(center_element != NULL)
	{
		center_element = center_element->NextSiblingElement();
		element_count++;
	}

	if (element_count == 0) return NULL;
	PixelPoint** pixel_centers = new PixelPoint*[element_count + 1];
	
	element_count = 0;
	center_element = start_element;
	while(center_element != NULL)
	{	
		TiXmlElement* x_center_element = center_element->FirstChildElement("x");
		TiXmlElement* y_center_element = center_element->FirstChildElement("y");
		uint32 x_center = atoi(x_center_element->GetText());
		uint32 y_center = atoi(y_center_element->GetText());
	
		PixelPoint* pixel_center  = new PixelPoint(x_center, y_center);
		pixel_centers[element_count] = pixel_center;
		
		center_element = center_element->NextSiblingElement();
		element_count++;
	}
	
	pixel_centers[element_count] = NULL;
	
	return pixel_centers;
}

CSC2110::ListArray<PixelPoint>* PixelXML::getPixelCentersList(const char* image_element_name)
{
	TiXmlElement* root_element = pixel_xml_document.RootElement();
	TiXmlElement* image_element = root_element->FirstChildElement(image_element_name);
	
	CSC2110::ListArray<PixelPoint>* pixel_centers = new CSC2110::ListArray<PixelPoint>();
	TiXmlElement* center_element = image_element->FirstChildElement("center");
	while(center_element != NULL)
	{
		TiXmlElement* x_center_element = center_element->FirstChildElement("x");
		TiXmlElement* y_center_element = center_element->FirstChildElement("y");
		uint32 x_center = atoi(x_center_element->GetText());
		uint32 y_center = atoi(y_center_element->GetText());
	
		PixelPoint* pixel_center  = new PixelPoint(x_center, y_center);
		pixel_centers->add(pixel_center);
		
		center_element = center_element->NextSiblingElement();
	}
	
	return pixel_centers;
}
