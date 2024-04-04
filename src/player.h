#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <fstream>
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
		: _name(DEFAULT_NAME),
		_money(0U),
		_status(PlayerStatus::AVERAGE_PLAYER),
		_hand_points(0)
	{}

	explicit Player(std::string name)
		: _name(CheckName(name)),
		_money(0U),
		_status(PlayerStatus::AVERAGE_PLAYER),
		_hand_points(0)
	{}

	explicit Player(unsigned int money)
		: _name(DEFAULT_NAME),
		_money(CheckMoney(money)),
		_status(PlayerStatus::AVERAGE_PLAYER),
		_hand_points(0)
	{}

	explicit Player(std::string name, unsigned int money)
		: _name(CheckName(name)),
		_money(CheckMoney(money)),
		_status(PlayerStatus::AVERAGE_PLAYER),
		_hand_points(0)
	{}

	explicit Player(PlayerStatus ps)
		: _name(DEFAULT_NAME),
		_money(0U),
		_status(ps),
		_hand_points(0)
	{}

	explicit Player(std::string name, PlayerStatus ps)
		: _name(CheckName(name)),
		_money(0U),
		_status(ps),
		_hand_points(0)
	{}

	explicit Player(unsigned int money, PlayerStatus ps)
		: _name(DEFAULT_NAME),
		_money(CheckMoney(money)),
		_status(ps),
		_hand_points(0)
	{}

	explicit Player(std::string name, unsigned int money, PlayerStatus ps)
		: _name(CheckName(name)),
		_money(CheckMoney(money)),
		_status(ps),
		_hand_points(0)
	{}

	// 取函数
	unsigned int money() const;
	PlayerStatus player_status() const;
	int hand_points() const;
	std::string name() const;
	int hand_size() const;								// 玩家手中牌的数量

	// 存函数
	Player& set_money(const unsigned int money);		// 直接设置玩家账户金额
	Player& set_status(const PlayerStatus ps);			// 设置玩家身份
	Player& set_name(const std::string name);			// 设置玩家姓名

	// 一般功能函数
	Player& AddCard(const Card& card);													// 要一张牌
	Player& ClearCard();																// 清除手中所有牌
	unsigned int Raise(const unsigned int money);										// 加注
	unsigned int LowerBet(const unsigned int money);									// 减注
	std::string DisplayHandCards(bool masked = false) const;							// 展示手里的所有牌
	std::string DisplayHandPoints(bool masked = false) const;							// 展示手里牌的点数
	std::string DisplayHandCP(bool masked = false, bool is_player_self = true) const;	// 展示手里的所有牌和点数
	Player& Save(std::ofstream& outFile);												// 保存数据到文件
	bool Load(std::ifstream& inFile);												// 读取数据

	static const std::string DEFAULT_NAME;				// 默认姓名
	static const unsigned int MIN_NAME_LENGTH = 1U;		// 名字最短长度
	static const unsigned int MAX_NAME_LENGTH = 10U;	// 名字最长长度
	static const unsigned int MAX_MONEY = 100000000U;	// 最大金额 1 亿元

	bool operator<(const Player& other) const;
	bool operator>(const Player& other) const;
private:
	std::string _name;									// 玩家姓名
	PlayerStatus _status;								// 玩家身份
	unsigned int _money = 0U;							// 手里的钱（账户金额）
	std::vector<Card> _hand_cards;						// 手里的牌
	int _hand_points;									// 手里牌的总积分

	// 检查函数
	std::string CheckName(const std::string name) const;		// 检查玩家姓名规范（1~10字符）
	unsigned int CheckMoney(const unsigned int money) const;	// 检查输入金额（用于构造函数初始化列表检查）

	// 私有功能函数
	Player& CalculateHandPoints();
};

#endif // !_PLAYER_H_

