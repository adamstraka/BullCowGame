// BullCowGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using Ftext = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
Ftext GetValidGuess();
bool AskToPlayAgain();
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
	std::cout << "\n\nWelcome to Bulls and Cows, a boobs and pussy game. \n";
	std::cout << "Can you guess the isogram word containing " << BCGame.GetHiddenWordLength() << " letters, that Im thinking of? \n\n";
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "Maximum tries: " << MaxTries << std::endl;

	//loop asking for guesses while the game is NOT won
	//and there are still turns remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		Ftext Guess = GetValidGuess();

		// submit valid guess to the game and receive counts.
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// print the guess back to them
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows;
		std::cout << "\n\n";
	}
	if (BCGame.IsGameWon())
	{
		std::cout << "***!!! Kurvicko you guessed the right word and WON!!!***\n\n";
	}
	else
	{
		std::cout << "Kurvicko, unfortunatelly you ran out of tries, better luck next time! (loooooooooser)\n\n";
	}
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
		std::cout << "Try: " << CurrentTry << "\n Come on mrdko, take a guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Kurvicko enter " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Kurvicko you can enter only lowercase word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Kurvicko you can enter only words that contain single letter only once (e.g. isogram).\n";
			break;
		default:
			break; //assuming valid guess is submmited			
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //keep looping until we get valid guess input.
	return Guess;
}

bool AskToPlayAgain()
{
	Ftext Response = "";
	std::cout << "Do you want to play again Mrdko? Y/N" << std::endl;
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}


