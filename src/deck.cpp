#include "deck.h"

Deck::Deck()
{
	this->ResetDeck();
}

Deck& Deck::ResetDeck()
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

Card Deck::DealCard(Card::Rank rank)
{
	for (std::vector<Card>::iterator it = _deck.begin(); it != _deck.end(); it++) {
		if ((*it).rank() == rank) {
			Card c = (*it);
			_deck.erase(it);
			return c;
		}
	}

	// ���δ�ҵ�ָ�� rank �� Card�����׳��쳣
	throw std::runtime_error("Card not found.");
}

Card Deck::PeekNextCard()
{
	Card card = _deck.back();
	return card;
}

const int Deck::DeckSize() const
{
	return static_cast<const int>(_deck.size());
}
