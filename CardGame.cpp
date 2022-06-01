// CardGame.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Header.h"
#include <array>
#include <iostream>
#include <string>






int main()
{
	Deck deck;
	int cash = 100;
	std::string enterValue;
	deck.shuffleDeck();
	do
	{
		deck.shuffleDeck();
		if (playBlackjack(deck))
		{		
			std::cout << "Your prize is: " << (cash / 2) << "$" << std::endl;
			cash += (cash / 2);
			std::cout << "Your total is: " << cash << "$" << std::endl;
		}
		else {		
			std::cout << "You lost: " << (cash / 2) << "$" << std::endl;
			cash -= (cash / 2);
			std::cout << "Your total is: " << cash << "$" << std::endl;
		}
		std::cout << "Keep playing?" << std::endl;
		do
		{
			std::cin >> enterValue;
		} while ((enterValue != "yes") && (enterValue != "no") && (enterValue != "1") && (enterValue != "2") && (enterValue != "y") && (enterValue != "n"));
		if ((enterValue == "no") || (enterValue == "n") || (enterValue == "2"))
		{
			cash = 0;
		}
	} while (cash > 0);





	std::cin.clear();
	std::cin.ignore(32767, '\n');
	std::cin.get();
    return 0;
}

