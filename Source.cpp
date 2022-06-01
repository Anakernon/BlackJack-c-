#include "stdafx.h"
#include <string>
#include <iostream>
#include "Header.h"
#include <array>
#include <random>



/*






















*/

Card::Card(Rank rank, Suit suit) :
	m_rank(rank), m_suit(suit)
{

}

void Card::printCard() const {
	switch (Card::m_rank)
	{
	case Rank::II:
		std::cout << "II ";
		break;
	case Rank::III:
		std::cout << "III ";
		break;
	case Rank::IV:
		std::cout << "IV ";
		break;
	case Rank::V:
		std::cout << "V ";
		break;
	case Rank::VI:
		std::cout << "VI ";
		break;
	case Rank::VII:
		std::cout << "VII ";
		break;
	case Rank::VIII:
		std::cout << "VIII ";
		break;
	case Rank::IX:
		std::cout << "IX ";
		break;
	case Rank::X:
		std::cout << "X ";
		break;
	case Rank::JACK:
		std::cout << "Jack ";
		break;
	case Rank::QUEEN:
		std::cout << "Queen ";
		break;
	case Rank::KING:
		std::cout << "King ";
		break;
	case Rank::ACE:
		std::cout << "Ace ";
		break;
	default:
		break;
	}

	switch (Card::m_suit)
	{
	case Suit::CLUBS:
		std::cout << "Clubs" << std::endl;
		break;
	case Suit::DIAMONDS:
		std::cout << "Diamonds" << std::endl;
		break;
	case Suit::HEARTS:
		std::cout << "Hearts" << std::endl;
		break;
	case Suit::SPADES:
		std::cout << "Spades" << std::endl;
		break;
	default:
		break;
	}
}

int Card::getCardValue() const {
	int value;
	switch (Card::m_rank)
	{
	case Rank::II:
		value = 2;
		break;
	case Rank::III:
		value = 3;
		break;
	case Rank::IV:
		value = 4;
		break;
	case Rank::V:
		value = 5;
		break;
	case Rank::VI:
		value = 6;
		break;
	case Rank::VII:
		value = 7;
		break;
	case Rank::VIII:
		value = 8;
		break;
	case Rank::IX:
		value = 9;
		break;
	case Rank::X:
		value = 10;
		break;
	case Rank::JACK:
		value = 10;
		break;
	case Rank::QUEEN:
		value = 10;
		break;
	case Rank::KING:
		value = 10;
		break;
	case Rank::ACE:
		value = 11;
		break;
	default:
		break;
	}

	return value;
}

Deck::Deck() {
	for (int i = 0; i < static_cast<int>(Card::Rank::TOTAL_Rank); i++)
	{
		for (int j = 0; j < static_cast<int>(Card::Suit::TOTAL_Suit); j++)
		{
			m_deck.at(4 * i + j) = Card(static_cast<Card::Rank>(i), static_cast<Card::Suit>(j));
		}
	}
}

void Deck::printDeck() const {
	for (const auto &card : m_deck)
	{
		card.printCard();
	}
	std::cout << std::endl;
}

int Deck::random(int avoid_it) {
	int randomnumber;
	do
	{
		std::random_device rd;
		std::mt19937 mersenne(rd());
		randomnumber = mersenne() % 52;
	} while (randomnumber == avoid_it);
	return randomnumber;
}

void Deck::swapCard(Card &card1, Card &card2) {
	Card temp;
	temp = card1;
	card1 = card2;
	card2 = temp;
}

void Deck::shuffleDeck() {
	int i = 0;
	for (auto &card : m_deck)
	{
		swapCard(card, m_deck.at(random(i)));
		i++;
	}
	m_cardIndex = 0;
}

const Card& Deck::dealCard() {
	
	return m_deck[m_cardIndex++];
}

HandDeck::HandDeck() {

}

void HandDeck::addCard(const Card &card) {
	m_handdeck.push_back(card);
}

const int HandDeck::score() {
	int aces = 0;
	int score = 0;
	for (auto const &card : m_handdeck)
	{
		score += card.getCardValue();
		if (card.getCardValue() == 11)
		{
			aces++;
		}
	}
	if ((score > 21) && (aces > 0))
	{
		score -= (10 * aces);
	}
	return score;
}

 HandDeck::~HandDeck() {
	m_handdeck.clear();
}

bool playerChoice() {
	std::cout << "Hit or stand?" << std::endl;
	std::string enterValue;
	do
	{
		std::cin >> enterValue;
	} while ((enterValue != "Hit") && (enterValue != "hit") && (enterValue != "stand") && (enterValue != "1") && (enterValue != "2") && (enterValue != "h") && (enterValue != "s"));
	if ((enterValue == "Hit") || (enterValue == "hit") || (enterValue == "1") || (enterValue == "h"))
	{
		return true;
	}
	if ((enterValue == "stand") || (enterValue == "2") || (enterValue == "s"))
	{
		return false;
	}
}

void HandDeck::showCard() const {
	m_handdeck.back().printCard();
}

bool playBlackjack(Deck &deck) {
	HandDeck dealerHand;
	HandDeck playerHand;
	dealerHand.addCard(deck.dealCard());
	std::cout << "Dealer got: ";
	dealerHand.showCard();
	dealerHand.addCard(deck.dealCard());
	playerHand.addCard(deck.dealCard());
	std::cout << "Player got: ";
	playerHand.showCard();
	playerHand.addCard(deck.dealCard());
	std::cout << "Player got: ";
	playerHand.showCard();
	while ((playerHand.score() < 21) && (playerChoice()))
	{
		playerHand.addCard(deck.dealCard());
		std::cout << "Player got: ";
		playerHand.showCard();
		// if (playerscore >= 21) {break;}
	}
	if (playerHand.score() > 21)
	{
		printScore(playerHand.score(), dealerHand.score());
		std::cout << "You lost." << std::endl;
		return false;
	}

	std::cout << "Dealer got: ";
	dealerHand.showCard();
	while (dealerHand.score() < 17)
	{
		dealerHand.addCard(deck.dealCard());
		std::cout << "Dealer got: ";
		dealerHand.showCard();
	}
	if (dealerHand.score() > 21)
	{
		printScore(playerHand.score(), dealerHand.score());
		std::cout << "You win." << std::endl;
		return true;
	}
	if (playerHand.score() > dealerHand.score())
	{
		printScore(playerHand.score(), dealerHand.score());
		std::cout << "You win." << std::endl;
		return true;
	}
	if (playerHand.score() < dealerHand.score())
	{
		printScore(playerHand.score(), dealerHand.score());
		std::cout << "You lost." << std::endl;
		return false;
	}
	if (playerHand.score() == dealerHand.score())
	{
		printScore(playerHand.score(), dealerHand.score());
		std::cout << "push" << std::endl;
		return true;
	}
}

void printScore(const int &playerscore, const int &dealerscore) {
	std::cout << "P-" << playerscore << " : " << "D-" << dealerscore << std::endl;
}