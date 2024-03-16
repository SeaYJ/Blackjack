#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "card.h"

class Player
{
public:
	enum class PlayerStatus {
		AVERAGE_PLAYER = 0,
		ADVANCED_PLAYER,
		SUPER_PLAYER
	};

	explicit Player()
		: _money(0U),
		_player_status(PlayerStatus::AVERAGE_PLAYER),
		_hand_points(0)
	{}

	explicit Player(unsigned int money)
		: _money(CheckMoney(money)),
		_player_status(PlayerStatus::AVERAGE_PLAYER),
		_hand_points(0)
	{}

	explicit Player(PlayerStatus ps)
		: _money(0U),
		_player_status(ps),
		_hand_points(0)
	{}

	explicit Player(unsigned int money, PlayerStatus ps)
		: _money(CheckMoney(money)),
		_player_status(ps),
		_hand_points(0)
	{}

	// 取函数
	unsigned int money() const;
	PlayerStatus player_status() const;
	int hand_points() const;

	// 存函数
	Player& set_money(const unsigned int money);		// 直接设置玩家账户金额
	Player& set_player_status(const PlayerStatus ps);	// 设置玩家身份

	// 一般功能函数
	Player& ChangePlayerStatus(const PlayerStatus ps);	// 改变玩家身份
	Player& CallForACard(const Card& card);				// 要一张牌
	unsigned int Raise(const unsigned int money);		// 加注
	std::string DisplayHandCards() const;				// 展示手里的所有牌
	std::string DisplayHandPoints() const;				// 展示手里牌的点数

private:
	PlayerStatus _player_status;						// 玩家身份
	unsigned int _money = 0;							// 手里的钱（账户金额）
	std::vector<Card> _hand_cards;						// 手里的牌
	int _hand_points;									// 手里牌的总积分

	static const unsigned int MAX_MONEY = 100000000U;	// 最大金额 1 亿元

	// 检查函数
	unsigned int CheckMoney(const unsigned int money) const;	// 检查输入金额（用于构造函数初始化列表检查）

	// 私有功能函数
	Player& CalculateHandPoints();
};

