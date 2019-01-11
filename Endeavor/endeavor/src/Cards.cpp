#include "Cards.h"
#include "EndeavorGame.h"

#include "ListArrayIterator.h"
#include "StackLinked.h"

#include <sstream>

Card* Cards::lookAtTopCard()
{
	return pq_cards->pqPeek();
}

Card* Cards::takeSelectedCard(uint8 player_id)
{
   bool any_cards = !pq_cards->pqIsEmpty();
   Card* card = NULL;

   if (any_cards)  
   {
	   card = pq_cards->pqRemove();
   }
   
   return card;
}

void Cards::returnCardToRegion(Card* card)
{
   pq_cards->pqInsert(card);
   //cards->push(card);
   card->setPlayerID(0, &card_region_loc);
}

uint8 Cards::getCardLevel()
{
	bool any_cards = !pq_cards->pqIsEmpty();
	uint8 card_level = 255;
	
	if (any_cards)
	{
		Card* card = pq_cards->pqRemove();
		card_level = card->getCardLevel();
		pq_cards->pqInsert(card);
	}
	
	return card_level;
}

Card* Cards::moveGovernorCardToPlayer()
{
	Card* governor_card = NULL;
	Card* card = pq_cards->pqRemove();
	bool is_governor_card = card->isGovernor();
	pq_cards->pqInsert(card);
	
	if (is_governor_card)
	{
		governor_card = pq_cards->pqRemove();
	}
	return governor_card;
}

EndeavorRegionType Cards::findSelectedCard(uint32 x, uint32 y)
{
   bool any_cards = !pq_cards->pqIsEmpty();
   EndeavorRegionType card_id = INVALID_REGION_TYPE;

   if (any_cards)
   {
      Card* card = pq_cards->pqRemove();
      if (card->isSelectedCard(x, y))
      {
			card_id = card->getCardID(); 
      }
	  pq_cards->pqInsert(card);
   }
   
   return card_id;
}

void Cards::draw(wxDC&  dc)
{
	bool any_cards = !pq_cards->pqIsEmpty();
	if (any_cards)
	{
		Card* card = pq_cards->pqPeek();
		card->draw(dc);
		//pq_cards->pqInsert(card);
	}
}

Cards::Cards(EndeavorRegionType region_type, ImageLoader* image_loader, PixelPoint& card_region_center, PixelDimension& card_region_dim, PixelDimension& card_region_rot_dim) : card_region_loc(card_region_center)
{
	//cards = new CSC1310::StackLinked<Card>();
	pq_cards = new CSC1310::PQHeap<Card>(&Card::compareCardsByLevelAsc);
	all_cards = new CSC1310::ListArray<Card>();
	
	card_images = new wxBitmap*[12];
	
	switch(region_type)
	{
		case (MEDITERRANEAN):
		{
			int card_counter = 0;
			for (int i = 5; i >= 0; i--)
			{
				//complicated since the file name needs the current value of i
				std::ostringstream s_card_str;
				s_card_str << "mediterranean_" << i;
				std::string card_str(s_card_str.str());
				
				std::ostringstream s_card_rot_str;
				s_card_rot_str << "mediterranean_" << i;
				std::string card_rot_str(s_card_rot_str.str());

				wxBitmap* card_img = image_loader->loadImageRGBA(card_str.c_str());
				wxBitmap* card_rot_img = image_loader->loadImageRGBA(card_rot_str.c_str());

				card_images[card_counter++] = card_rot_img;
				card_images[card_counter++] = card_img;

				Card* card;
					
				switch(i)
				{
					case 0: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 1, 1, 0, 0, false, false); break;
					case 1: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 2, 0, 1, 0, false, false); break;
					case 2: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 0, 3, 0, false, false); break;
					case 3: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 1, 1, 1, 1, 0, false, false); break;
					case 4: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 0, 0, 5, false, false); break;
					case 5: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 3, 0, 0, 3, false, false); break;
				}
				//cards->push(card);
				pq_cards->pqInsert(card);
				all_cards->add(1, card);
			}
			break;
		}
		
		case (AFRICA):
		{
			int card_counter = 0;
			for (int i = 5; i >= 0; i--)
			{
				//complicated since the file name needs the current value of i
				std::ostringstream s_card_str;
				s_card_str << "africa_" << i;
				std::string card_str(s_card_str.str());
				
				std::ostringstream s_card_rot_str;
				s_card_rot_str << "africa_" << i << "_rot";
				std::string card_rot_str(s_card_rot_str.str());

				wxBitmap* card_img = image_loader->loadImageRGBA(card_str.c_str());
				wxBitmap* card_rot_img = image_loader->loadImageRGBA(card_rot_str.c_str());

				card_images[card_counter++] = card_rot_img;
				card_images[card_counter++] = card_img;

				Card* card;
					
				switch(i)
				{
					case 0: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 2, 1, 1, false, true); break;
					case 1: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 1, 0, 0, 1, 0, false, false); break;
					case 2: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 1, 0, 1, 1, 0, false, false); break;
					case 3: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 2, 2, 0, false, false); break;
					case 4: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 2, 0, 1, 1, 1, false, false); break;
					case 5: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 2, 0, 2, 0, 2, false, false); break;
				}
				//cards->push(card);
				pq_cards->pqInsert(card);
				all_cards->add(1, card);
			}
			break;
		}
		
		case (SOUTH_AMERICA):
		{
			int card_counter = 0;
			for (int i = 5; i >= 0; i--)
			{
				//complicated since the file name needs the current value of i
				std::ostringstream s_card_str;
				s_card_str << "south_america_" << i;
				std::string card_str(s_card_str.str());
				
				std::ostringstream s_card_rot_str;
				s_card_rot_str << "south_america_" << i << "_rot";
				std::string card_rot_str(s_card_rot_str.str());

				wxBitmap* card_img = image_loader->loadImageRGBA(card_str.c_str());
				wxBitmap* card_rot_img = image_loader->loadImageRGBA(card_rot_str.c_str());

				card_images[card_counter++] = card_rot_img;
				card_images[card_counter++] = card_img;

				Card* card;
					
				switch(i)
				{
					case 0: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 0, 3, 1, false, true); break;
					case 1: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 2, 0, 0, 0, false, false); break;
					case 2: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 3, 0, 0, 0, false, false); break;
					case 3: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 4, 0, 0, 0, false, false); break;
					case 4: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 3, 0, 2, false, false); break;
					case 5: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 3, 0, 3, false, false); break;
				}
				//cards->push(card);
				pq_cards->pqInsert(card);
				all_cards->add(1, card);
			}
			break;
		}
		
		case (CARIBBEAN):
		{
			int card_counter = 0;
			for (int i = 5; i >= 0; i--)
			{
				//complicated since the file name needs the current value of i
				std::ostringstream s_card_str;
				s_card_str << "caribbean_" << i;
				std::string card_str(s_card_str.str());
				
				std::ostringstream s_card_rot_str;
				s_card_rot_str << "caribbean_" << i;
				std::string card_rot_str(s_card_rot_str.str());

				wxBitmap* card_img = image_loader->loadImageRGBA(card_str.c_str());
				wxBitmap* card_rot_img = image_loader->loadImageRGBA(card_rot_str.c_str());

				card_images[card_counter++] = card_rot_img;
				card_images[card_counter++] = card_img;

				Card* card;
					
				switch(i)
				{
					case 0: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 2, 0, 1, 1, false, true); break;
					case 1: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 0, 2, 0, false, false); break;
					case 2: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 1, 2, 0, false, false); break;
					case 3: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 4, 0, 0, false, false); break;
					case 4: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 0, 3, 2, false, false); break;
					case 5: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 3, 0, 0, 0, 3, false, false); break;
				}
				//cards->push(card);
				pq_cards->pqInsert(card);
				all_cards->add(1, card);
			}
			break;
		}
		
		case (NORTH_AMERICA):
		{
			int card_counter = 0;
			for (int i = 5; i >= 0; i--)
			{
				//complicated since the file name needs the current value of i
				std::ostringstream s_card_str;
				s_card_str << "north_america_" << i;
				std::string card_str(s_card_str.str());
				
				std::ostringstream s_card_rot_str;
				s_card_rot_str << "north_america_" << i << "_rot";
				std::string card_rot_str(s_card_rot_str.str());

				wxBitmap* card_img = image_loader->loadImageRGBA(card_str.c_str());
				wxBitmap* card_rot_img = image_loader->loadImageRGBA(card_rot_str.c_str());

				card_images[card_counter++] = card_rot_img;
				card_images[card_counter++] = card_img;

				Card* card;
					
				switch(i)
				{
					case 0: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 1, 2, 1, false, true); break;
					case 1: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 2, 0, 0, 0, 0, false, false); break;
					case 2: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 3, 0, 0, false, false); break;
					case 3: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 2, 2, 0, 0, 0, false, false); break;
					case 4: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 2, 0, 2, 1, false, false); break;
					case 5: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 0, 0, 6, false, false); break;
				}
				//cards->push(card);
				pq_cards->pqInsert(card);
				all_cards->add(1, card);
			}
			break;
		}
		
		case (INDIA):
		{
			int card_counter = 0;
			for (int i = 5; i >= 0; i--)
			{
				//complicated since the file name needs the current value of i
				std::ostringstream s_card_str;
				s_card_str << "india_" << i;
				std::string card_str(s_card_str.str());
				
				std::ostringstream s_card_rot_str;
				s_card_rot_str << "india_" << i << "_rot";
				std::string card_rot_str(s_card_rot_str.str());

				wxBitmap* card_img = image_loader->loadImageRGBA(card_str.c_str());
				wxBitmap* card_rot_img = image_loader->loadImageRGBA(card_rot_str.c_str());

				card_images[card_counter++] = card_rot_img;
				card_images[card_counter++] = card_img;

				Card* card;
					
				switch(i)
				{
					case 0: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 1, 1, 1, 1, false, true); break;
					case 1: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 1, 0, 1, 0, false, false); break;
					case 2: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 1, 1, 1, 0, false, false); break;
					case 3: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 1, 2, 1, 0, false, false); break;
					case 4: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 2, 1, 2, false, false); break;
					case 5: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 2, 2, 2, false, false); break;
				}
				//cards->push(card);
				pq_cards->pqInsert(card);
				all_cards->add(1, card);
			}
			break;
		}
		
		case (FAR_EAST):
		{
			int card_counter = 0;
			for (int i = 5; i >= 0; i--)
			{
				//complicated since the file name needs the current value of i
				std::ostringstream s_card_str;
				s_card_str << "far_east_" << i;
				std::string card_str(s_card_str.str());
				
				std::ostringstream s_card_rot_str;
				s_card_rot_str << "far_east_" << i << "_rot";
				std::string card_rot_str(s_card_rot_str.str());

				wxBitmap* card_img = image_loader->loadImageRGBA(card_str.c_str());
				wxBitmap* card_rot_img = image_loader->loadImageRGBA(card_rot_str.c_str());

				card_images[card_counter++] = card_rot_img;
				card_images[card_counter++] = card_img;

				Card* card;
					
				switch(i)
				{
					case 0: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 2, 1, 0, 0, 1, false, true); break;
					case 1: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 1, 0, 1, 0, 0, false, false); break;
					case 2: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 2, 0, 1, 0, 0, false, false); break;
					case 3: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 2, 0, 2, 0, 0, false, false); break;
					case 4: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 1, 1, 1, 1, 1, false, false); break;
					case 5: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 0, 3, 3, false, false); break;
				}
				//cards->push(card);
				pq_cards->pqInsert(card);
				all_cards->add(1, card);
			}
			break;
		}
		
		case (SLAVERY):
		{
			int card_counter = 0;
			for (int i = 5; i >= 0; i--)
			{
				//complicated since the file name needs the current value of i
				std::ostringstream s_card_str;
				s_card_str << "slavery_" << i;
				std::string card_str(s_card_str.str());
				
				std::ostringstream s_card_rot_str;
				s_card_rot_str << "slavery_" << i;
				std::string card_rot_str(s_card_rot_str.str());

				wxBitmap* card_img = image_loader->loadImageRGBA(card_str.c_str());
				wxBitmap* card_rot_img = image_loader->loadImageRGBA(card_rot_str.c_str());

				card_images[card_counter++] = card_rot_img;
				card_images[card_counter++] = card_img;

				Card* card;
					
				switch(i)
				{
					case 0: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 2, 0, 0, 0, 0, true, false); break;
					case 1: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 0, 0, 2, 0, 0, true, false); break;
					case 2: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 1, 0, 2, 0, 0, true, false); break;
					case 3: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 3, 0, 0, 0, 0, true, false); break;
					case 4: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 2, 0, 2, 0, 0, true, false); break;
					case 5: card = new Card(region_type, i, card_img, card_rot_img, &card_region_loc, card_region_dim, card_region_rot_dim, 3, 0, 2, 0, 0, true, false); break;
				}
				//cards->push(card);
				pq_cards->pqInsert(card);
				all_cards->add(1, card);
			}
			break;
		}
	}
}

Cards::~Cards()
{
	while(!pq_cards->pqIsEmpty())
   {
      Card* card = pq_cards->pqRemove();
      delete card;
   }
   delete pq_cards;
   delete all_cards;
 
//delete card images
   for (int i = 0; i <= 11; i++)
   {
	   delete card_images[i];
   }
   delete[] card_images;
}

Card* Cards::getCard(uint8 card_level)
{
	return all_cards->get(card_level+1);
}

TiXmlElement* Cards::writeXML()
{
   TiXmlElement* cards_element = new TiXmlElement("Cards");
   
  //get the cards out of the priority queue to write XML tags for them
    CSC1310::StackLinked<Card>* stack_cards = new CSC1310::StackLinked<Card>();
	while(!pq_cards->pqIsEmpty())
	{
		Card* card = pq_cards->pqRemove();
		stack_cards->push(card);
		TiXmlElement* card_element = card->writeXML();
		cards_element->LinkEndChild(card_element);
	}
	
	//put the cards back on the priority queue
	while(!stack_cards->isEmpty())
	{
		Card* card = stack_cards->pop();
		pq_cards->pqInsert(card);
	}
	delete stack_cards;

   return cards_element;
}

void Cards::readXML(TiXmlElement* cards_element)
{	  
	//empty out the priority queue
	while(!pq_cards->pqIsEmpty())
	{
		Card* card = pq_cards->pqRemove();
	}
	
   TiXmlElement* card_element = cards_element->FirstChildElement();
   while(card_element != NULL)
   {
	   TiXmlElement* card_level_element = card_element->FirstChildElement();
	   uint8 card_level = (uint8) EndeavorGame::integerFromXMLElement(card_level_element);

	   Card* card = all_cards->get(card_level+1);
	   card->readXML(card_element, card_region_loc);
	   pq_cards->pqInsert(card);
	   card_element = card_element->NextSiblingElement();
   }
}
