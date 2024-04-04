#pragma once

#ifndef _DECK_H_
#define _DECK_H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "card.h"

class Deck
{
public:
	explicit Deck();

	// һ�㹦�ܺ���
	Deck& ResetDeck();				// �����ƶ�
	Deck& Shuffle();				// ϴ��
	Card DealCard();				// ���ƣ��� vector �� last ��ʼ���ƣ�
	Card DealCard(Card::Rank rank);	// ���ƣ�ָ���ض����ƣ�
	Card PeekNextCard();			// ��̽��һ����
	const int DeckSize() const;		// ��ȡ�ƶ�δ���Ƶ�����

private:
	std::vector<Card> _deck;	// �ƶ�
};

#endif // !_DECK_H_


