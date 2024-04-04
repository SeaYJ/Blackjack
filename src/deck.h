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

	// 一般功能函数
	Deck& ResetDeck();				// 重置牌堆
	Deck& Shuffle();				// 洗牌
	Card DealCard();				// 发牌（从 vector 的 last 开始发牌）
	Card DealCard(Card::Rank rank);	// 发牌（指定特定的牌）
	Card PeekNextCard();			// 窥探下一张牌
	const int DeckSize() const;		// 获取牌堆未发牌的总数

private:
	std::vector<Card> _deck;	// 牌堆
};

#endif // !_DECK_H_


