#include "main.h"
#include "card.h"
#include "console_color.h"
#include "deck.h"
#include "player.h"
#include "blackjack_game.h"

//#define M_DEBUG

int main() {

#ifdef M_DEBUG
	Debug();
#endif // M_DEBUG

	BlackjackGame game;

	game.LaunchGame();

	//system("cls");

	//Deck deck;

	//// 游戏开始
	//char choice;
	//do {
	//	system("cls");
	//	deck.ResetDeck();	// 每轮重置牌堆
	//	deck.Shuffle();		// 每轮重新洗牌

	//	Player player(1000U, Player::PlayerStatus::AVERAGE_PLAYER);
	//	Player dealer(1000000U, Player::PlayerStatus::ADVANCED_PLAYER);

	//	// 庄家获得两张牌
	//	dealer.AddCard(deck.DealCard());
	//	dealer.AddCard(deck.DealCard());

	//	// 玩家获得两张牌
	//	player.AddCard(deck.DealCard());
	//	player.AddCard(deck.DealCard());

	//	cout << magenta << "首轮发牌\n\n\n" << def;

	//	// 展示界面
	//	cout << cyan
	//		<< "===== 庄家 =====\n"
	//		<< dealer.DisplayHandCards(true)
	//		<< "庄家点数: " << dealer.DisplayHandPoints(true) << "\n"
	//		<< cyan << "===== ==== =====\n\n\n" << def;
	//	cout << blue
	//		<< "===== 玩家 =====\n"
	//		<< player.DisplayHandCards(false)
	//		<< "玩家点数: " << player.DisplayHandPoints(false) << "\n"
	//		<< blue << "===== ==== =====\n\n\n" << def;

	//	cout << "[请按 Y 继续]:";
	//	do {
	//		choice = _getch();
	//	} while (choice != 'y' && choice != 'Y');

	//	system("cls");

	//	// 庄家是否要牌(这里默认为高级玩家/与玩家的高级玩家略有不同[不用输入密码])
	//	cout << magenta << "庄家要牌阶段...\n" << def;
	//	if (dealer.player_status() == Player::PlayerStatus::ADVANCED_PLAYER) {
	//		while (true) {	// 高级玩家(庄家无密码)自动要牌，并保证不超过 21 点
	//			Card card = deck.DealCard();
	//			int dp = dealer.hand_points();
	//			int cp = card.points();

	//			if (cp + dp <= 21) {
	//				dealer.AddCard(card);
	//			}
	//			else {
	//				break;
	//			}
	//		}
	//	}
	//	Sleep(1500);	// 模拟庄家思考过程
	//	cout << magenta << "庄家要牌结束!\n\n\n" << def;

	//	Sleep(800);
	//	system("cls");

	//	// 玩家是否要牌
	//	int availableDraws = 3;
	//	while (true) {
	//		if (availableDraws <= 0) {
	//			break;
	//		}
	//		system("cls");
	//		cout << magenta << "玩家要牌阶段...\n" << def;
	//		cout << "当前手牌:\n" << player.DisplayHandCards();
	//		cout << string("是否") + (availableDraws != 3 ? "继续" : "") + string("要牌？(y/N): ");

	//		choice = _getch();
	//		if (choice == 'y' || choice == 'Y') {
	//			Card c = deck.DealCard();
	//			player.AddCard(c);
	//			availableDraws--;
	//			continue;
	//		}
	//		else if (choice == 'P' || choice == 'p') {
	//			static const string pwdA = "123";
	//			static const string pwdS = "456";

	//			string input;
	//			cout << "请输入密码:";
	//			cin >> input;

	//			if (input == pwdA) {
	//				player.set_status(Player::PlayerStatus::ADVANCED_PLAYER);
	//				cout << "已修改身份为高级玩家!\n";
	//			}
	//			else if (input == pwdS) {
	//				player.set_status(Player::PlayerStatus::SUPER_PLAYER);
	//				cout << "已修改身份为超级玩家!\n";
	//			}
	//			else {
	//				system("cls");
	//				continue;
	//			}
	//		}
	//		else {
	//			break;
	//		}

	//		if (player.player_status() == Player::PlayerStatus::ADVANCED_PLAYER) {
	//			cout << "[高级玩家]自动要牌中...\n";
	//			while (true) {	// 高级玩家(庄家无密码)自动要牌，并保证不超过 21 点
	//				Card card = deck.DealCard();

	//				int pp = player.hand_points();
	//				int cp = card.points();

	//				cout << "下一张牌是:\n"
	//					<< card.Display() << "\n";

	//				if (cp + pp <= 21) {
	//					player.AddCard(card);
	//					cout << "已自动要牌!\n";
	//				}
	//				else {
	//					cout << "舍弃此牌!\n";
	//					break;
	//				}
	//			}
	//			break;
	//		}
	//		else if (player.player_status() == Player::PlayerStatus::SUPER_PLAYER) {
	//			cout << "[超级玩家]正在操作...\n";
	//			cout << "[天眼窥视]庄家手牌:\n"
	//				<< dealer.DisplayHandCards(false)
	//				<< "玩家手牌:\n"
	//				<< player.DisplayHandCards(false);

	//			int p;
	//			cout << "请指定下一张牌的点数[0, 10]:";
	//			cin >> p;
	//			if (p >= 1 && p <= 10) {
	//				Card c(static_cast<Card::Rank>(p));
	//				player.AddCard(c);
	//			}
	//			break;
	//		}
	//	}

	//	cout << "\n";

	//	// 计算输赢
	//	cout << cyan
	//		<< "===== 庄家 =====\n"
	//		<< dealer.DisplayHandCards(false)
	//		<< "庄家点数: " << dealer.DisplayHandPoints(false) << "\n"
	//		<< cyan << "===== ==== =====\n\n\n" << def;
	//	cout << blue
	//		<< "===== 玩家 =====\n"
	//		<< player.DisplayHandCards(false)
	//		<< "玩家点数: " << player.DisplayHandPoints(false) << "\n"
	//		<< blue << "===== ==== =====\n\n\n" << def;

	//	if (player.hand_points() > 21 || dealer.hand_points() > player.hand_points()) {
	//		cout << red << "你输了!\n" << def;
	//	}
	//	else if (dealer.hand_points() < player.hand_points()) {
	//		cout << blue << "你赢了!\n" << def;
	//	}
	//	else {
	//		cout << lightGray << "平局!\n" << def;
	//	}

	//	cout << magenta << "是否继续游戏？(y/N): " << def;
	//	choice = _getch();
	//} while (choice == 'y' || choice == 'Y');


	return 0;
}

void Debug()
{
	Card ACE(Card::Rank::ACE);
	Card TWO(Card::Rank::TWO);
	Card THREE(Card::Rank::THREE);
	Card FOUR(Card::Rank::FOUR);
	Card FIVE(Card::Rank::FIVE);
	Card SIX(Card::Rank::SIX);
	Card SEVEN(Card::Rank::SEVEN);
	Card EIGHT(Card::Rank::EIGHT);
	Card NINE(Card::Rank::NINE);
	Card TEN(Card::Rank::TEN);
	Card JACK(Card::Rank::JACK);
	Card QUEEN(Card::Rank::QUEEN);
	Card KING(Card::Rank::KING);
	vector<Card> cardInHand;
	cardInHand.push_back(ACE);
	cardInHand.push_back(TWO);
	cardInHand.push_back(THREE);
	cardInHand.push_back(FOUR);
	cardInHand.push_back(FIVE);
	cardInHand.push_back(SIX);
	cardInHand.push_back(SEVEN);
	cardInHand.push_back(EIGHT);
	cardInHand.push_back(NINE);
	cardInHand.push_back(TEN);
	cardInHand.push_back(JACK);
	cardInHand.push_back(QUEEN);
	cardInHand.push_back(KING);

	for (int row = 0; row < 6; row++) {
		for (int i = 0; i < cardInHand.size(); i++) {
			cout << cardInHand[i].Display(row) << " ";
		}
		cout << "\n";
	}

	cout << "Points Value:\t";
	for (int i = 0; i < cardInHand.size(); i++) {
		cout << cardInHand[i].points() << (i == cardInHand.size() - 1 ? "\n" : "       ");
	}

	cout << "隐藏牌:\n";
	for (int row = 0; row < 6; row++) {
		for (int i = 0; i < cardInHand.size(); i++) {
			cout << cardInHand[i].Display(row, true) << " ";
		}
		cout << "\n";
	}

	Deck deck;
	deck.Shuffle();

	for (int i = 0; i < 52; i++) {
		Card card = deck.DealCard();
		cout << card.Display() << "\t"
			<< "Points: " << card.points() << "\t"
			<< "Symbol: " << card.symbol() << "\n";
	}

	try {
		deck.ResetDeck();
		deck.Shuffle();

		Player player0;
		Player player1(1000U);
		Player player2(Player::PlayerStatus::ADVANCED_PLAYER);
		Player player3(1000000U, Player::PlayerStatus::SUPER_PLAYER);

		cout << "===== player0 =====\n"
			<< "money: " << player0.money() << "\n"
			<< "===== player1 =====\n"
			<< "money: " << player1.money() << "\n"
			<< "===== player2 =====\n"
			<< "money: " << player2.money() << "\n"
			<< "===== player3 =====\n"
			<< "money: " << player3.money() << "\n";

		cout << "\n重新设置 player0、player2 的账户金额...\n\n";

		player0.set_money(100U);
		player2.set_money(10000U);

		cout << "===== player0 =====\n"
			<< "money: " << player0.money() << "\n"
			<< "===== player2 =====\n"
			<< "money: " << player2.money() << "\n";

		cout << "\n正在发牌...\n\n";

		player0.AddCard(deck.DealCard());
		player0.AddCard(deck.DealCard());
		player1.AddCard(deck.DealCard());
		player1.AddCard(deck.DealCard());
		player2.AddCard(deck.DealCard());
		player2.AddCard(deck.DealCard());
		player3.AddCard(deck.DealCard());
		player3.AddCard(deck.DealCard());

		cout << "====== player0 ======\n"
			<< player0.DisplayHandCards()
			<< "HandCardsPoints: " << player0.DisplayHandPoints() << "\n"
			<< "====== player1 ======\n"
			<< player1.DisplayHandCards(true)
			<< "HandCardsPoints: " << player1.DisplayHandPoints(true) << "\n"
			<< "====== player2 ======\n"
			<< player2.DisplayHandCards()
			<< "HandCardsPoints: " << player2.DisplayHandPoints() << "\n"
			<< "====== player3 ======\n"
			<< player3.DisplayHandCards()
			<< "HandCardsPoints: " << player3.DisplayHandPoints() << "\n";

		cout << "\n第一轮要牌...\n\n";

		player1.AddCard(deck.DealCard());
		player2.AddCard(deck.DealCard());
		player3.AddCard(deck.DealCard());

		cout << "====== player0 ======\n"
			<< player0.DisplayHandCards()
			<< "HandCardsPoints: " << player0.DisplayHandPoints() << "\n"
			<< "====== player1 ======\n"
			<< player1.DisplayHandCards(true)
			<< "HandCardsPoints: " << player1.DisplayHandPoints(true) << "\n"
			<< "====== player2 ======\n"
			<< player2.DisplayHandCards()
			<< "HandCardsPoints: " << player2.DisplayHandPoints() << "\n"
			<< "====== player3 ======\n"
			<< player3.DisplayHandCards()
			<< "HandCardsPoints: " << player3.DisplayHandPoints() << "\n";

		cout << "\n第二轮要牌...\n\n";

		player2.AddCard(deck.DealCard());
		player3.AddCard(deck.DealCard());

		cout << "====== player0 ======\n"
			<< player0.DisplayHandCards()
			<< "HandCardsPoints: " << player0.DisplayHandPoints() << "\n"
			<< "====== player1 ======\n"
			<< player1.DisplayHandCards(true)
			<< "HandCardsPoints: " << player1.DisplayHandPoints(true) << "\n"
			<< "====== player2 ======\n"
			<< player2.DisplayHandCards()
			<< "HandCardsPoints: " << player2.DisplayHandPoints() << "\n"
			<< "====== player3 ======\n"
			<< player3.DisplayHandCards()
			<< "HandCardsPoints: " << player3.DisplayHandPoints() << "\n";

		Player player4("SeaYJ", 1000000U, Player::PlayerStatus::SUPER_PLAYER);
		Player player5("海纪元", 1000000U, Player::PlayerStatus::SUPER_PLAYER);
		player4.AddCard(deck.DealCard());
		player4.AddCard(deck.DealCard());
		player4.AddCard(deck.DealCard());
		player4.AddCard(deck.DealCard());
		player5.AddCard(deck.DealCard());
		player5.AddCard(deck.DealCard());
		
		cout << "\n\n" 
			<< player3.DisplayHandCP(false, false) << "\n"
			<< player4.DisplayHandCP(false, false) << "\n"
			<< player5.DisplayHandCP(true, true) << "\n";

		BlackjackGame game;
		//game.CoutGameHeader();
		//game.ShowGameMainMenu();
		//game.CoutGameOutcome(BlackjackGame::GameResult::WIN);
		//game.CoutGameOutcome(BlackjackGame::GameResult::LOSE);
		//game.CoutGameOutcome(BlackjackGame::GameResult::TIE);

		cout << "--- 底端 ---\n";

		cout << "牌堆现在还有: " << deck.DeckSize() << " 张牌";
	}
	catch (const std::exception& e) {
		cerr << e.what() << endl;
	}
}
