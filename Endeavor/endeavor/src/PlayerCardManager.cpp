#include "PlayerCardManager.h"
#include "EndeavorGame.h"

#include "PixelPoint.h"

#include "ListArrayIterator.h"
#include "Sort.h"

uint8 PlayerCardManager::getNumDiscardedSlaveryCards()
{
	return num_discarded_slavery_cards;
}

void PlayerCardManager::placeCardsOnPlayerBoard(uint8 num_regular_allowed, CSC1310::ListArray<PixelPoint>* player_board_card_locs)
{
	placeCardsOnPlayerBoard(num_regular_allowed);
	
	CSC1310::ListArrayIterator<Card>* card_iter = cards->iterator();
   while(card_iter->hasNext())
   {
      Card* card = card_iter->next();
	  uint8 player_board_loc = card->getPlayerBoardLoc();
	  PixelPoint* pixel_center = player_board_card_locs->get(player_board_loc);
	  card->setPlayerID(card->getPlayerID(), pixel_center);
   }
   delete card_iter;
}

void PlayerCardManager::placeCardsOnPlayerBoard(uint8 num_regular_allowed)
{
   int num_total_cards = cards->size();      
   int over_limit = num_total_cards - num_regular_allowed;

   sortCardsByLevel();  //initial sort and board location

   if (over_limit <= 0)  //in most cases, this is good enough
   {
      return;
   }

   CSC1310::ListArray<Card>* placed_cards = new CSC1310::ListArray<Card>();  //will need to use this list
   Card* slavery_to_move = NULL;
   Card* governor_to_move = NULL;

   //check slavery first, then governor
   int needs_slavery_space = needsToUseSlaverySpace(num_regular_allowed);
   if (needs_slavery_space > 0)
   {
      over_limit--;
      //protected slavery card
      slavery_to_move = cards->get(needs_slavery_space);
      cards->remove(needs_slavery_space);
	  slavery_to_move->setPlayerBoardLoc(5);
   }
 
   int needs_governor_space = -1;
   if (over_limit > 0)
   {
      needs_governor_space = needsToUseGovernorSpace();
   }

   if (needs_governor_space > 0)
   {
      over_limit--;
      //protected governor card
      governor_to_move = cards->get(needs_governor_space);
      cards->remove(needs_governor_space);
	  governor_to_move->setPlayerBoardLoc(6);
   }

   int num_cards_left_in_sorted_list = cards->size();
   int split_loc = num_cards_left_in_sorted_list - over_limit;
   //assign and move the good cards to the new list of cards
   for (int i = 1; i <= split_loc; i++)
   {
      Card* card = cards->get(i);
	  card->setPlayerBoardLoc(i);
      placed_cards->add(card);
   }

   //assign and move possible discards
   for (int i = split_loc + 1; i <= num_cards_left_in_sorted_list; i++)
   {
      Card* card = cards->get(i);
	  card->setPlayerBoardLoc(i - split_loc + 6);
      placed_cards->add(card);
   }

   //put the protected cards (if any) into the new list, at the front (new)
   if (slavery_to_move != NULL)
   {
      placed_cards->add(1, slavery_to_move);
   }
   if (governor_to_move != NULL)
   {
      placed_cards->add(1, governor_to_move);
   }

   delete cards;
   cards = placed_cards;
}

void PlayerCardManager::sortCardsByLevel()
{
	Card** unsorted_cards = cards->toArray();
	int num_cards = cards->size();
	Card** sorted_cards = Sort<Card>::quickSort(unsorted_cards, num_cards, &Card::compareCardsByLevelDesc);
	cards->removeAll();
	
	for (int i = 0; i < num_cards; i++)
	{
		cards->add(sorted_cards[i]);
		sorted_cards[i]->setPlayerBoardLoc(i+1);
	}
	
	delete[] unsorted_cards;
	delete[] sorted_cards;
}

void PlayerCardManager::draw(wxDC&  dc)
{
   CSC1310::ListArrayIterator<Card>* card_iter = cards->iterator();
   while(card_iter->hasNext())
   {
      Card* card = card_iter->next();
      card->draw(dc);
   }
   delete card_iter;
}

uint8 PlayerCardManager::getNumCardsOnPlayerBoard()
{
   return cards->size();
}

bool PlayerCardManager::mustDiscardIfCardTaken(Card* card, uint8 enhanced_num_regular_allowed)
{
   cards->add(card);
   bool must_discard = mustDiscard(enhanced_num_regular_allowed);
   cards->remove(cards->size());  //remove the test card
   return must_discard;
}

void PlayerCardManager::addCard(Card* card, uint8 num_regular_allowed, CSC1310::ListArray<PixelPoint>* player_board_card_locs)
{
   cards->add(card);
   placeCardsOnPlayerBoard(num_regular_allowed, player_board_card_locs);
}

bool PlayerCardManager::mustDiscard(uint8 num_regular_allowed) 
{
   int num_total_cards = cards->size();

   if (num_total_cards <= num_regular_allowed) return false;
   if (num_total_cards >= 7) return true;
      
   bool has_governor_card = hasGovernorCard();
   bool has_slavery_card = hasSlaveryCard();
   bool only_one_over = (num_total_cards - 1) == num_regular_allowed;
   bool only_two_over = (num_total_cards - 2) == num_regular_allowed;
   bool less_than_five = num_regular_allowed < 5;

   //check slavery first
   //only want to use the free governor space if absolutely necessary
   //a slavery card can only be protected if the num_regular_allowed is less than five
   if (has_slavery_card && only_one_over && less_than_five) return false;
   if (has_governor_card && only_one_over) return false;
   if (has_slavery_card && has_governor_card && only_two_over && less_than_five) return false;

   return true;
}

bool PlayerCardManager::isFreeGovernorSpaceUncovered(uint8 num_regular_allowed)
{
   if (!hasGovernorCard()) return true;

   int num_total_cards = cards->size();
   bool has_slavery_card = hasSlaveryCard();

   if (num_total_cards <= num_regular_allowed) 
   {
      return true;
   }
   else if (has_slavery_card && num_regular_allowed < 5 && (num_total_cards - 1 <= num_regular_allowed))
   {
      return true;
   }

   return false;
}

bool PlayerCardManager::hasSlaveryCard()
{
   CSC1310::ListArrayIterator<Card>* card_iter = cards->iterator();
   while(card_iter->hasNext())
   {
      Card* card = card_iter->next();
      if (card->isSlavery()) 
      {
         delete card_iter;
         return true;
      }
   }
   delete card_iter;

   return false;
}

bool PlayerCardManager::hasGovernorCard()
{
   CSC1310::ListArrayIterator<Card>* card_iter = cards->iterator();
   while(card_iter->hasNext())
   {
      Card* card = card_iter->next();
      if (card->isGovernor())
      {
         delete card_iter;
         return true;
      }
   }
   delete card_iter;

   return false;
}

CSC1310::ListArray<Card>* PlayerCardManager::abolishSlavery(uint8 num_regular_allowed)
{
   CSC1310::ListArray<Card>* slavery_discards = new CSC1310::ListArray<Card>();
   if (hasSlaveryCard())
   {
      for (int card_id = 1; card_id <= cards->size(); card_id++)
      {
         Card* card = cards->get(card_id);

         if (card->isSlavery())
         {
            discard(card_id, num_regular_allowed); 
            slavery_discards->add(card);
            card_id--;         //adjust the counter as a card has been removed
         }
      }
   }
   
   return slavery_discards;
}

uint8 PlayerCardManager::getDefaultCardToDiscard(uint8 num_regular_allowed)
{
	if (!mustDiscard(num_regular_allowed)) return 0;
	else return cards->size();
}

uint8 PlayerCardManager::findSelectedCardToDiscard(uint32 x, uint32 y)
{
   uint8 card_id = 1;  //player board location
   CSC1310::ListArrayIterator<Card>* card_iter = cards->iterator();
   while(card_iter->hasNext())
   {
      Card* card = card_iter->next();
      if (card->isSelectedCard(x, y))
      {
         delete card_iter;
         return card_id;
      }
      card_id++;
   }
   delete card_iter;

   return 0;
}

Card* PlayerCardManager::discard(uint8 card_id, uint8 num_regular_allowed)  
{   
   Card* card = cards->get(card_id);
   cards->remove(card_id);
   placeCardsOnPlayerBoard(num_regular_allowed);
   
	if (card->getCardID() == SLAVERY)
	{
		num_discarded_slavery_cards++;
	}

   return card;  //regular cards go back into play
}

//will find the best slavery card to protect in the slavery space if possible (1-based)
uint8 PlayerCardManager::needsToUseSlaverySpace(uint8 num_regular_allowed)
{
   uint8 slavery_space = 0;
   int slavery_count = 1;

   CSC1310::ListArrayIterator<Card>* card_iter = cards->iterator();
   while(card_iter->hasNext())
   {
      Card* card = card_iter->next();
      if (card->isSlavery() && num_regular_allowed < 5)
      {
         slavery_space = slavery_count;
         break;
      }
      slavery_count++;
   }
   delete card_iter;

   return slavery_space;
}

//will find a governor card to protect in the free governor space (1-based)
uint8 PlayerCardManager::needsToUseGovernorSpace()
{
   uint8 governor_space = 0;
   int governor_count = 1;

   CSC1310::ListArrayIterator<Card>* card_iter = cards->iterator();
   while(card_iter->hasNext())
   {
      Card* card = card_iter->next();
      if (card->isGovernor())
      {
         governor_space = governor_count;
         break;
      }
      governor_count++;
   }
   delete card_iter;

   return governor_space;
}

PlayerCardManager::PlayerCardManager()
{
   cards = new CSC1310::ListArray<Card>();
   num_discarded_slavery_cards = 0;
}

PlayerCardManager::~PlayerCardManager()
{
   CSC1310::ListArrayIterator<Card>* card_iter = cards->iterator();
   while(card_iter->hasNext())
   {
      Card* card = card_iter->next();
      delete card;
   }
   delete card_iter;
   delete cards;
}

TiXmlElement* PlayerCardManager::writeXML()
{
	TiXmlElement* cards_element = new TiXmlElement("Cards");
	
	TiXmlElement* discarded_slavery_element = EndeavorGame::xmlElementFromInteger("discarded_slavery", (int) num_discarded_slavery_cards);
	cards_element->LinkEndChild(discarded_slavery_element);

    CSC1310::ListArrayIterator<Card>* cards_iter = cards->iterator();
	while(cards_iter->hasNext())
	{
		Card* card = cards_iter->next();
		TiXmlElement* card_element = card->writeXML();
		cards_element->LinkEndChild(card_element);
	}
	delete cards_iter;

	return cards_element;
}

void PlayerCardManager::readXML(TiXmlElement* cards_element, EndeavorGame* game, uint8 num_regular_allowed, CSC1310::ListArray<PixelPoint>* player_board_card_locs)
{
	TiXmlElement* discarded_slavery_element = cards_element->FirstChildElement("discarded_slavery");
	num_discarded_slavery_cards = (uint8) EndeavorGame::integerFromXMLElement(discarded_slavery_element);
	
   TiXmlElement* card_element = discarded_slavery_element->NextSiblingElement();
   cards->removeAll();
   while(card_element != NULL)
   {
	   TiXmlElement* card_level_element = card_element->FirstChildElement();
	   uint8 card_level = (uint8) EndeavorGame::integerFromXMLElement(card_level_element);
	   TiXmlElement* card_region_element = card_level_element->NextSiblingElement();
	   EndeavorRegionType card_region_type = (EndeavorRegionType) EndeavorGame::integerFromXMLElement(card_region_element);
	   Card* card = game->getCard(card_region_type, card_level);
	   card->readXML(card_element);
	   cards->add(card);
	   card_element = card_element->NextSiblingElement();
   }
   
   placeCardsOnPlayerBoard(num_regular_allowed, player_board_card_locs);
}
