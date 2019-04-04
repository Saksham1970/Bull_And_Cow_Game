/*
This file contains the main functioning of the game
*/

#include "FBullCowGame.h"
#include <map>
//Unreal Standards
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() 
{
	bSameWord = false;
	Reset();
	
}//Constructor

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{	
	const FString HIDDEN_WORDS_THREE [] = {"cat","day","tac","may","ago","aid","any","ape","axe","awe","aye","boy","bay","ben","ten","man", "map", "mid" , "red","sad"};
	const FString HIDDEN_WORDS_FOUR[] = { "lame","maze","dice","tore","fats" ,"dame", "sake","defy","dewy","tack","bach","undo","rims","frat","myth","worm","dorm","beam"};
	const FString HIDDEN_WORDS_FIVE[] = { "night","fight","named" ,"brick", "jumpy", "vozhd", "glent", "waqfs","vibex", "fjord", "nymph", "waltz", "gucks","bling","blind","treck" };
	const FString HIDDEN_WORDS_SIX[] = { "planet","earthy","donkey","jawbox", "kvetch", "flumps"," drying","jumbly", "dwarfs", "kvetch", "poxing", "fledgy", "skrump", "chintz "};
	const FString HIDDEN_WORDS_SEVEN[] = { "agentry","bushman","campers","stumped", "flyback", "whoring","mucking"," batfowl", "zephyrs","jordans"," phlegmy", "overply", "dumbing", "thwacks" };
	int32 RandNumber;
	if(!bSameWord){
	switch (WordLength)
		{
			case 3:
				RandNumber = rand() % sizeof(HIDDEN_WORDS_THREE)/sizeof(HIDDEN_WORDS_THREE[0]);
				MyHiddenWord = HIDDEN_WORDS_THREE[RandNumber] ;
				break;
			case 4:
				RandNumber = rand() % sizeof(HIDDEN_WORDS_FOUR) / sizeof(HIDDEN_WORDS_FOUR[0]); 
				MyHiddenWord = HIDDEN_WORDS_FOUR[RandNumber];
				break;
			case 5:
				RandNumber = rand() % sizeof(HIDDEN_WORDS_FIVE) / sizeof(HIDDEN_WORDS_FIVE[0]);
				MyHiddenWord = HIDDEN_WORDS_FIVE[RandNumber];
				break;
			case 6:
				RandNumber = rand() % sizeof(HIDDEN_WORDS_SIX) / sizeof(HIDDEN_WORDS_SIX[0]);
				MyHiddenWord = HIDDEN_WORDS_SIX[RandNumber];
				break;
			case 7:
				RandNumber = rand() % sizeof(HIDDEN_WORDS_SEVEN) / sizeof(HIDDEN_WORDS_SEVEN[0]);
				MyHiddenWord = HIDDEN_WORDS_SEVEN[RandNumber];
				break;
		}	
	
	}
	
	
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase; // TODO write function
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}


// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // incriment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; // setup our map
	for (auto Letter : Word) 	// for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) {// if the letter is in the map
			return false; // we do NOT have an isogram
		}
		else {
			LetterSeen[Letter] = true;// add the letter to the map
		}
	}

	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{	
	for (auto Letter : Word)
	{
		if (!islower(Letter)) {
			return false;
		}
	}

	return true;
}
