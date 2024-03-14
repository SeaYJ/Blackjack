#include "main.h"
#include "card.h"
#include "console_color.h"

int main() {
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
			cout << yellow << cardInHand[i].display(row) << " " << def;
		}
		cout << "\n";
	}

	for (int i = 0; i < cardInHand.size(); i++) {
		cout  << cardInHand[i].points() << "       ";
	}

	return 0;
}