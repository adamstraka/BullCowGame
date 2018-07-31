#include "stdafx.h"
#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTry; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 10;
	MyMaxTry = MAX_TRIES;
	const FString HIDDEN_WORD = "hitler";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	//if word isnt an isogram, return error
	if (false)
	{
		return EGuessStatus::Not_Isogram;
	}
	//if word isnt the right length, return error
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	//if word isnt lowercase, return error
	else if (false)
	{
		return EGuessStatus::Not_Lowercase;
	}
	//otherwise return OK
	else
	{
		return EGuessStatus::OK;
	}
}

//receives the valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++; // inciment number of tries
	FBullCowCount BullCowCount; //setup return variable
	int32 WordLength = MyHiddenWord.length(); // assuming guess word is the same length as hidden word
	
	for (int32 MHWchar = 0; MHWchar < WordLength; MHWchar++) //loop trough all letters in the guess
	{
		for (int32 Gchar = 0; Gchar < WordLength; Gchar++) // compare letters against the hidden word
		{
			if (Guess[Gchar] == MyHiddenWord[MHWchar]) // if they match
			{
				if (MHWchar == Gchar)
				{
					BullCowCount.Bulls++; // inciment bulls if same place
				}
				else
				{
					BullCowCount.Cows++; //must be cow
				}								
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}





