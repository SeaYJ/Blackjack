#pragma once

#include <iostream>
#include <string>
#include <array>
#include <sstream>

class Card
{
public:
	enum class Rank {					// 牌名定义
		ACE = 1, TWO, THREE, FOUR, FIVE,
		SIX, SEVEN, EIGHT, NINE, TEN,
		JACK, QUEEN, KING
	};

	explicit Card(const Rank rank)		// 构造函数
		:_kRank(rank),
		_kSymbol(_kSymbolStr[static_cast<int>(rank) - 1]),
		_kPoints((static_cast<int>(rank) > 10 ? int(static_cast<int>(rank) * 0.5) : static_cast<int>(rank)))
	{}

	// 取函数
	const Rank rank() const;			
	const std::string symbol() const;	
	const int points() const;			

	// 普通功能函数
	std::string display(const int line) const;	// 单行展示（留着多牌并列输出的）
	std::string display() const;				// 基于单行展示实现的完整牌形展示

private:
	const std::array<std::string, 13> _kSymbolStr = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K" };
	const Rank _kRank;					// 牌名
	const std::string _kSymbol;			// 牌在程序中的符号
	const int _kPoints;					// 牌实际的点数

	std::string printSpecialLine(const int line) const;
};

