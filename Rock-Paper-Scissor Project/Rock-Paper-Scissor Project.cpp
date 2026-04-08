// Rock-Paper-Scissor Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
using namespace std;




// Rock Paper Scissor Game 



enum enGameControls{Rock =1,Paper=2,Scissor=3};



int ReadPositiveNumber(string Message) {

	int Number;

	do {

		cout << Message << endl;
		cin >> Number;
	} while (Number < 0);

	return Number;

}


int GameRounds() {

	int Rounds = ReadPositiveNumber("How many Rounds : 1 to 10 ? \n");

	return Rounds;
	
}

int RandomGenerator(int From, int To) {

	int Number = rand() % (To - From + 1) + From;

	return Number;
}


bool CheckIfPlayerWin(int UserInput, int ComputerChoice) {

	
	if (UserInput == enGameControls::Rock && ComputerChoice == enGameControls::Scissor) {

		return true;
	}
	else if (UserInput == enGameControls::Paper && ComputerChoice == enGameControls::Rock) {

		return true;
	}
	else if (UserInput == enGameControls::Scissor && ComputerChoice == enGameControls::Paper) {

		return true;
	}

	return false;

}


string GetChoiceName(int Input) {

	enGameControls GameNames;
	if (Input == enGameControls::Rock) {

		return "Rock";
	}
	else if (Input == enGameControls::Paper) {

		return "Paper";
	}
	else if (Input == enGameControls::Scissor) {

		return "Scissor";
	}
}


void RoundResult(int PlayerInput, int ComputerChoice, string RoundWinner) {


	
	cout << "Player 1 Choice : " << GetChoiceName(PlayerInput) << endl;
	cout << "Computer Choice : " << GetChoiceName(ComputerChoice) << endl;
	cout << "Round Winner : " << RoundWinner;
	cout << "----------------------------------------\n\n";

}

string Winner(int PlayerScore, int ComputerScore) {

	if (PlayerScore > ComputerScore) {
		system("color A7");
		return "[Player 1]";
	}
	else {
		system("Color 4F");
		return "[Computer]";
	}
}

void GameResults(int Rounds, int PlayerScore, int ComputerScore, int DrawTimes) {

	cout << "\t\t --------------------------------------------------------------------\n";
	cout << "\t\t -------------------------- *** Game Over *** -----------------------\n";
	cout << "\t\t --------------------------------------------------------------------\n";
	cout << "\t\t -------------------------- [Game Results ] -------------------------\n";

	cout << "\t\t Game Rounds            : " << Rounds << endl;
	cout << "\t\t Player1 Won times      : " << PlayerScore << endl;
	cout << "\t\t Computer Won times     : " << ComputerScore << endl;
	cout << "\t\t Draw times             : " << DrawTimes << endl;
	if (PlayerScore == ComputerScore) {
		system("color 6F");
		cout << "\t\t Final Winner           : [ No Winner ] "  << endl;

	}
	else {

		cout << "\t\t Final Winner           : " << Winner(PlayerScore, ComputerScore) << endl;
	}

	cout << "\t\t --------------------------------------------------------------------\n";



}


bool CheckContinuePlaying(int& Rounds) {

	char Input;
	cout << "Do you want to Play again ? Y/N ?";
	cin >> Input;

	if (toupper(Input) == 'Y') {
		system("color 07");
		system("cls");
		Rounds = GameRounds();
		return true;
	}
	else {
		return false;
	}
}


void GamePlay(int Rounds) {


	do {

		int UserInput, ComputerChoice, UserScore = 0, ComputerScore = 0, DrawCounter = 0;

		string RoundWinner;

		for (int i = 1; i <= Rounds; i++) {

			cout << "Round [" << i << "] begins : \n";

			cout << "Your Choice: [1] :Rock, [2]:Paper, [3]:Scissor ?  ";
			cin >> UserInput;

			ComputerChoice = RandomGenerator(1, 3);

			cout << "-------- Round [" << i << "] --------" << endl;

			if (UserInput == ComputerChoice) {

				system("color 6F");

				RoundWinner = "[No Winner]\n";

				RoundResult(UserInput, ComputerChoice, RoundWinner);

				++DrawCounter;

			}
			else {

				if (CheckIfPlayerWin(UserInput, ComputerChoice)) {

					system("color A7");
					++UserScore;
					RoundWinner = "[Player 1]\n";
					RoundResult(UserInput, ComputerChoice, RoundWinner);
				}
				else {

					system("color 4F");
					cout << "\a"; // to make the compurer make a beeb sound 
					++ComputerScore;
					RoundWinner = "[Computer]\n";
					RoundResult(UserInput, ComputerChoice, RoundWinner);
				}

			}


		}

		GameResults(Rounds, UserScore, ComputerScore, DrawCounter);

		
		

	} while (CheckContinuePlaying(Rounds));



}




int main()
{
	// To seed rand function 
	srand((unsigned)time(NULL));


	GamePlay(GameRounds());




	


}

