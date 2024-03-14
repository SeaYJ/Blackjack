#pragma once

#include <iostream>
#include <string>
#include <array>
#include <sstream>

class Card
{
public:
	enum class Rank {					// ��������
		ACE = 1, TWO, THREE, FOUR, FIVE,
		SIX, SEVEN, EIGHT, NINE, TEN,
		JACK, QUEEN, KING
	};

	explicit Card(const Rank rank)		// ���캯��
		:_kRank(rank),
		_kSymbol(_kSymbolStr[static_cast<int>(rank) - 1]),
		_kPoints((static_cast<int>(rank) > 10 ? int(static_cast<int>(rank) * 0.5) : static_cast<int>(rank)))
	{}

	// ȡ����
	const Rank rank() const;			
	const std::string symbol() const;	
	const int points() const;			

	// ��ͨ���ܺ���
	std::string display(const int line) const;	// ����չʾ�����Ŷ��Ʋ�������ģ�
	std::string display() const;				// ���ڵ���չʾʵ�ֵ���������չʾ

private:
	const std::array<std::string, 13> _kSymbolStr = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K" };
	const Rank _kRank;					// ����
	const std::string _kSymbol;			// ���ڳ����еķ���
	const int _kPoints;					// ��ʵ�ʵĵ���

	std::string printSpecialLine(const int line) const;
};

