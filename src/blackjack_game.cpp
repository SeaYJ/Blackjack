#include "blackjack_game.h"

const std::string BlackjackGame::_kMarginLeft = std::string(10, ' ');

BlackjackGame::BlackjackGame()
{
	// ��ȡ��׼������
	_h_console_input = GetStdHandle(STD_INPUT_HANDLE);
	if (_h_console_input == INVALID_HANDLE_VALUE) {
		throw std::runtime_error("Error: Unable to get console input handle.");
	}

	// ��������ģʽ��ʹ֮�ܹ����ռ����¼�
	DWORD mode;
	GetConsoleMode(_h_console_input, &mode);
	SetConsoleMode(_h_console_input, mode | ENABLE_WINDOW_INPUT);

	// ��ʼ����ر���
	memset(_input_buffer, 0, sizeof(_input_buffer));
	_num_events_read = 0;
	_deck = Deck();	// ��ʼ���ƶѣ�˳��ģ�
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
		// ��ȡ�����¼�
		if (!ReadConsoleInput(_h_console_input, _input_buffer, 128, &_num_events_read)) {
			throw std::runtime_error("Error: Unable to read console input.");
			return (*this);
		}

		// ����ÿһ�������¼�
		for (DWORD i = 0; i < _num_events_read; ++i) {
			if (_input_buffer[i].EventType == KEY_EVENT && _input_buffer[i].Event.KeyEvent.bKeyDown) {
				// ��鰴�µļ���������Ӧ����Ӧ
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
	// ���֮ǰ�ļ����¼�
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
			throw std::runtime_error("Please select an option.");	// ����������ᴥ��
			break;
	}

	return (*this);
}

BlackjackGame& BlackjackGame::StartNewGame()
{
	this->ClearConsole();

	// ��ȡ��������Ĭ�Ͻ�ɫ
	std::string name_buffer;
	std::cout << "Enter your name: ";
	std::cin >> name_buffer;
	_active_player = Player(name_buffer, 100U, Player::PlayerStatus::AVERAGE_PLAYER);

	// ��ʾ��ӭ�ʺ���
	this->ClearConsole();
	this->CoutGameWelcomeMsg(10);// ��Ϸ��ӭ����

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
	// �����˻�
	Player dealer_adv("Dealer", 100000000, Player::PlayerStatus::ADVANCED_PLAYER);
	_opposing_players.push_back(dealer_adv);

	// �����ʼ��ע
	try {
		_player_bet_records[_active_player] = _active_player.Raise(MIN_BET);
	}
	catch (const std::exception&) {
		ClearConsole();
		CoutGameOverMsg();
		std::cout << "\nI'm sorry! You have lost all of your money!\n";
		exit(0);
	}

	// ������ʼ��ע
	for (std::vector<Player>::iterator op = _opposing_players.begin(); op != _opposing_players.end(); op++) {
		// ���������
		std::random_device rd;  //���ڻ������
		std::mt19937 gen(rd()); //������豸��Ϊ���ӣ���ʼ��Mersenne Twister������

		// ����ֲ���Χ
		std::uniform_int_distribution<> distrib(MIN_BET, 100);

		// ���������
		int random_bet = distrib(gen);
		_player_bet_records[(*op)] = (*op).Raise(random_bet);
	}

	return (*this);
}

BlackjackGame& BlackjackGame::ShowBettingInterface()
{
	this->ClearConsole();
	this->CoutGameHeader();

	// ����ȼ���� mw = min_width => ȷ��������ʾ��Ȳ���������²����۵���ʾ����
	int mw_money = static_cast<int>(std::log10(Player::MAX_MONEY) + 1);
	int mw_name = Player::MAX_NAME_LENGTH;
	int width = (mw_money > mw_name ? mw_money : mw_name);

	// �����ע���ʽ����
	std::cout << "\n" << _kMarginLeft
		<< cyan << "Name: " << std::left << std::setw(width) << std::setfill(' ') << _active_player.name() << " " << def
		<< magenta << "Bet: " << std::left << std::setw(width) << std::setfill(' ') << _player_bet_records[_active_player] << " " << def
		<< green << "Money: " << std::left << std::setw(width) << std::setfill(' ') << _active_player.money() << "\n" << def;

	// ���������ע���
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
		// ��ȡ�����¼�
		if (!ReadConsoleInput(_h_console_input, _input_buffer, 128, &_num_events_read)) {
			throw std::runtime_error("Error: Unable to read console input.");
		}

		// ����ÿһ�������¼�
		for (DWORD i = 0; i < _num_events_read; ++i) {
			if (_input_buffer[i].EventType == KEY_EVENT && _input_buffer[i].Event.KeyEvent.bKeyDown) {

				// pm => player money
				// pb => player bet
				unsigned int pm = _active_player.money();
				unsigned int pb = _player_bet_records[_active_player];

				// ��鰴�µļ���������Ӧ����Ӧ
				switch (_input_buffer[i].Event.KeyEvent.wVirtualKeyCode) {
					case VK_RETURN:
						return Duel();
					case 'A':
						// ������Ǯ�Ƿ񹻼�ע��������ȡ�������ļ�ע
						if (pm < MIN_BET_INCREMENT) {
							break;
						}

						_player_bet_records[_active_player] += _active_player.Raise(MIN_BET_INCREMENT);
						for (std::vector<Player>::iterator op = _opposing_players.begin(); op != _opposing_players.end(); op++) {
							_player_bet_records[(*op)] += (*op).Raise(MIN_BET_INCREMENT);// ��Ҽӵ�Խ�࣬������Ҳ��ӵȽ���ע��
						}

						ShowBettingInterface();
						break;
					case 'D':
						// ���ʣ�µ�ע���Ƿ����������ע���������ھ�ȡ�������ļ�ע
						if (pb <= MIN_BET) {
							break;
						}

						_player_bet_records[_active_player] -= _active_player.LowerBet(MIN_BET_INCREMENT);
						for (std::vector<Player>::iterator op = _opposing_players.begin(); op != _opposing_players.end(); op++) {
							_player_bet_records[(*op)] -= (*op).LowerBet(MIN_BET_INCREMENT);// ��Ҽ���Խ�࣬������Ҳ���ٵȽ���ע��
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

	// ����Ӧ�ý���ǰ��ҷ������չʾ
	std::cout << _active_player.DisplayHandCP(false);

	std::cout << "Would you like to hit?\n"
		<< "[ A = Hit | Enter = Face-up Card ]\n";

	return (*this);
}

BlackjackGame& BlackjackGame::Duel()
{
	// ��ʼ����
	// ��ҷ�������
	_active_player.AddCard(_deck.DealCard());
	_active_player.AddCard(_deck.DealCard());

	// ���еĶ��ַ�������
	for (std::vector<Player>::iterator op = _opposing_players.begin(); op != _opposing_players.end(); op++) {
		(*op).AddCard(_deck.DealCard());
		(*op).AddCard(_deck.DealCard());

		// ���������ɻ����˵�Ҫ��
		RobotBehavior(*op);
	}

	ShowDuelInterface();

	this->ClearKeyboardBuffer();
	while (true) {
		// ��ȡ�����¼�
		if (!ReadConsoleInput(_h_console_input, _input_buffer, 128, &_num_events_read)) {
			throw std::runtime_error("Error: Unable to read console input.");
		}

		// ����ÿһ�������¼�
		for (DWORD i = 0; i < _num_events_read; ++i) {
			if (_input_buffer[i].EventType == KEY_EVENT && _input_buffer[i].Event.KeyEvent.bKeyDown) {
				// ��鰴�µļ���������Ӧ����Ӧ
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

						// ��������Զ�����
						if (_active_player.hand_points() > MAX_HAND_POINTS) {
							return DuelOver();
						}

						ShowDuelInterface();	// ����������Ϊ�˱�����Чˢ�ºʹ������������ᱻ���ǣ�
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
		if (robot.player_status() == Player::PlayerStatus::ADVANCED_PLAYER) {	// �߼����
			// �ȿ�̽��һ���Ʋ����������
			Card card = _deck.PeekNextCard();
			int total_points = card.points() + robot.hand_points();

			// ֻ�е�������������²Ż����Ҫ��
			if (total_points <= MAX_HAND_POINTS) {
				robot.AddCard(_deck.DealCard());
			}
			// �������Ҫ��
			else {
				break;
			}
		}
		else {	// �������
			int require_points = 20 - robot.hand_points();
			try {
				if (require_points >= static_cast<int>(Card::Rank::ACE) && require_points <= static_cast<int>(Card::Rank::KING)) {
					// ֱ�����ƶ���Ѱ���Լ���Ҫ����
					Card card = _deck.DealCard(static_cast<Card::Rank>(require_points));
					robot.AddCard(card);
				}
				else {
					break;	// û�з���Ҫ����ƣ��ͽ���Ҫ��
				}
			}
			catch (const std::exception&) {
				break;		// �Ҳ�����Ҫ���ƣ��ͽ���Ҫ��
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
	else {	// ��������ֱ����
		game_result = BlackjackGame::GameResult::LOSE;
	}

	unsigned int total_bets_amount = 0;
	for (std::map<Player, unsigned int>::iterator pbr = _player_bet_records.begin();
		pbr != _player_bet_records.end();
		pbr++) {
		total_bets_amount += pbr->second;
	}

	// ����ע��
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

	// ������ʾ
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

	_active_player.ClearCard();		// �������״̬
	_opposing_players.clear();		// ǰ������´���
	_deck.ResetDeck().Shuffle();	// �����ƶѲ�ϴ��
	_player_bet_records.clear();	// �������ע��¼

	return (*this);
}

BlackjackGame& BlackjackGame::SaveGame()
{
	// ����һ������ļ������󣬲����ļ�
	std::string file_name = _active_player.name() + ".dat";
	std::ofstream outFile(file_name, std::ios::binary);

	// ����ļ��Ƿ�ɹ���
	if (!outFile) {
		std::cerr << "Error opening file for writing." << std::endl;
		return (*this);
	}

	// д������
	_active_player.set_money(_active_player.money() + _player_bet_records[_active_player]);// �黹δ��ʼ�Ծ�����ע���
	_active_player.Save(outFile);

	// �ر��ļ�
	outFile.close();

	// ��ȡ����·��
	char full_path[MAX_PATH]; // ���ڴ洢����·���Ļ�����
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
	CHAR szFile[260] = { 0 };	// ���ڴ���ļ����Ļ�����
	OPENFILENAME ofn;			// OPENFILENAME�ṹ�����ڳ�ʼ���Ի���

	// ��ʼ��OPENFILENAME�ṹ��
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GetForegroundWindow();    // ��ȡ��ǰ����ڵľ��
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Data files\0*.dat\0"; // �����ļ�������
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL; // ���ó�ʼĿ¼��NULL��ʾ��ǰĿ¼
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// ��ʾ���ļ��Ի���
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
		// ��ȡ�����¼�
		if (!ReadConsoleInput(_h_console_input, _input_buffer, 128, &_num_events_read)) {
			throw std::runtime_error("Error: Unable to read console input.");
		}

		// ����ÿһ�������¼�
		for (DWORD i = 0; i < _num_events_read; ++i) {
			if (_input_buffer[i].EventType == KEY_EVENT && _input_buffer[i].Event.KeyEvent.bKeyDown) {
				// ��鰴�µļ���������Ӧ����Ӧ
				switch (_input_buffer[i].Event.KeyEvent.wVirtualKeyCode) {
					case VK_RETURN:
						// �˻����ĳ�ʼ�� & ��ǰ��ҽ�����ע
						HumanVsMachineInit().PlaceBet();
						break;
					default:
						break;
				}
			}
		}
	}
}

