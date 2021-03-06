// BullCowGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using Ftext = std::string;
using int32 = int;

void PrintIntro();
int32 SelectHiddenWordLength();
void PlayGame();
Ftext GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();
bool AskToShowRules();
FBullCowGame BCGame; //instantiate a new game



int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	return 0; //exit application
}



//intro
void PrintIntro()
{
	bool bShowRules = false;
	std::cout << "\n\n#=======================================================================================#\n";
	std::cout << "#                                                                                       #\n";
	std::cout << "#                        {]_[}                      _____                               #\n";
	std::cout << "#                        |> <|                    (){O o}()                             #\n";
	std::cout << "#        ----------------/|__|                      |   |                               #\n";
	std::cout << "#       /  B     L     ,// 00                       \\OO/\\\\,_______________              #\n";
	std::cout << "#      /|     U     L  |                                 \\|   C  O  W     \\             #\n";
	std::cout << "#     / '--\\\\--------''                                   -----------------\\\            #\n";
	std::cout << "#       / \\ \\\\     /\\                                       /\\    (_|_) /\\  \\           #\n";
	std::cout << "#      /   \\      /  \\                                     /  \\     oo /  \\             #\n";
	std::cout << "#=======================================================================================#\n\n";
	std::cout << "\n\nWelcome to Bulls and Cows game! \n";
	std::cout << "Can you guess the isogram word containing " << BCGame.GetHiddenWordLength() << " letters, that Im thinking of? \n\n";

	
	bShowRules = AskToShowRules();
	if (bShowRules) {
		std::cout << "RULES for guesses:\n";
		std::cout << "1.) only isograms are allowed\n";
		std::cout << "2.) only lowercase words are allowed\n";
		std::cout << "3.) only words that have the same length as a hidden word are allowed\n\n";
		std::cout << "After every guess you take, you will be given respective number of BULLS and COWS.\n";
		std::cout << "BULL means that you guessed a right letter in a right place.\nCOW means you guessed a right letter, but in a wrong place. \n\n";
		std::cout << "For example, if the word you have to guess is \"right\" and your guess is \"rough\", you will get Bulls:1 Cows:2,\n because \"r\" is a Bull and \"g, h\" are Cows\n\n";
	}
	
	return;
}

/* TODO user hidden word lenght input, possible code 
int32 SelectHiddenWordLength()
{
	int32 UserSelectedLength;
	std::cout << "Please type in how long word you want to guess using numbers from 3 to 7: "
	do 
	{
		std::getline(std::cin, UserSelectedLength);
	} while (UserSelectedLength >= 3 && UserSelectedLength <= 7);
	return UserSelectedLength;
}*/

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "Maximum tries: " << MaxTries << "\n\n";

	//loop asking for guesses while the game is NOT won
	//and there are still turns remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		Ftext Guess = GetValidGuess();

		// submit valid guess to the game and receive counts.
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// print the guess back to them
		std::cout << "BULLS = " << BullCowCount.Bulls;
		std::cout << ". COWS = " << BullCowCount.Cows;
		std::cout << "\n============================================\n";
		std::cout << "\n\n";
	}
	PrintGameSummary();
}

//loop until user gives a valid guess
Ftext GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	Ftext Guess = "";

	do
	{
		//get a guess from the user
		int32 CurrentTry = BCGame.GetCurrentTry();
		int32 TriesLeft = BCGame.GetMaxTries() - BCGame.GetCurrentTry();
		std::cout << "============================================\n";
		std::cout << "Current try: " << CurrentTry << " -> Tries left: " << TriesLeft << "\n";
		std::cout << "Come on, take a guess : ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "You can enter only " << BCGame.GetHiddenWordLength() << " letter word.";
			std::cout << "\n============================================\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "You can enter only lowercase word.";
			std::cout << "\n============================================\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "You can enter only words that contain a single letter only once (e.g. isogram).";
			std::cout << "\n============================================\n\n";
			break;
		default:
			break; //assuming valid guess is submmited			
		}		
	} while (Status != EGuessStatus::OK); //keep looping until we get valid guess input.
	return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "***!!! Ohh mr. right, yeah thats right, you are right, you guessed the right right right and WON !!!***\n\n";
	}
	else
	{
		std::cout << "Ohh mr. wrong, you are again wrong and unfortunatelly you ran out of tries, better luck next time!\n\n";
	}
}

bool AskToPlayAgain()
{
	Ftext Response = "";
	std::cout << "Do you want to play again? Y/N" << std::endl;
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

bool AskToShowRules()
{
	Ftext Response = "";
	std::cout << "Do you want to show a rules of this game? y = YES/ n = NO\n";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}


