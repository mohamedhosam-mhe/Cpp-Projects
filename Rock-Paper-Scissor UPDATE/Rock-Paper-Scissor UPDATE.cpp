// Rock-Paper-Scissor UPDATE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


// Updated version of Rock Paper Scissor Game 

 
enum enGameChoice {Rock =1, Paper = 2, Scissor = 3};
enum enWinner {Player1 =1 ,Computer =2, Draw =3};

int RandomGenerator(int From , int To) {

    int RandomNumber = rand() % (To - From + 1) + From;

    return RandomNumber;

}
struct stRoundInfo {
    short RoundNumber = 0; 
    enGameChoice Player1Input;
    enGameChoice ComputerChoice;
    enWinner RoundWinner;
    string WinnerName;
};

struct stGameResult {

    short GameRounds = 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};


short ReadHowManyRounds() {

    short Rounds =1;

    do {

        cout << "Please enter how many rounds you want to play 1 to 10  ?";
        cin >> Rounds;
    } while (Rounds < 1 || Rounds > 10);

    return Rounds;
}

string ChoiceName(enGameChoice Choice) {

    string arrGameChoices[3] = { "Rock", "Paper", "Scissor" };

    return arrGameChoices[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner) {

    switch (Winner) {

    case enWinner::Player1:

        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    default:
        system("color 6F");
        break;
    }
}


void PrintRoundResult(stRoundInfo RoundInfo) {

    cout << "\n ____________________ Round [" << RoundInfo.RoundNumber << "] _______________________\n";
    cout << "Player 1 Choice : " << ChoiceName(RoundInfo.Player1Input) << endl;
    cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner : " << RoundInfo.WinnerName << endl;
    cout << "----------------------------------------\n\n";

    SetWinnerScreenColor(RoundInfo.RoundWinner);

}

enWinner WhoWonTheRound(stRoundInfo RoundInfo) {

    if (RoundInfo.Player1Input == RoundInfo.ComputerChoice) {

        return enWinner::Draw;
   }

    switch (RoundInfo.Player1Input) {

    case enGameChoice::Rock:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper) {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice = enGameChoice::Scissor) {

            return enWinner::Computer;
        }
        break;
    case enGameChoice::Scissor:
        if (RoundInfo.ComputerChoice == enGameChoice::Rock) {

            return enWinner::Computer;
        }
        break;

    }

    // If we reach here that's mean that player1 won 
    return enWinner::Player1;
}

string WinnerName(enWinner Winner) {

    string arrWinnerName[3] = { "Player1", "Computer", "No Winner" };

    return arrWinnerName[Winner - 1];
}

enGameChoice ReadPlayer1Input() {

    short UserChoice = 1;

    do {

        cout << "\nYour Choice: [1] :Rock, [2]:Paper, [3]:Scissor ?  ";
        cin >> UserChoice;
    } while (UserChoice < 1 || UserChoice > 3);

    return (enGameChoice)UserChoice;
}

enGameChoice GetComputerChoice() {

    short ComputerChoice = RandomGenerator(1, 3);

    return (enGameChoice)ComputerChoice;
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes) {

    if (Player1WinTimes > ComputerWinTimes) {

        return enWinner::Player1;
    }
    else if (ComputerWinTimes > Player1WinTimes) {

        return enWinner::Computer;
    }
    else {
        return enWinner::Draw;
    }
}

stGameResult FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes) {

    stGameResult GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;

}

stGameResult PlayGame(short RoundsNumber) {

    stRoundInfo RoundInfo;

    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1;  GameRound <= RoundsNumber; GameRound++) {

        cout << "\nRound [" << GameRound << "] begins : \n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Input = ReadPlayer1Input();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.RoundWinner);


        // Increase win/Draw counters

        if (RoundInfo.RoundWinner == enWinner::Player1) {

            Player1WinTimes++;
        }
        else if (RoundInfo.RoundWinner == enWinner::Computer) {
            ComputerWinTimes++;
        }
        else {

            DrawTimes++;
        }


        PrintRoundResult(RoundInfo);
    }

    return FillGameResults(RoundsNumber, Player1WinTimes, ComputerWinTimes, DrawTimes);

}

void ResetScreen() {

    system("color 0F");
    system("cls");
}

string Tabs(short NumberOfTabs) {

    string t = "";

    for (int i = 1; i < NumberOfTabs; i++) {

        t = t + "\t";
        cout << t;
    }
    return t; 
}

void ShowGameOverScreen() {

    cout << Tabs(2) << "_____________________________________________________-\n\n";
    cout << Tabs(2) << "                        +++ Game Over +++\n";
    cout << Tabs(2) << "_____________________________________________________-\n\n";

}

void ShowFinalGameResults(stGameResult GameResults) {

    cout << Tabs(2) << "______________________________[Game Results]___________________\n\n";
    cout << Tabs(2) << "Game Rounds            : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1WonTimes        : " << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "ComputerWinTimes       : " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "DrawTimes              : " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner           : " << WinnerName(GameResults.GameWinner) << endl;
    cout << Tabs(2) << "_________________________________________________________________\n\n";

    SetWinnerScreenColor(GameResults.GameWinner);
}

void StartGame() {

    char PlayAgain = 'Y';

    do {

        ResetScreen();

        stGameResult GameResults = PlayGame(ReadHowManyRounds());

        ShowGameOverScreen();

        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(3) << "Do you want to play again ? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}



int main()
{

    // To seed random output

    srand((unsigned)time(NULL));


    StartGame();



}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
