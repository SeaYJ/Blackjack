#pragma once

#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include "console_color.h"

class Card
{
public:
	enum class Rank {					// 牌名定义
		ACE = 1, TWO, THREE, FOUR, FIVE,
		SIX, SEVEN, EIGHT, NINE, TEN,
		JACK, QUEEN, KING
	};

	explicit Card(const Rank rank)		// 构造函数
		:_rank(rank),
		_symbol(_kSymbolStr[static_cast<int>(rank) - 1]),
		_points((rank >= Rank::JACK ? int(static_cast<int>(rank) * 0.5) : static_cast<int>(rank))),
		_color((rank >= Rank::TEN ? yellow : def))
	{}		

	// 取函数
	Rank rank() const;
	std::string symbol() const;
	int points() const;

	// 普通功能函数
	std::string Display(const int line) const;	// 单行展示（留着多牌并列输出的）
	std::string Display() const;				// 基于单行展示实现的完整牌形展示

private:
	static const std::array<const std::string, 13> _kSymbolStr;
	Rank _rank;							// 牌名
	std::string _symbol;				// 牌在程序中的符号
	int _points;						// 牌实际的点数
	ConsoleColor::Modifier _color;		// 牌色

	std::string printSpecialLine(const int line) const;
};

