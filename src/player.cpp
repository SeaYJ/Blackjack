#include "player.h"

unsigned int Player::money() const
{
	return _money;
}

Player::PlayerStatus Player::player_status() const
{
	return _player_status;
}

int Player::hand_points() const
{
	return _hand_points;
}

Player& Player::set_money(const unsigned int money)
{
	if (money > MAX_MONEY) {
		throw std::invalid_argument("The 'money' must not exceed "
			+ std::to_string(MAX_MONEY) +
			" RMB.");
	}

	_money = money;

	return (*this);
}

Player& Player::set_player_status(const PlayerStatus ps)
{
	_player_status = ps;

	return (*this);
}

Player& Player::ChangePlayerStatus(const PlayerStatus ps)
{
	_player_status = ps;
	return (*this);
}

Player& Player::CallForACard(const Card& card)
{
	_hand_cards.push_back(card);

	this->CalculateHandPoints();	// 重新计算点数

	return (*this);
}

unsigned int Player::Raise(const unsigned int money)
{
	if (_money < money) {
		throw std::invalid_argument("Insufficient account balance. The account balance is "
			+ std::to_string(_money)
			+ " RMB, which is not enough to make a payment of "
			+ std::to_string(money)
			+ " RMB.");
	}

	_money -= money;

	return money;
}

std::string Player::DisplayHandCards() const
{
	std::stringstream ss;

	for (int row = 0; row < 6; row++) {
		for (int i = 0; i < _hand_cards.size(); i++) {
			ss << _hand_cards[i].Display(row) << " ";
		}
		ss << "\n";
	}

	return ss.str();
}

std::string Player::DisplayHandPoints() const
{
	std::stringstream ss;

	if (_hand_points > 21) {
		ss << red;		// 溢出用红色
	}
	else {
		ss << green;	// 未溢出用绿色
	}

	ss << std::to_string(_hand_points) << def;

	return ss.str();
}

unsigned int Player::CheckMoney(const unsigned int money) const
{
	if (money < 0U || money > MAX_MONEY) {
		throw std::invalid_argument("Invalid account amount setting. The balance must not be less than 0 RMB and cannot exceed "
			+ std::to_string(MAX_MONEY)
			+ " RMB.");
	}

	return money;
}

Player& Player::CalculateHandPoints()
{
	_hand_points = 0;	// 必须先初始化为 0，重新计算手中点数

	for (std::vector<Card>::iterator it = _hand_cards.begin(); it != _hand_cards.end(); it++) {
		int cardPoint = (*it).points();
		_hand_points += cardPoint;
	}
	
	return (*this);
}


