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

	// ȡ����
	unsigned int money() const;
	PlayerStatus player_status() const;
	int hand_points() const;

	// �溯��
	Player& set_money(const unsigned int money);		// ֱ����������˻����
	Player& set_player_status(const PlayerStatus ps);	// ����������

	// һ�㹦�ܺ���
	Player& ChangePlayerStatus(const PlayerStatus ps);	// �ı�������
	Player& CallForACard(const Card& card);				// Ҫһ����
	unsigned int Raise(const unsigned int money);		// ��ע
	std::string DisplayHandCards() const;				// չʾ�����������
	std::string DisplayHandPoints() const;				// չʾ�����Ƶĵ���

private:
	PlayerStatus _player_status;						// ������
	unsigned int _money = 0;							// �����Ǯ���˻���
	std::vector<Card> _hand_cards;						// �������
	int _hand_points;									// �����Ƶ��ܻ���

	static const unsigned int MAX_MONEY = 100000000U;	// ����� 1 ��Ԫ

	// ��麯��
	unsigned int CheckMoney(const unsigned int money) const;	// �����������ڹ��캯����ʼ���б��飩

	// ˽�й��ܺ���
	Player& CalculateHandPoints();
};

