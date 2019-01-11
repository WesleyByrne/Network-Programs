#if !defined ENDEAVOR_PLAYER_CARD_MANAGER
#define ENDEAVOR_PLAYER_CARD_MANAGER

#include "wx/wx.h"
#include "tinyxml.h"

#include "ListArray.h"

#include "EndeavorHeader.h"
#include "Card.h"

class EndeavorGame;
class PlayerCardManager
{
	private:
		CSC1310::ListArray<Card>* cards;

		bool hasGovernorCard();
		bool hasSlaveryCard();
		uint8 needsToUseSlaverySpace(uint8 num_regular_allowed);
		uint8 needsToUseGovernorSpace();
		void sortCardsByLevel();
		
		uint8 num_discarded_slavery_cards;

	public:
		PlayerCardManager();
		virtual ~PlayerCardManager();
		
		uint8 getNumDiscardedSlaveryCards();
		
		void placeCardsOnPlayerBoard(uint8 num_regular_allowed, CSC1310::ListArray<PixelPoint>* player_board_card_locs);
		void placeCardsOnPlayerBoard(uint8 num_regular_allowed);

		uint8 getDefaultCardToDiscard(uint8 num_regular_allowed);
		void addCard(Card* card, uint8 num_regular_allowed, CSC1310::ListArray<PixelPoint>* player_board_card_locs);
		bool mustDiscard(uint8 num_regular_allowed);
		bool mustDiscardIfCardTaken(Card* card, uint8 enhanced_num_regular_allowed);
		uint8 findSelectedCardToDiscard(uint32 x, uint32 y);
		Card* discard(uint8 card_id, uint8 num_regular_allowed);
		CSC1310::ListArray<Card>* abolishSlavery(uint8 num_regular_allowed);
		
		bool isFreeGovernorSpaceUncovered(uint8 num_regular_allowed);
		uint8 getNumCardsOnPlayerBoard();

		void draw(wxDC&  dc);
		
		TiXmlElement* writeXML();
        void readXML(TiXmlElement* card_element, EndeavorGame* game, uint8 num_regular_allowed, CSC1310::ListArray<PixelPoint>* player_board_card_locs);
};

#endif
