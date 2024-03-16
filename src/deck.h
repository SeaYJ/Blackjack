#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "card.h"

class Deck
{
public:
	explicit Deck();
	Deck& resetDeck();
	Deck& Shuffle();			// ϴ��
	Card DealCard();			// ���ƣ��� vector �� last ��ʼ���ƣ�
private:
	std::vector<Card> _deck;	// �ƶ�
};

