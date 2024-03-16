#include "deck.h"

Deck::Deck()
{
	this->resetDeck();
}

Deck& Deck::resetDeck()
{
	// ��˳���� 13 * 4 = 52 ����
	int minRank = static_cast<int>(Card::Rank::ACE);
	int maxRank = static_cast<int>(Card::Rank::KING);
	for (int suit = 0; suit < 4; suit++) {
		for (int rankIndex = minRank; rankIndex <= maxRank; rankIndex++) {
			(this->_deck).push_back(Card(static_cast<Card::Rank>(rankIndex)));
		}
	}

	return (*this);
}

Deck& Deck::Shuffle()
{
	// ʹ������������������ƶ�˳��
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(_deck.begin(), _deck.end(), g);

	return (*this);
}

Card Deck::DealCard()
{
	Card card = _deck.back();
	_deck.pop_back();
	return card;
}
