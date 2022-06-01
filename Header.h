#pragma once
#include <array>
#include <vector>


/*


struct Card {
	Rank rank;
	Suit suit;
};












*/


class Card {

public:
	enum class Rank {
		II,
		III,
		IV,
		V,
		VI,
		VII,
		VIII,
		IX,
		X,
		JACK,
		QUEEN,
		KING,
		ACE,
		TOTAL_Rank
	};

	enum class Suit {
		CLUBS,
		DIAMONDS,
		HEARTS,
		SPADES,
		TOTAL_Suit
	};

private:
	Rank m_rank;
	Suit m_suit;

public:
	Card(Rank rank = Rank::TOTAL_Rank, Suit suit = Suit::TOTAL_Suit);

	void printCard() const;

	int getCardValue() const;
};

class Deck {
private:
	std::array<Card, 52> m_deck;
	int m_cardIndex = 0;

public:
	Deck();

	void printDeck() const;

	void shuffleDeck();

	const Card& dealCard();

private:
	static int random(int avoid_it);
	
	static void swapCard(Card &card1, Card &card2);
};

class HandDeck {
private:
	std::vector<Card> m_handdeck;

public:
	HandDeck();

	void addCard(const Card &card);

	const int score();

	~HandDeck();

	void showCard() const;
};

bool playerChoice();

bool playBlackjack(Deck &deck);

void printScore(const int &playerscore, const int &dealerscore);