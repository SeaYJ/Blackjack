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

	// ȡ����
	unsigned int money() const;
	PlayerStatus player_status() const;
	int hand_points() const;
	std::string name() const;
	int hand_size() const;								// ��������Ƶ�����

	// �溯��
	Player& set_money(const unsigned int money);		// ֱ����������˻����
	Player& set_status(const PlayerStatus ps);			// ����������
	Player& set_name(const std::string name);			// �����������

	// һ�㹦�ܺ���
	Player& AddCard(const Card& card);													// Ҫһ����
	Player& ClearCard();																// �������������
	unsigned int Raise(const unsigned int money);										// ��ע
	unsigned int LowerBet(const unsigned int money);									// ��ע
	std::string DisplayHandCards(bool masked = false) const;							// չʾ�����������
	std::string DisplayHandPoints(bool masked = false) const;							// չʾ�����Ƶĵ���
	std::string DisplayHandCP(bool masked = false, bool is_player_self = true) const;	// չʾ����������ƺ͵���
	Player& Save(std::ofstream& outFile);												// �������ݵ��ļ�
	bool Load(std::ifstream& inFile);												// ��ȡ����

	static const std::string DEFAULT_NAME;				// Ĭ������
	static const unsigned int MIN_NAME_LENGTH = 1U;		// ������̳���
	static const unsigned int MAX_NAME_LENGTH = 10U;	// ���������
	static const unsigned int MAX_MONEY = 100000000U;	// ����� 1 ��Ԫ

	bool operator<(const Player& other) const;
	bool operator>(const Player& other) const;
private:
	std::string _name;									// �������
	PlayerStatus _status;								// ������
	unsigned int _money = 0U;							// �����Ǯ���˻���
	std::vector<Card> _hand_cards;						// �������
	int _hand_points;									// �����Ƶ��ܻ���

	// ��麯��
	std::string CheckName(const std::string name) const;		// �����������淶��1~10�ַ���
	unsigned int CheckMoney(const unsigned int money) const;	// �����������ڹ��캯����ʼ���б��飩

	// ˽�й��ܺ���
	Player& CalculateHandPoints();
};

#endif // !_PLAYER_H_

