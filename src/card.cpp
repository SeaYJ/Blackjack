#include "card.h"

const Card::Rank Card::rank() const
{
	return _kRank;
}

const std::string Card::symbol() const
{
	return _kSymbol;
}

const int Card::points() const
{
	return _kPoints;
}

std::string Card::display(const int line) const
{
	// 避免字符串的多次拼接带来的性能消耗
	std::stringstream ss;

	switch (line) {
		case 0: ss << ".------."; break;
		case 1: ss << "|" << (this->_kSymbol) << ".--. |"; break;
		case 2: ss << (this->printSpecialLine(1)); break;
		case 3: ss << (this->printSpecialLine(2)); break;
		case 4: ss << "| '--'" << (this->_kSymbol) << "|"; break;
		case 5: ss << "`------'"; break;
		default:ss << ""; break;
	}

	return ss.str();
}

std::string Card::display() const
{
	// 避免字符串的多次拼接带来的性能消耗
	std::stringstream ss;

	for (int i = 0; i < 6; i++) {
		ss << display(i) << "\n";
	}

	return ss.str();
}

std::string Card::printSpecialLine(const int line) const
{
	switch (line)
	{
		case 1:
			switch (this->_kRank)
			{
				case Card::Rank::ACE: case Card::Rank::THREE: case Card::Rank::FIVE:
				case Card::Rank::SEVEN: case Card::Rank::NINE:
					return std::string("| :/\\: |");
					break;
				case Card::Rank::TWO: case Card::Rank::FOUR: case Card::Rank::SIX:
				case Card::Rank::EIGHT: case Card::Rank::TEN:
					return std::string("| :(): |");
					break;
				default:
					return std::string("|  //  |");
					break;
			}
			break;
		default:
			switch (this->_kRank)
			{
				case Card::Rank::ACE:
					return std::string("| :\\/: |");
				case Card::Rank::THREE: case Card::Rank::FIVE:
				case Card::Rank::SEVEN: case Card::Rank::NINE:
					return std::string("| (__) |");
				case Card::Rank::TWO: case Card::Rank::FOUR: case Card::Rank::SIX:
				case Card::Rank::EIGHT: case Card::Rank::TEN:
					return std::string("| ()() |");
				default:
					return std::string("|  //  |");
			}
			break;
	}
}
