#include <iostream>
#include "classes.h"
using namespace std;

//default constructor for the card class
card::card()
{
	suit = "suit";
        rank = "rank";
	value = 0;
        location = "location";
}

//copy constructor for the card class
card::card(const card& index)
{
	suit = index.suit;
        rank = index.rank;
	value = index.value;
        location = index.location;
}

//destructor for the card class
card::~card()
{
	suit = "suit";
        rank = "rank";
	value = 0;
        location = "location";
}

//overloaded assignment operator for the card class
card& card::operator=(const card& index)
{
	suit = index.suit;
        rank = index.rank;
        location = index.location;
	return*this;
}

//overloaded assignment operator for the greater than check between card classes
bool card::operator>(const card& index) const
{
	if (value > index.value)
	{
		return true;
	}
	return false;
}

//sets the location of a card
void card::setLocation(string place)
{
	location = place;
}

//overloaded assignment operator for the less than check between card classes
bool operator<(const card& first, const card& second)
{
	if (first.value < second.value)
	{
		return true;
	}
	return false;
}

//outputs each of the cards' member data
ostream& operator<<(ostream& out, card& index)
{
	out << index.suit << '\t' << index.rank << '\t' << index.location << endl;

	return out;
}

//inputs each of the cards' member data
ifstream& operator>>(ifstream& values, card& index)
{
	values >> index.suit;
	values >> index.rank;
	if (index.rank == "two")
	{
		index.value = 2;
	}
	if (index.rank == "three")
	{
		index.value = 3;
	}
	if (index.rank == "four")
	{
		index.value = 4;
	}
	if (index.rank == "five")
	{
		index.value = 5;
	}
	if (index.rank == "six")
	{
		index.value = 6;
	}
	if (index.rank == "seven")
	{
		index.value = 7;
	}
	if (index.rank == "eight")
	{
		index.value = 8;
	}
	if (index.rank == "nine")
	{
		index.value = 9;
	}
	if (index.rank == "ten")
	{
		index.value = 10;
	}
	if (index.rank == "jack")
	{
		index.value = 11;
	}
	if (index.rank == "queen")
	{
		index.value = 12;
	}
	if (index.rank == "king")
	{
		index.value = 13;
	}
	if (index.rank == "ace")
	{
		index.value = 14;
	}
	index.location = "unshuffled";
	return values;
}

//default constructor of the player class
player::player()
{
	name = "first last";
        hand = new card[5];
	bet = 0.0;
}

//destructor of the player class
player::~player()
{
	name = "first last";
        delete [] hand;
	hand = NULL;
	bet = 0.0;
}

//outputs each data member of the player class
ostream& operator<<(ostream& out, player& index)
{
	out << index.name << endl;
	for (int i = 0; i < 5; i++)
	{
		out << index.hand[i];
	}
	out << "$" << index.bet << endl << endl;
	return out;
}

//inputs each data member of the player class
ifstream& operator>>(ifstream& values, player& index)
{
	string first;
	string last;
	values >> first;
	values >> last;
	index.name = first + " " + last;
	return values;
}

//retyrbs the name of a player
string player::getName()
{
	return name;
}

//takes in 5 cards and sets them into the player's hand
void player::setCards(card* index)
{
	for (int i = 0; i < 5; i++)
	{
		hand[i] = index[i];
	}
}
