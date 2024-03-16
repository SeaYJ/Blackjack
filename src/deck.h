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
	Deck& Shuffle();			// 洗牌
	Card DealCard();			// 发牌（从 vector 的 last 开始发牌）
private:
	std::vector<Card> _deck;	// 牌堆
};

