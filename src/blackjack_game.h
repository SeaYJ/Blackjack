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
#include <commdlg.h> // 包含通用对话框函数和结构体的定义
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

	BlackjackGame& LaunchGame();				// 显示游戏主菜单
	void Typewriter(std::string str,
		int duration = 10,
		ConsoleColor::Modifier color = def
	);											// 打字机
private:
	HANDLE _h_console_input;					// 控制台句柄
	INPUT_RECORD _input_buffer[128];			// 键盘事件缓冲区
	DWORD _num_events_read;						// 键盘事件个数

	static const unsigned int MIN_BET = 5U;				// 最小下注额度
	static const unsigned int MIN_BET_INCREMENT = 5U;	// 最小增额
	static const unsigned int MAX_HAND_SIZE = 5U;		// 玩家的最大持牌数（手中最多不超过此数量的牌）
	static const unsigned int MAX_HAND_POINTS = 21U;		// 玩家手中最大点数和

	static const std::string _kMarginLeft;				// “菜单”左 Margin
	Player _active_player;								// 玩家信息
	std::vector<Player> _opposing_players;				// 对手玩家
	Deck _deck;											// 牌堆
	std::map<Player, unsigned int> _player_bet_records;	// 玩家与下注对应记录

	void ClearKeyboardBuffer();												// 清除键盘事件缓冲区
	void ExitGame(int code);												// 退出游戏程序
	BlackjackGame& ClearConsole();											// 清除控制台内容
	BlackjackGame& CoutGameHeader();										// 输出游戏标题
	BlackjackGame& CoutGameWelcomeMsg(int duration = 800);					// 输出游戏欢迎语
	BlackjackGame& CoutGameWelcomeBackMsg();								// 输出游戏欢迎回来语
	BlackjackGame& CoutGameFarewellMsg(int duration = 400);					// 输出游戏离别语
	BlackjackGame& CoutGameOutcome(GameResult gres);						// 输出游戏结果
	BlackjackGame& CoutGameOverMsg();										// 输出游戏结束语
	BlackjackGame& CoutGameMainMenu(int selected_menu_item = 1);			// 输出游戏主菜单
	BlackjackGame& HandleGameMainMenuItemSelection(int selected_menu_item);	// 处理游戏主菜单选项

	BlackjackGame& StartNewGame();				// 开始新游戏
	BlackjackGame& HumanVsMachineInit();		// 人机对弈
	BlackjackGame& ShowBettingInterface();		// 下赌注界面(多人会用到界面的单独刷新)
	BlackjackGame& PlaceBet();					// 下注进程
	BlackjackGame& ShowDuelInterface();			// 显示对弈界面(多人会用到界面的单独刷新)
	BlackjackGame& Duel();						// 对弈进程
	BlackjackGame& RobotBehavior(Player& robot);// 机器人行为逻辑
	BlackjackGame& DuelOver();					// 对局结束


	BlackjackGame& SaveGame();			// 保存游戏
	BlackjackGame& LoadGame();			// 导入旧游戏
	BlackjackGame& GameManual();		// 游戏说明

	bool OpenFileDialog(std::string& outFilePath);
	void BridgeNewAndImportGame();		// 游戏逻辑关键桥
};

#endif // !_BLACKJACK_GAME_H_
