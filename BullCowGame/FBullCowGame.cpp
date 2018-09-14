#include "stdafx.h"
#include "FBullCowGame.h"
#include <map>
#define Tmap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
	Tmap <int32, int32> WordLengthToMaxTries{ { 3,5 }, { 4,7 }, { 5,10 }, { 6,15 }, { 7,20 } };

	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// trteat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	Tmap <char, bool> LetterSeen; //setup map
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter); //to allow mixed casses
		if (LetterSeen[Letter]) { //if the letter is in the map
			return false;		// we do NOT have an isogram
		}
		else {
			LetterSeen[Letter] = true;	//add the letter to the map as seen
		}		
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "blind";
	/*TODO allow user to input hidden word lenght to be selected from a map  - Tmap <int32, FString> HiddenWord { { 3, prd },{ 4, muka },{ 5, kudla },{ 6, poklad },{ 7, pustina } }; */
	MyHiddenWord = HIDDEN_WORD; /*HiddenWord[SelectHiddenWordLength()] ;*/ // part of the possible code
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	//if word isnt an isogram, return error
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	//if word isnt the right length, return error
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	//if word isnt lowercase, return error
	else if (!IsLowercase(Guess))
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







