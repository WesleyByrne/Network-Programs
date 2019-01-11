#include "Card.h"
#include "EndeavorGame.h"

uint8 Card::getPlayerBoardLoc()
{
	return player_board_loc;
}

void Card::setPlayerBoardLoc(uint8 board_loc)
{
	player_board_loc = board_loc;
}

int Card::compareCardsByLevelAsc(Card* card_1, Card* card_2)
{
	uint8 level_1 = card_1->getCardLevel();
	uint8 level_2 = card_2->getCardLevel();
	return ((int) level_1) - ((int) level_2);
}

int Card::compareCardsByLevelDesc(Card* card_1, Card* card_2)
{
	return -1*(compareCardsByLevelAsc(card_1, card_2));
}

Card::Card(EndeavorRegionType r_type, uint8 c_level, wxBitmap* card_img, wxBitmap* card_rot_img, PixelPoint* pixel_center, PixelDimension& pixel_dim, PixelDimension& pixel_rot_dim, uint8 industry_, uint8 culture_, uint8 finance_, uint8 politics_, uint8 glory_, bool slavery_, bool governor_)
{
	region_type = r_type;
   player_id = 0;
   player_board_loc = 0;
   card_level = c_level;

   industry = industry_;
   culture = culture_;
   finance = finance_;
   politics = politics_;
   glory = glory_;

   slavery = slavery_;
   governor = governor_;
   
   card_draw_img_rotated = new DrawImage(card_rot_img, (uint8) r_type, pixel_rot_dim);
   card_draw_img_rotated->showImage(*pixel_center);
   
   card_draw_img = new DrawImage(card_img, (uint8) r_type, pixel_dim);
}

Card::~Card()
{
	//the wxBitmap is not deleted
	delete card_draw_img;
	delete card_draw_img_rotated;
}

uint8 Card::getCardLevel()
{
   return card_level;
}

EndeavorRegionType Card::getCardID()
{
	return region_type;
   //return card_draw_img->getDrawImageID();
}

uint8 Card::getPlayerID()
{
   return player_id;
}

void Card::setPlayerID(uint8 p_id)
{
	player_id = p_id;
}

void Card::setPlayerID(uint8 p_id, PixelPoint* pixel_center)
{
	player_id = p_id;
	if (p_id > 0)
	{
		card_draw_img->showImage(*pixel_center);
		card_draw_img_rotated->hideImage();
	}
	else
	{
		card_draw_img_rotated->showImage(*pixel_center);
		card_draw_img->hideImage();
		player_board_loc = 0;
	}
}

bool Card::isGovernor()
{
   return governor;
}

bool Card::isSlavery()
{
   return slavery;
}

uint8 Card::getIndustry()
{
   return industry;
}

uint8 Card::getCulture()
{
   return culture;
}

uint8 Card::getFinance()
{
   return finance;
}

uint8 Card::getPolitics()
{
   return politics;
}

uint8 Card::getGlory()
{
   return glory;
}

bool Card::isSelectedCard(uint32 x, uint32 y)
{
	if (card_draw_img->isVisible())
	{
		return card_draw_img->isSelectedDrawImage(x, y);
	}
	else
	{
		return card_draw_img_rotated->isSelectedDrawImage(x, y);
	}
}

void Card::draw(wxDC&  dc)
{
	//only one will be drawn
	card_draw_img->draw(dc);
	card_draw_img_rotated->draw(dc);
}

TiXmlElement* Card::writeXML()
{
   TiXmlElement* card_element = new TiXmlElement("Card");
   TiXmlElement* card_level_element = EndeavorGame::xmlElementFromInteger("card_level", (int) card_level);
   TiXmlElement* card_region_element = EndeavorGame::xmlElementFromInteger("card_region", (int) region_type);
   TiXmlElement* player_board_loc_element = EndeavorGame::xmlElementFromInteger("player_board_loc", (int) player_board_loc);
   TiXmlElement* player_id_element = EndeavorGame::xmlElementFromInteger("player_id", (int) player_id);

   card_element->LinkEndChild(card_level_element);
   card_element->LinkEndChild(card_region_element);
   card_element->LinkEndChild(player_board_loc_element);
   card_element->LinkEndChild(player_id_element);

   return card_element;
}

void Card::readXML(TiXmlElement* card_element)
{
	TiXmlElement* card_level_element = card_element->FirstChildElement();
	card_level = (uint8) EndeavorGame::integerFromXMLElement(card_level_element);
	
	TiXmlElement* card_region_element = card_level_element->NextSiblingElement();
	region_type = (EndeavorRegionType) EndeavorGame::integerFromXMLElement(card_region_element);
   
	TiXmlElement* player_board_loc_element = card_region_element->NextSiblingElement();
	player_board_loc = (uint8) EndeavorGame::integerFromXMLElement(player_board_loc_element);
		
	TiXmlElement* player_id_element = player_board_loc_element->NextSiblingElement();
	player_id = (uint8) EndeavorGame::integerFromXMLElement(player_id_element);
}

void Card::readXML(TiXmlElement* card_element, PixelPoint& card_region_loc)
{
	TiXmlElement* card_level_element = card_element->FirstChildElement();
	card_level = (uint8) EndeavorGame::integerFromXMLElement(card_level_element);
	
	TiXmlElement* card_region_element = card_level_element->NextSiblingElement();
	region_type = (EndeavorRegionType) EndeavorGame::integerFromXMLElement(card_region_element);
   
	TiXmlElement* player_board_loc_element = card_region_element->NextSiblingElement();
	player_board_loc = (uint8) EndeavorGame::integerFromXMLElement(player_board_loc_element);
	
	if (player_board_loc == 0)
	{
		setPlayerID(0, &card_region_loc);
	}
	
	TiXmlElement* player_id_element = player_board_loc_element->NextSiblingElement();
	player_id = (uint8) EndeavorGame::integerFromXMLElement(player_id_element);
}
