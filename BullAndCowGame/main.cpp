/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>	
#include "FBullCowGame.h"

//Using Unreal Standards
using FText = std::string;
using FString = std::string;
using int32 = int;

//Initializing Various Functions
void PrintIntro();
void PlayGame();
FText GetValidGuess();
int32 GetLetterNumber();
bool AskToPlayAgain();
bool AskForSameIsogram();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game

// the entry point for our application
int main()
{
	bool bPlayAgain = false;
	
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
		if(bPlayAgain){
		BCGame.bSameWord = AskForSameIsogram();
		}
	} while (bPlayAgain);

	return 0; // exit the application
}


// introduce the game
void PrintIntro()
{
	

	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	if(!BCGame.bSameWord){
	BCGame.WordLength = GetLetterNumber();
	}
	std::cout << "Can you guess the " << BCGame.WordLength;
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

//gets the Letter's Length
int32 GetLetterNumber()
{
	FString LengthInput ;
	bool pass = false;
	
	do {
		std::cout << "How many letter Isogram do you want to guess(between 3-7): ";
		std::getline(std::cin, LengthInput);
		
		for (auto Letter : LengthInput) {
			if (!isdigit(Letter) || std::stoi(LengthInput) < 3 || std::stoi(LengthInput) > 7 || LengthInput == "") {

				std::cout <<"Please enter a 'number' between 3 and 7\n ";
				break;
			}
			else {
				pass = true;
				return	std::stoi(LengthInput);
				
			}
		}
	} while (!pass);
}
//Playing of the actual game
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}
// Boolean To Ask Player To Play Again
bool AskToPlayAgain()
{	
	while (true)
	{
		std::cout << "Do you want to play again(y/n)? ";
		FText Response = "";
		std::getline(std::cin, Response);
		if (Response[0] == 'y' || Response[0] == 'Y') {
			return true;
			break;
		}
		else if (Response[0] == 'n' || Response[0] == 'N') {
			return false;
			break;
		}
		else {
			std::cout << "Please Enter Either y or n\n\n";
		}
	}
		
	
}

bool AskForSameIsogram()
{
	while (true)
	{
		std::cout << "Do you want to play again with the same Isogram or a random one(s/r)? ";
		FText Response = "";
		std::getline(std::cin, Response);
		if (Response[0] == 's' || Response[0] == 'S') {
			return true;
			break;
		}
		else if (Response[0] == 'r' || Response[0] == 'R') {
			return false;
			break;
		}
		else {
			std::cout << "Please Enter Either s or r\n\n";
		}
	}
}

//Prints Summary
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}