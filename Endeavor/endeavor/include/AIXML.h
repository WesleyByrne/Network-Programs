#if !defined AI_XML
#define AI_XML

#include "EndeavorHeader.h"

#include "tinyxml.h"
#include <string>

class AIXML
{
	private:
		TiXmlDocument ai_xml_document;
		
	public:
		AIXML(const char* xml_file_name);
		virtual ~AIXML();
		
		EndeavorActionType* getActionPriorityList();
		EndeavorTokenType* getCityTokenPriorityList();
		EndeavorTokenType* getShipTokenPriorityList();
		EndeavorBuildingType* getBuildingPaymentPriorityList();
		EndeavorBuildingType* getBuildingSelectPriorityList();
};

#endif
