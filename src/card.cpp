#include "card.h"

const std::array<const std::string, 13> Card::_kSymbolStr = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K" };


Card::Rank Card::rank() const
{
	return _rank;
}

std::string Card::symbol() const
{
	return _symbol;
}

int Card::points() const
{
	return _points;
}

std::string Card::Display(const int line) const
{
	// 避免字符串的多次拼接带来的性能消耗
	std::stringstream ss;

	ss << (this->_color);

	switch (line) {
		case 0: ss << ".------."; break;
		case 1: ss << "|" << (this->_symbol) << ".--. |"; break;
		case 2: ss << (this->printSpecialLine(1)); break;
		case 3: ss << (this->printSpecialLine(2)); break;
		case 4: ss << "| '--'" << (this->_symbol) << "|"; break;
		case 5: ss << "`------'"; break;
		default:ss << ""; break;
	}

	ss << def;

	return ss.str();
}

std::string Card::Display() const
{
	// 避免字符串的多次拼接带来的性能消耗
	std::stringstream ss;

	for (int i = 0; i < 6; i++) {
		ss << Display(i) << (i == 5 ? "" : "\n");
	}

	return ss.str();
}

std::string Card::printSpecialLine(const int line) const
{
	switch (line)
	{
		case 1:
			switch (this->_rank)
			{
				case Card::Rank::ACE: case Card::Rank::THREE: case Card::Rank::FIVE:
				case Card::Rank::SEVEN: case Card::Rank::NINE:
					return std::string("| :/\\: |");
				case Card::Rank::TWO: case Card::Rank::FOUR: case Card::Rank::SIX:
				case Card::Rank::EIGHT: 
					return std::string("| :(): |");
				case Card::Rank::TEN:
				default:
					return std::string("|  //  |");
			}
			break;
		default:
			switch (this->_rank)
			{
				case Card::Rank::ACE:
					return std::string("| :\\/: |");
				case Card::Rank::THREE: case Card::Rank::FIVE:
				case Card::Rank::SEVEN: case Card::Rank::NINE:
					return std::string("| (__) |");
				case Card::Rank::TWO: case Card::Rank::FOUR: case Card::Rank::SIX:
				case Card::Rank::EIGHT:
					return std::string("| ()() |");
				case Card::Rank::TEN:
				default:
					return std::string("|  //  |");
			}
			break;
	}
}
