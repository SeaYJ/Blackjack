#pragma once

#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include "console_color.h"

class Card
{
public:
	enum class Rank {					// ��������
		ACE = 1, TWO, THREE, FOUR, FIVE,
		SIX, SEVEN, EIGHT, NINE, TEN,
		JACK, QUEEN, KING
	};

	explicit Card(const Rank rank)		// ���캯��
		:_rank(rank),
		_symbol(_kSymbolStr[static_cast<int>(rank) - 1]),
		_points((rank >= Rank::JACK ? int(static_cast<int>(rank) * 0.5) : static_cast<int>(rank))),
		_color((rank >= Rank::TEN ? yellow : def))
	{}		

	// ȡ����
	Rank rank() const;
	std::string symbol() const;
	int points() const;

	// ��ͨ���ܺ���
	std::string Display(const int line) const;	// ����չʾ�����Ŷ��Ʋ�������ģ�
	std::string Display() const;				// ���ڵ���չʾʵ�ֵ���������չʾ

private:
	static const std::array<const std::string, 13> _kSymbolStr;
	Rank _rank;							// ����
	std::string _symbol;				// ���ڳ����еķ���
	int _points;						// ��ʵ�ʵĵ���
	ConsoleColor::Modifier _color;		// ��ɫ

	std::string printSpecialLine(const int line) const;
};

