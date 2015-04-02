/****************************************************************************************/
/* PROGRAM: Project8                                                                    */
/*                                                                                      */
/* AUTHOR: Joriel Justin Z Alves                                                        */
/*                                                                                      */
/* DATE: 4/1/15                                                                         */
/*                                                                                      */
/* REVISIONS: this project no longer uses the previous slot machine formats		*/
/*                                                                                      */
/* PURPOSE: through classes, the program reads in cards, shuffles them, and reads in players so that the cards can be dealt with each player*/
/*                                                                                      */
/****************************************************************************************/

#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "classes.h"
using namespace std;

void readCards(card *deck);
void shuffleCards(card *deck, card *shuffledDeck);
void readPlayers(player *person, int playerSize);
void dealCards(card *shuffledDeck, card *discarded, card *stocked, player *person, int playerSize);
void printEverything(card *deck, card *shuffledDeck, card *discarded, card *stocked, player *person, int playerSize);

int numCards = 52;

int main()
{
	//declare an unshuffled deck of 52 cards
	card *unshuffled;
	unshuffled = new card [52];
	//declare a shuffled deck of 52 cards
	card *shuffled;
	shuffled = new card [52];
	//declare a pile of one discarded card
	card *discardpile;
	discardpile = new card [1];
	//declare a stockpile of 52 available spaces
	card *stockpile;
	stockpile = new card [52];
	int input;
	int numberPlayers;
	//ask the user how many players will be in the card game
	while(input < 2 || input > 8)
	{
		cout << endl << "How many dudes are playing today? (Input 2 - 8 players)" << endl;
		cin >> input;
	}
	//declare players
	numberPlayers = input;
	player *gamer;
	gamer = new player [numberPlayers];
	input = 0;
	while(input != 6)		//allows the menu to keep appearing until the user inputs a value of 6
	{
		cout << endl << "What do you want to do?" << endl << "1. Read a deck of cards in from file" << endl << "2. Shuffle the deck of cards" << endl << "3. Read in a list of players from file" << endl << "4. Deal first round of cards to the players" << endl << "5. Print the unshuffled deck, unshuffled deck, discarded cards, remaining cards, and player information to screen" << endl << "6. Quit" << endl;
		cin >> input;
		cout << endl;
		switch (input)		//each case will initiate a function depending on the what value the user inputs
		{
			case 1: readCards(unshuffled);
    				break;
			case 2: shuffleCards(unshuffled, shuffled);
    				break;
			case 3: readPlayers(gamer, numberPlayers);
    				break;
			case 4: dealCards(shuffled, discardpile, stockpile, gamer, numberPlayers);
    				break;
			case 5: printEverything(unshuffled, shuffled, discardpile, stockpile, gamer, numberPlayers);
				break;
		}
	}
}

void readCards(card *deck)
{
	char* temp = new char[20];
	cout << "Name of file to be read:" << endl;	//asks the user for the name of the card file
	cin >> temp;
	ifstream fin;
	fin.open(temp);
	//reads in each card to the unshuffled deck array
	for (int i = 0; i < 52; i++)
	{
		fin >> deck[i];
	}
	cout << "List of cards successfully read!" << endl;
}

void shuffleCards(card *deck, card *shuffledDeck)
{
	int randomNumber;
	card temp;
	//copies the unshuffled deck into the shuffled deck
	for (int i = 0; i < 52; i++)
	{
		shuffledDeck[i] = deck[i];
		shuffledDeck[i].setLocation("shuffled");
	}
	//goes through every card on the deck and swaps them with any card on the deck
	for (int i = 51; i > 0; i--)
	{
		randomNumber = rand() % (i + 1);
		temp = shuffledDeck[randomNumber];
		shuffledDeck[randomNumber] = shuffledDeck[i];
		shuffledDeck[i] = temp;
	}
	cout << "Cards successfully shuffled!" << endl;
}

void readPlayers(player *person, int playerSize)
{
	char* temp = new char[20];
	cout << "Name of file to be read:" << endl;	//asks the user for the name of the player file
	cin >> temp;
	ifstream fin;
	fin.open(temp);
	//copies every name in the file and inputs them into the player array
	for (int i = 0; i < playerSize; i++)
	{
		fin >> person[i];
	}
	cout << "List of players successfully read!" << endl;
}

void dealCards(card *shuffledDeck, card *discarded, card *stocked, player *person, int playerSize)
{
	card* temp = new card[5];		//creates an array of 5 cards
	string personLocation;
	for(int i=0; i<playerSize; i++)
	{
		for(int j=0; j<5; j++)
		{
			temp[j] = shuffledDeck[i + j*playerSize];	//i indicates the player number, while j indicates the card number for the hand, so for example, the first player gets the first card, it then skips each person's first card, then gets the card after that series, then the process repeats
			personLocation = person[i].getName();
			temp[j].setLocation(personLocation);		//indicates the person who currently holds the card
		}
		person[i].setCards(temp);			//takes the properties of 5 temporary cards and sets them as the five cards of the person's hand
	}
	int cardsUsed = 5*playerSize;				//declares how many cards were currently used after dealing
	int remaining = 52 - 5*playerSize;			//declares how many cards have not been dealt
	//put the next card on the discard pile
	discarded[0] = shuffledDeck[cardsUsed + 1];		
	discarded[0].setLocation("discard");
	//looks two cards ahead since the last deal, and starts placing the remaining cards on the stock pile
	for (int i = 2; i < remaining; i++)			//i starts at 2 because 0 indicates the last dealt card, and 1 indicates the discarded card
	{
		stocked[i-2] = shuffledDeck[cardsUsed + i];	
		stocked[i-2].setLocation("stock");
	}
	cout << "Cards successfully dealt!" << endl;
}

void printEverything(card *deck, card *shuffledDeck, card *discarded, card *stocked, player *person, int playerSize)
{
	int remaining = 52 - 5*playerSize;
	//outputs the unshuffled deck
	cout << "UNSHUFFLED DECK" << endl << endl;
	for (int i = 0; i < 52; i++)
	{
		cout << deck[i];
	}
	cout << endl << endl;
	//outputs the shuffled deck
	cout << "SHUFFLED DECK" << endl << endl;
	for (int i = 0; i < 52; i++)
	{
		cout << shuffledDeck[i];
	}
	cout << endl << endl;
	//outputs the discard pile
	cout << "DISCARD PILE" << endl << endl << discarded[0];
	cout << endl << endl;
	//outputs the stock pile
	cout << "STOCK PILE" << endl << endl;
	for (int i = 0; i < remaining - 2; i++)
	{
		cout << stocked[i];
	}
	cout << endl << endl;
	//outputs the player information
	cout << "PLAYER INFORMATION" << endl << endl;
	for (int i = 0; i < playerSize; i++)
	{
		cout << person[i];
	}
	cout << endl << endl;
}
# test
