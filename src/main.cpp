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

	//// ��Ϸ��ʼ
	//char choice;
	//do {
	//	system("cls");
	//	deck.ResetDeck();	// ÿ�������ƶ�
	//	deck.Shuffle();		// ÿ������ϴ��

	//	Player player(1000U, Player::PlayerStatus::AVERAGE_PLAYER);
	//	Player dealer(1000000U, Player::PlayerStatus::ADVANCED_PLAYER);

	//	// ׯ�һ��������
	//	dealer.AddCard(deck.DealCard());
	//	dealer.AddCard(deck.DealCard());

	//	// ��һ��������
	//	player.AddCard(deck.DealCard());
	//	player.AddCard(deck.DealCard());

	//	cout << magenta << "���ַ���\n\n\n" << def;

	//	// չʾ����
	//	cout << cyan
	//		<< "===== ׯ�� =====\n"
	//		<< dealer.DisplayHandCards(true)
	//		<< "ׯ�ҵ���: " << dealer.DisplayHandPoints(true) << "\n"
	//		<< cyan << "===== ==== =====\n\n\n" << def;
	//	cout << blue
	//		<< "===== ��� =====\n"
	//		<< player.DisplayHandCards(false)
	//		<< "��ҵ���: " << player.DisplayHandPoints(false) << "\n"
	//		<< blue << "===== ==== =====\n\n\n" << def;

	//	cout << "[�밴 Y ����]:";
	//	do {
	//		choice = _getch();
	//	} while (choice != 'y' && choice != 'Y');

	//	system("cls");

	//	// ׯ���Ƿ�Ҫ��(����Ĭ��Ϊ�߼����/����ҵĸ߼�������в�ͬ[������������])
	//	cout << magenta << "ׯ��Ҫ�ƽ׶�...\n" << def;
	//	if (dealer.player_status() == Player::PlayerStatus::ADVANCED_PLAYER) {
	//		while (true) {	// �߼����(ׯ��������)�Զ�Ҫ�ƣ�����֤������ 21 ��
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
	//	Sleep(1500);	// ģ��ׯ��˼������
	//	cout << magenta << "ׯ��Ҫ�ƽ���!\n\n\n" << def;

	//	Sleep(800);
	//	system("cls");

	//	// ����Ƿ�Ҫ��
	//	int availableDraws = 3;
	//	while (true) {
	//		if (availableDraws <= 0) {
	//			break;
	//		}
	//		system("cls");
	//		cout << magenta << "���Ҫ�ƽ׶�...\n" << def;
	//		cout << "��ǰ����:\n" << player.DisplayHandCards();
	//		cout << string("�Ƿ�") + (availableDraws != 3 ? "����" : "") + string("Ҫ�ƣ�(y/N): ");

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
	//			cout << "����������:";
	//			cin >> input;

	//			if (input == pwdA) {
	//				player.set_status(Player::PlayerStatus::ADVANCED_PLAYER);
	//				cout << "���޸����Ϊ�߼����!\n";
	//			}
	//			else if (input == pwdS) {
	//				player.set_status(Player::PlayerStatus::SUPER_PLAYER);
	//				cout << "���޸����Ϊ�������!\n";
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
	//			cout << "[�߼����]�Զ�Ҫ����...\n";
	//			while (true) {	// �߼����(ׯ��������)�Զ�Ҫ�ƣ�����֤������ 21 ��
	//				Card card = deck.DealCard();

	//				int pp = player.hand_points();
	//				int cp = card.points();

	//				cout << "��һ������:\n"
	//					<< card.Display() << "\n";

	//				if (cp + pp <= 21) {
	//					player.AddCard(card);
	//					cout << "���Զ�Ҫ��!\n";
	//				}
	//				else {
	//					cout << "��������!\n";
	//					break;
	//				}
	//			}
	//			break;
	//		}
	//		else if (player.player_status() == Player::PlayerStatus::SUPER_PLAYER) {
	//			cout << "[�������]���ڲ���...\n";
	//			cout << "[���ۿ���]ׯ������:\n"
	//				<< dealer.DisplayHandCards(false)
	//				<< "�������:\n"
	//				<< player.DisplayHandCards(false);

	//			int p;
	//			cout << "��ָ����һ���Ƶĵ���[0, 10]:";
	//			cin >> p;
	//			if (p >= 1 && p <= 10) {
	//				Card c(static_cast<Card::Rank>(p));
	//				player.AddCard(c);
	//			}
	//			break;
	//		}
	//	}

	//	cout << "\n";

	//	// ������Ӯ
	//	cout << cyan
	//		<< "===== ׯ�� =====\n"
	//		<< dealer.DisplayHandCards(false)
	//		<< "ׯ�ҵ���: " << dealer.DisplayHandPoints(false) << "\n"
	//		<< cyan << "===== ==== =====\n\n\n" << def;
	//	cout << blue
	//		<< "===== ��� =====\n"
	//		<< player.DisplayHandCards(false)
	//		<< "��ҵ���: " << player.DisplayHandPoints(false) << "\n"
	//		<< blue << "===== ==== =====\n\n\n" << def;

	//	if (player.hand_points() > 21 || dealer.hand_points() > player.hand_points()) {
	//		cout << red << "������!\n" << def;
	//	}
	//	else if (dealer.hand_points() < player.hand_points()) {
	//		cout << blue << "��Ӯ��!\n" << def;
	//	}
	//	else {
	//		cout << lightGray << "ƽ��!\n" << def;
	//	}

	//	cout << magenta << "�Ƿ������Ϸ��(y/N): " << def;
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

	cout << "������:\n";
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

		cout << "\n�������� player0��player2 ���˻����...\n\n";

		player0.set_money(100U);
		player2.set_money(10000U);

		cout << "===== player0 =====\n"
			<< "money: " << player0.money() << "\n"
			<< "===== player2 =====\n"
			<< "money: " << player2.money() << "\n";

		cout << "\n���ڷ���...\n\n";

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

		cout << "\n��һ��Ҫ��...\n\n";

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

		cout << "\n�ڶ���Ҫ��...\n\n";

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
		Player player5("����Ԫ", 1000000U, Player::PlayerStatus::SUPER_PLAYER);
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

		cout << "--- �׶� ---\n";

		cout << "�ƶ����ڻ���: " << deck.DeckSize() << " ����";
	}
	catch (const std::exception& e) {
		cerr << e.what() << endl;
	}
}
