#include "blackjack_game.h"

const std::string BlackjackGame::_kMarginLeft = std::string(10, ' ');

BlackjackGame::BlackjackGame()
{
	// 获取标准输入句柄
	_h_console_input = GetStdHandle(STD_INPUT_HANDLE);
	if (_h_console_input == INVALID_HANDLE_VALUE) {
		throw std::runtime_error("Error: Unable to get console input handle.");
	}

	// 设置输入模式，使之能够接收键盘事件
	DWORD mode;
	GetConsoleMode(_h_console_input, &mode);
	SetConsoleMode(_h_console_input, mode | ENABLE_WINDOW_INPUT);

	// 初始化相关变量
	memset(_input_buffer, 0, sizeof(_input_buffer));
	_num_events_read = 0;
	_deck = Deck();	// 初始化牌堆（顺序的）
}

BlackjackGame::~BlackjackGame()
{
}

BlackjackGame& BlackjackGame::LaunchGame()
{
	int selected_menu_item = 1;

	this->ClearConsole();
	this->CoutGameMainMenu(selected_menu_item);

	this->ClearKeyboardBuffer();
	while (true) {
		// 读取键盘事件
		if (!ReadConsoleInput(_h_console_input, _input_buffer, 128, &_num_events_read)) {
			throw std::runtime_error("Error: Unable to read console input.");
			return (*this);
		}

		// 处理每一个键盘事件
		for (DWORD i = 0; i < _num_events_read; ++i) {
			if (_input_buffer[i].EventType == KEY_EVENT && _input_buffer[i].Event.KeyEvent.bKeyDown) {
				// 检查按下的键并做出相应的响应
				switch (_input_buffer[i].Event.KeyEvent.wVirtualKeyCode) {
					case VK_RETURN:
						this->HandleGameMainMenuItemSelection(selected_menu_item);
						break;
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
						selected_menu_item = _input_buffer[i].Event.KeyEvent.wVirtualKeyCode - '0';
						this->ClearConsole();
						this->CoutGameMainMenu(selected_menu_item);
						break;
					default:
						break;
				}
			}
		}
	}

	return (*this);
}

void BlackjackGame::Typewriter(std::string str, int duration, ConsoleColor::Modifier color)
{
	for (int i = 0; i < str.length(); i++) {
		std::cout << color << str[i] << def;
		Sleep(duration);
	}
}

void BlackjackGame::ExitGame(int code)
{
	this->ClearConsole();
	this->CoutGameFarewellMsg();

	return exit(code);
}

void BlackjackGame::ClearKeyboardBuffer()
{
	// 清除之前的键盘事件
	FlushConsoleInputBuffer(_h_console_input);
}

BlackjackGame& BlackjackGame::ClearConsole()
{
	system("cls");

	return (*this);
}

BlackjackGame& BlackjackGame::CoutGameHeader()
{
	std::string game_header = R"(
    ____    ___                    __                             __         
   /\  _`\ /\_ \                  /\ \        __                 /\ \        
   \ \ \L\ \//\ \      __      ___\ \ \/'\   /\_\     __      ___\ \ \/'\    
    \ \  _ <'\ \ \   /'__`\   /'___\ \ , <   \/\ \  /'__`\   /'___\ \ , <    
     \ \ \L\ \\_\ \_/\ \L\.\_/\ \__/\ \ \\`\  \ \ \/\ \L\.\_/\ \__/\ \ \\`\  
      \ \____//\____\ \__/.\_\ \____\\ \_\ \_\_\ \ \ \__/.\_\ \____\\ \_\ \_\
       \/___/ \/____/\/__/\/_/\/____/ \/_/\/_/\ \_\ \/__/\/_/\/____/ \/_/\/_/
                                             \ \____/                        
                                              \/___/                         
)";

	std::cout << lightBlue << game_header << def;

	return (*this);
}

BlackjackGame& BlackjackGame::CoutGameWelcomeMsg(int duration)
{
	std::string welcome_msg = R"(
       __      __       .__                             ._.
      /  \    /  \ ____ |  |   ____  ____   _____   ____| |
      \   \/\/   // __ \|  | _/ ___\/  _ \ /     \_/ __ \ |
       \        /\  ___/|  |_\  \__(  <_> )  Y Y  \  ___/\|
        \__/\  /  \___  >____/\___  >____/|__|_|  /\___  >_
             \/       \/          \/            \/     \/\/
)";

	std::cout << lightYellow << welcome_msg << def;
	Sleep(duration);

	return (*this);
}

BlackjackGame& BlackjackGame::CoutGameWelcomeBackMsg()
{
	std::string welcomeback_msg = R"(
   __          __  _                            _                _    
   \ \        / / | |                          | |              | |   
    \ \  /\  / /__| | ___ ___  _ __ ___   ___  | |__   __ _  ___| | __
     \ \/  \/ / _ \ |/ __/ _ \| '_ ` _ \ / _ \ | '_ \ / _` |/ __| |/ /
      \  /\  /  __/ | (_| (_) | | | | | |  __/ | |_) | (_| | (__|   < 
       \/  \/ \___|_|\___\___/|_| |_| |_|\___| |_.__/ \__,_|\___|_|\_\
)";

	std::cout << lightYellow << welcomeback_msg << def;

	return (*this);
}

BlackjackGame& BlackjackGame::CoutGameFarewellMsg(int duration)
{
	std::string farewell_msg = R"(
        ________                  .______.               ._.
       /  _____/  ____   ____   __| _/\_ |__ ___.__. ____| |
      /   \  ___ /  _ \ /  _ \ / __ |  | __ <   |  |/ __ \ |
      \    \_\  (  <_> |  <_> ) /_/ |  | \_\ \___  \  ___/\|
       \______  /\____/ \____/\____ |  |___  / ____|\___  >_
              \/                   \/      \/\/         \/\/
)";

	std::cout << lightYellow << farewell_msg << def;
	Sleep(duration);

	return (*this);
}

BlackjackGame& BlackjackGame::CoutGameOutcome(GameResult gres)
{
	std::string win = R"(
  __  __               _       ___       __
  \ \/ /___  __  __   | |     / (_)___  / /
   \  / __ \/ / / /   | | /| / / / __ \/ / 
   / / /_/ / /_/ /    | |/ |/ / / / / /_/  
  /_/\____/\__,_/     |__/|__/_/_/ /_(_)   
)";

	std::string lose = R"(
  __  __               __                    __
  \ \/ /___  __  __   / /   ____  ________  / /
   \  / __ \/ / / /  / /   / __ \/ ___/ _ \/ / 
   / / /_/ / /_/ /  / /___/ /_/ (__  )  __/_/  
  /_/\____/\__,_/  /_____/\____/____/\___(_)   
)";

	std::string tie = R"(
      ______     _                  _______      __
     /  _/ /_   (_)____   ____ _   /_  __(_)__  / /
     / // __/  / / ___/  / __ `/    / / / / _ \/ / 
   _/ // /_   / (__  )  / /_/ /    / / / /  __/_/  
  /___/\__/  /_/____/   \__,_/    /_/ /_/\___(_)   
)";

	switch (gres)
	{
		case BlackjackGame::GameResult::LOSE:
			std::cout << red << lose << def;
			break;
		case BlackjackGame::GameResult::WIN:
			std::cout << green << win << def;
			break;
		case BlackjackGame::GameResult::TIE:
			std::cout << cyan << tie << def;
			break;
		default:
			throw std::runtime_error("Unknown error.");
			break;
	}

	return (*this);
}

BlackjackGame& BlackjackGame::CoutGameOverMsg()
{
	std::string gameover_msg = R"(
     _____                         ____                 
    / ____|                       / __ \                
   | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ 
   | | |_ |/ _` | '_ ` _ \ / _ \ | |  | \ \ / / _ \ '__|
   | |__| | (_| | | | | | |  __/ | |__| |\ V /  __/ |   
    \_____|\__,_|_| |_| |_|\___|  \____/  \_/ \___|_|   
)";
	std::cout << red << gameover_msg << def;

	return (*this);
}

BlackjackGame& BlackjackGame::CoutGameMainMenu(int selected_menu_item)
{
	this->CoutGameHeader();

	std::vector<std::string> menu_items = {
		"Start a New Game",
		"Load from Game",
		"How to Play",
		"Exit"
	};

	for (int i = 0; i < menu_items.size(); ++i) {
		std::cout << _kMarginLeft << lightMagenta << (selected_menu_item == i + 1 ? "* " : "") << def << i + 1 << " - " << menu_items[i] << "\n";
	}

	std::cout << "\nSelect and Enter!\n";
	std::cout << "[ ";
	for (int i = 0; i < menu_items.size(); ++i) {
		std::cout << i + 1 << (i == menu_items.size() - 1 ? "" : " | ");
	}
	std::cout << " | Enter ]\n";

	return (*this);
}

BlackjackGame& BlackjackGame::HandleGameMainMenuItemSelection(int selected_menu_item)
{
	switch (selected_menu_item) {
		case 1:
			this->StartNewGame();
			break;
		case 2:
			this->LoadGame();
			break;
		case 3:
			this->GameManual();
			break;
		case 4:
			this->ExitGame(0);
			break;
		default:
			throw std::runtime_error("Please select an option.");	// 正常情况不会触发
			break;
	}

	return (*this);
}

BlackjackGame& BlackjackGame::StartNewGame()
{
	this->ClearConsole();

	// 获取姓名创建默认角色
	std::string name_buffer;
	std::cout << "Enter your name: ";
	std::cin >> name_buffer;
	_active_player = Player(name_buffer, 100U, Player::PlayerStatus::AVERAGE_PLAYER);

	// 显示欢迎问候语
	this->ClearConsole();
	this->CoutGameWelcomeMsg(10);// 游戏欢迎界面

	std::stringstream introductory_greeting[3];
	introductory_greeting[0] << "\n\nHello, ";
	introductory_greeting[1] << cyan << _active_player.name() << def;
	introductory_greeting[2] << "!\n" << "Welcome to the Blackjack game hall...\n\n"
		<< "Now, let's get started! Please take your seat, take a deep breath, and prepare for the challenge.\n"
		<< "Remember, no matter the outcome, the most important thing is to enjoy the fun the game brings.\n\n"
		<< "Good luck, and may you return home with a big win today!\n\n\n";
	for (int i = 0; i < 3; i++) {
		if (i == 1) {
			std::cout << introductory_greeting[1].str();
		}
		else {
			this->Typewriter(introductory_greeting[i].str(), 5);
		}
	}

	std::cout << "[Enter] to continue!";

	BridgeNewAndImportGame();

	return (*this);
}

BlackjackGame& BlackjackGame::HumanVsMachineInit()
{
	// 创建人机
	Player dealer_adv("Dealer", 100000000, Player::PlayerStatus::ADVANCED_PLAYER);
	_opposing_players.push_back(dealer_adv);

	// 玩家起始下注
	try {
		_player_bet_records[_active_player] = _active_player.Raise(MIN_BET);
	}
	catch (const std::exception&) {
		ClearConsole();
		CoutGameOverMsg();
		std::cout << "\nI'm sorry! You have lost all of your money!\n";
		exit(0);
	}

	// 其他初始下注
	for (std::vector<Player>::iterator op = _opposing_players.begin(); op != _opposing_players.end(); op++) {
		// 随机数引擎
		std::random_device rd;  //用于获得种子
		std::mt19937 gen(rd()); //以随机设备作为种子，初始化Mersenne Twister生成器

		// 定义分布范围
		std::uniform_int_distribution<> distrib(MIN_BET, 100);

		// 生成随机数
		int random_bet = distrib(gen);
		_player_bet_records[(*op)] = (*op).Raise(random_bet);
	}

	return (*this);
}

BlackjackGame& BlackjackGame::ShowBettingInterface()
{
	this->ClearConsole();
	this->CoutGameHeader();

	// 输出等间距宽度 mw = min_width => 确保文字显示宽度不会过长导致不美观的显示问题
	int mw_money = static_cast<int>(std::log10(Player::MAX_MONEY) + 1);
	int mw_name = Player::MAX_NAME_LENGTH;
	int width = (mw_money > mw_name ? mw_money : mw_name);

	// 玩家下注及资金情况
	std::cout << "\n" << _kMarginLeft
		<< cyan << "Name: " << std::left << std::setw(width) << std::setfill(' ') << _active_player.name() << " " << def
		<< magenta << "Bet: " << std::left << std::setw(width) << std::setfill(' ') << _player_bet_records[_active_player] << " " << def
		<< green << "Money: " << std::left << std::setw(width) << std::setfill(' ') << _active_player.money() << "\n" << def;

	// 其他玩家下注情况
	for (std::vector<Player>::iterator op = _opposing_players.begin(); op != _opposing_players.end(); op++) {
		std::cout << _kMarginLeft
			<< cyan << "Name: " << std::left << std::setw(width) << std::setfill(' ') << (*op).name() << " " << def
			<< magenta << "Bet: " << std::left << std::setw(width) << std::setfill(' ') << _player_bet_records[(*op)] << " " << def
			<< green << "Money: " << std::left << std::setw(width) << std::setfill(' ') << (*op).money() << "\n" << def;
	}

	std::cout << "\nPlace your bet!\n"
		<< "[ A = Add | D = Decrease | Enter | Esc ]\n";

	return (*this);
}

BlackjackGame& BlackjackGame::PlaceBet()
{
	ShowBettingInterface();

	this->ClearKeyboardBuffer();
	while (true) {
		// 读取键盘事件
		if (!ReadConsoleInput(_h_console_input, _input_buffer, 128, &_num_events_read)) {
			throw std::runtime_error("Error: Unable to read console input.");
		}

		// 处理每一个键盘事件
		for (DWORD i = 0; i < _num_events_read; ++i) {
			if (_input_buffer[i].EventType == KEY_EVENT && _input_buffer[i].Event.KeyEvent.bKeyDown) {

				// pm => player money
				// pb => player bet
				unsigned int pm = _active_player.money();
				unsigned int pb = _player_bet_records[_active_player];

				// 检查按下的键并做出相应的响应
				switch (_input_buffer[i].Event.KeyEvent.wVirtualKeyCode) {
					case VK_RETURN:
						return Duel();
					case 'A':
						// 检查玩家钱是否够加注，不够就取消即将的加注
						if (pm < MIN_BET_INCREMENT) {
							break;
						}

						_player_bet_records[_active_player] += _active_player.Raise(MIN_BET_INCREMENT);
						for (std::vector<Player>::iterator op = _opposing_players.begin(); op != _opposing_players.end(); op++) {
							_player_bet_records[(*op)] += (*op).Raise(MIN_BET_INCREMENT);// 玩家加的越多，机器人也添加等金额的注金
						}

						ShowBettingInterface();
						break;
					case 'D':
						// 检查剩下的注金是否会低于最低下注，如果会低于就取消即将的减注
						if (pb <= MIN_BET) {
							break;
						}

						_player_bet_records[_active_player] -= _active_player.LowerBet(MIN_BET_INCREMENT);
						for (std::vector<Player>::iterator op = _opposing_players.begin(); op != _opposing_players.end(); op++) {
							_player_bet_records[(*op)] -= (*op).LowerBet(MIN_BET_INCREMENT);// 玩家减的越多，机器人也减少等金额的注金
						}

						ShowBettingInterface();
						break;
					case VK_ESCAPE:
						SaveGame();
						break;
					default:
						break;
				}
			}
		}
	}

	return (*this);
}

BlackjackGame& BlackjackGame::ShowDuelInterface()
{
	this->ClearConsole();

	for (std::vector<Player>::iterator op = _opposing_players.begin(); op != _opposing_players.end(); op++) {
		std::cout << (*op).DisplayHandCP(true);
	}

	// 这里应该将当前玩家放在最后展示
	std::cout << _active_player.DisplayHandCP(false);

	std::cout << "Would you like to hit?\n"
		<< "[ A = Hit | Enter = Face-up Card ]\n";

	return (*this);
}

BlackjackGame& BlackjackGame::Duel()
{
	// 初始发牌
	// 玩家发两张牌
	_active_player.AddCard(_deck.DealCard());
	_active_player.AddCard(_deck.DealCard());

	// 所有的对手发两张牌
	for (std::vector<Player>::iterator op = _opposing_players.begin(); op != _opposing_players.end(); op++) {
		(*op).AddCard(_deck.DealCard());
		(*op).AddCard(_deck.DealCard());

		// 在这里就完成机器人的要牌
		RobotBehavior(*op);
	}

	ShowDuelInterface();

	this->ClearKeyboardBuffer();
	while (true) {
		// 读取键盘事件
		if (!ReadConsoleInput(_h_console_input, _input_buffer, 128, &_num_events_read)) {
			throw std::runtime_error("Error: Unable to read console input.");
		}

		// 处理每一个键盘事件
		for (DWORD i = 0; i < _num_events_read; ++i) {
			if (_input_buffer[i].EventType == KEY_EVENT && _input_buffer[i].Event.KeyEvent.bKeyDown) {
				// 检查按下的键并做出相应的响应
				switch (_input_buffer[i].Event.KeyEvent.wVirtualKeyCode) {
					case VK_RETURN:
						return DuelOver();
					case 'A':
						if (_active_player.hand_size() < MAX_HAND_SIZE) {
							_active_player.AddCard(_deck.DealCard());
						}
						else {
							std::cout << "Players can hold a maximum of 5 cards! No more cards can be drawn.   [AnyKey]" << std::endl;
							int pause = _getch();
						}

						// 点数溢出自动结束
						if (_active_player.hand_points() > MAX_HAND_POINTS) {
							return DuelOver();
						}

						ShowDuelInterface();	// 放在这里是为了避免无效刷新和错误输出（否则会被覆盖）
						break;
					default:
						break;
				}
			}
		}
	}

	return (*this);
}

BlackjackGame& BlackjackGame::RobotBehavior(Player& robot)
{
	while (true) {
		if (robot.player_status() == Player::PlayerStatus::ADVANCED_PLAYER) {	// 高级玩家
			// 先窥探下一张牌并计算点数和
			Card card = _deck.PeekNextCard();
			int total_points = card.points() + robot.hand_points();

			// 只有点数不超的情况下才会进行要牌
			if (total_points <= MAX_HAND_POINTS) {
				robot.AddCard(_deck.DealCard());
			}
			// 否则结束要牌
			else {
				break;
			}
		}
		else {	// 超级玩家
			int require_points = 20 - robot.hand_points();
			try {
				if (require_points >= static_cast<int>(Card::Rank::ACE) && require_points <= static_cast<int>(Card::Rank::KING)) {
					// 直接在牌堆中寻找自己需要的牌
					Card card = _deck.DealCard(static_cast<Card::Rank>(require_points));
					robot.AddCard(card);
				}
				else {
					break;	// 没有符合要求的牌，就结束要牌
				}
			}
			catch (const std::exception&) {
				break;		// 找不到需要的牌，就结束要牌
			}
		}
	}

	return (*this);
}

BlackjackGame& BlackjackGame::DuelOver()
{
	this->ClearConsole();

	BlackjackGame::GameResult game_result = BlackjackGame::GameResult::WIN;
	int num_players_in_draw = 0;
	if (_active_player.hand_points() <= BlackjackGame::MAX_HAND_POINTS) {
		for (std::vector<Player>::iterator op = _opposing_players.begin();
			op != _opposing_players.end();
			op++) {
			if ((*op).hand_points() > _active_player.hand_points()) {
				game_result = BlackjackGame::GameResult::LOSE;
				break;
			}
			else if ((*op).hand_points() == _active_player.hand_points()) {
				game_result = BlackjackGame::GameResult::TIE;
				num_players_in_draw += 1;
			}
		}
	}
	else {	// 点数超了直接输
		game_result = BlackjackGame::GameResult::LOSE;
	}

	unsigned int total_bets_amount = 0;
	for (std::map<Player, unsigned int>::iterator pbr = _player_bet_records.begin();
		pbr != _player_bet_records.end();
		pbr++) {
		total_bets_amount += pbr->second;
	}

	// 处理注金
	unsigned int money_buf = _active_player.money();
	if (game_result == BlackjackGame::GameResult::WIN) {
		money_buf += total_bets_amount;
	}
	else if (game_result == BlackjackGame::GameResult::TIE) {
		money_buf += (total_bets_amount / num_players_in_draw);
	}
	else {
		money_buf;
	}
	_active_player.set_money((money_buf > Player::MAX_MONEY ? Player::MAX_MONEY : money_buf));

	// 界面显示
	std::cout << "==================================================\n";
	CoutGameOutcome(game_result);
	std::cout << "\n==================================================\n\n";

	for (std::vector<Player>::iterator op = _opposing_players.begin(); op != _opposing_players.end(); op++) {
		std::cout << (*op).DisplayHandCards(false);
	}

	std::cout << _active_player.DisplayHandCards(false);

	std::cout << "\n";
	if (game_result == BlackjackGame::GameResult::WIN) {
		std::cout << "Earn " << green << total_bets_amount - _player_bet_records[_active_player] << def;
	}
	else if (game_result == BlackjackGame::GameResult::TIE) {
		std::cout << "Earn " << green << (total_bets_amount / num_players_in_draw) - _player_bet_records[_active_player] << def;
	}
	else {
		std::cout << "Lost " << red << _player_bet_records[_active_player] << def;
	}
	std::cout << " RMB and press [Enter] key to continue...";

	_active_player.ClearCard();		// 重置玩家状态
	_opposing_players.clear();		// 前面会重新创建
	_deck.ResetDeck().Shuffle();	// 重置牌堆并洗牌
	_player_bet_records.clear();	// 清除旧下注记录

	return (*this);
}

BlackjackGame& BlackjackGame::SaveGame()
{
	// 创建一个输出文件流对象，并打开文件
	std::string file_name = _active_player.name() + ".dat";
	std::ofstream outFile(file_name, std::ios::binary);

	// 检查文件是否成功打开
	if (!outFile) {
		std::cerr << "Error opening file for writing." << std::endl;
		return (*this);
	}

	// 写入数据
	_active_player.set_money(_active_player.money() + _player_bet_records[_active_player]);// 归还未开始对决的下注金额
	_active_player.Save(outFile);

	// 关闭文件
	outFile.close();

	// 获取绝对路径
	char full_path[MAX_PATH]; // 用于存储绝对路径的缓冲区
	DWORD length = GetFullPathNameA(file_name.c_str(), MAX_PATH, full_path, NULL);

	if (length == 0) {
		std::cerr << "Failed to get full path." << std::endl;
		return (*this);
	}

	this->ClearConsole();
	std::cout << "The game has been saved for you! The file name is: \n"
		<< darkGray << "[" << file_name << "]\n" << def
		<< "And its path is: \n"
		<< darkGray << "[" << full_path << "]\n" << def;
	CoutGameFarewellMsg(800);
	exit(0);

	return (*this);
}

BlackjackGame& BlackjackGame::LoadGame()
{
	std::string filePath;
	if (OpenFileDialog(filePath)) {
		std::cout << "Loading file: " << darkGray << filePath << def << " ";
		Typewriter(".", 1000);
		Typewriter("....", 300);
		Typewriter(".", 600);

		std::ifstream inFile(filePath, std::ios::binary);
		if (!inFile) {
			std::cerr << "Error opening file for reading." << std::endl;
			return (*this);
		}

		if (_active_player.Load(inFile)) {
			ClearConsole();
			CoutGameWelcomeBackMsg();

			std::string welcomeback_info = "\n\nWelcome back, esteemed veteran player! \n\nIt's a pleasure to have you join us once again at the Blackjack table. Your return adds more excitement to the game. \n\nHere, every round is full of possibilities, and every choice matters. May your strategies be more refined and your luck ever in your favor. \n\nLet's set sail again and enjoy this contest of wit and fortune. \n\nWishing you a streak of good fortune and a victory that brings home the bacon!";
			Typewriter(welcomeback_info);

			std::cout << "\n\n[Enter] to continue!\n";

			BridgeNewAndImportGame();

		}
		else {
			std::cerr << "Failed to load player." << std::endl;
		}
	}
	else {
		std::cout << "No file selected or dialog cancelled." << std::endl;
	}

	return (*this);
}

BlackjackGame& BlackjackGame::GameManual()
{
	this->ClearConsole();
	std::stringstream manual;

	manual << R"(
In the game of 21-point poker, you will take on the role of a daring and meticulous gambler, navigating between the blackjack tables in the casino.

First comes the betting, where you can choose your bet amount. Once the bet is successful, the cards are dealt. You start with only two cards, and you can choose to either take more cards or end the round by comparing points. Of course, you can't have more than )" << lightRed << R"(5 cards)" << def << R"( in your hand. Lastly, if the total points of your hand )" << lightRed << R"(exceed 21)" << def << R"(, unfortunately, you will automatically lose the game.

Additional notes:
    - Poker cards )" << lightYellow << R"(1)" << def << R"( to )" << lightYellow << R"(X)" << def << R"( represent )" << darkGray << R"(1)" << def << R"( to )" << darkGray << R"(10)" << def << R"( points respectively.
    - Poker cards )" << lightYellow << R"(J, Q, K)" << def << R"( each represent )" << darkGray << R"(5, 5, 6)" << def << R"( points (half the face value rounded down).

Author: SeaYJ
Blog: )" << lightBlue << R"(https://www.seayj.cn)" << def << R"(
Github Repository: )" << lightBlue << R"(https://github.com/SeaYJ/Blackjack)" << def << R"(

[AnyKey] to continue!)";

	std::cout << manual.str();

	int pause = _getch();
	this->ClearConsole();
	this->CoutGameMainMenu(3);

	return (*this);
}

bool BlackjackGame::OpenFileDialog(std::string& outFilePath)
{
	CHAR szFile[260] = { 0 };	// 用于存放文件名的缓冲区
	OPENFILENAME ofn;			// OPENFILENAME结构体用于初始化对话框

	// 初始化OPENFILENAME结构体
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GetForegroundWindow();    // 获取当前活动窗口的句柄
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Data files\0*.dat\0"; // 设置文件过滤器
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL; // 设置初始目录，NULL表示当前目录
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// 显示打开文件对话框
	if (GetOpenFileName(&ofn) == TRUE) {
		outFilePath = szFile;
		return true;
	}
	return false;
}

void BlackjackGame::BridgeNewAndImportGame()
{
	this->ClearKeyboardBuffer();
	while (true) {
		// 读取键盘事件
		if (!ReadConsoleInput(_h_console_input, _input_buffer, 128, &_num_events_read)) {
			throw std::runtime_error("Error: Unable to read console input.");
		}

		// 处理每一个键盘事件
		for (DWORD i = 0; i < _num_events_read; ++i) {
			if (_input_buffer[i].EventType == KEY_EVENT && _input_buffer[i].Event.KeyEvent.bKeyDown) {
				// 检查按下的键并做出相应的响应
				switch (_input_buffer[i].Event.KeyEvent.wVirtualKeyCode) {
					case VK_RETURN:
						// 人机对弈初始化 & 当前玩家进行下注
						HumanVsMachineInit().PlaceBet();
						break;
					default:
						break;
				}
			}
		}
	}
}

