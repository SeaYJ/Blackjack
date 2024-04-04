#pragma once

#ifndef _BLACKJACK_GAME_H_
#define _BLACKJACK_GAME_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <iomanip>
#include <random>
#include <conio.h>
#include <Windows.h>
#include <commdlg.h> // ����ͨ�öԻ������ͽṹ��Ķ���
#include "deck.h"
#include "player.h"
#include "console_color.h"

class BlackjackGame
{
public:
	enum class GameResult {
		LOSE = 0,
		WIN = 1,
		TIE = 2
	};

	explicit BlackjackGame();
	~BlackjackGame();

	BlackjackGame& LaunchGame();				// ��ʾ��Ϸ���˵�
	void Typewriter(std::string str,
		int duration = 10,
		ConsoleColor::Modifier color = def
	);											// ���ֻ�
private:
	HANDLE _h_console_input;					// ����̨���
	INPUT_RECORD _input_buffer[128];			// �����¼�������
	DWORD _num_events_read;						// �����¼�����

	static const unsigned int MIN_BET = 5U;				// ��С��ע���
	static const unsigned int MIN_BET_INCREMENT = 5U;	// ��С����
	static const unsigned int MAX_HAND_SIZE = 5U;		// ��ҵ�����������������಻�������������ƣ�
	static const unsigned int MAX_HAND_POINTS = 21U;		// ���������������

	static const std::string _kMarginLeft;				// ���˵����� Margin
	Player _active_player;								// �����Ϣ
	std::vector<Player> _opposing_players;				// �������
	Deck _deck;											// �ƶ�
	std::map<Player, unsigned int> _player_bet_records;	// �������ע��Ӧ��¼

	void ClearKeyboardBuffer();												// ��������¼�������
	void ExitGame(int code);												// �˳���Ϸ����
	BlackjackGame& ClearConsole();											// �������̨����
	BlackjackGame& CoutGameHeader();										// �����Ϸ����
	BlackjackGame& CoutGameWelcomeMsg(int duration = 800);					// �����Ϸ��ӭ��
	BlackjackGame& CoutGameWelcomeBackMsg();								// �����Ϸ��ӭ������
	BlackjackGame& CoutGameFarewellMsg(int duration = 400);					// �����Ϸ�����
	BlackjackGame& CoutGameOutcome(GameResult gres);						// �����Ϸ���
	BlackjackGame& CoutGameOverMsg();										// �����Ϸ������
	BlackjackGame& CoutGameMainMenu(int selected_menu_item = 1);			// �����Ϸ���˵�
	BlackjackGame& HandleGameMainMenuItemSelection(int selected_menu_item);	// ������Ϸ���˵�ѡ��

	BlackjackGame& StartNewGame();				// ��ʼ����Ϸ
	BlackjackGame& HumanVsMachineInit();		// �˻�����
	BlackjackGame& ShowBettingInterface();		// �¶�ע����(���˻��õ�����ĵ���ˢ��)
	BlackjackGame& PlaceBet();					// ��ע����
	BlackjackGame& ShowDuelInterface();			// ��ʾ���Ľ���(���˻��õ�����ĵ���ˢ��)
	BlackjackGame& Duel();						// ���Ľ���
	BlackjackGame& RobotBehavior(Player& robot);// ��������Ϊ�߼�
	BlackjackGame& DuelOver();					// �Ծֽ���


	BlackjackGame& SaveGame();			// ������Ϸ
	BlackjackGame& LoadGame();			// �������Ϸ
	BlackjackGame& GameManual();		// ��Ϸ˵��

	bool OpenFileDialog(std::string& outFilePath);
	void BridgeNewAndImportGame();		// ��Ϸ�߼��ؼ���
};

#endif // !_BLACKJACK_GAME_H_
