// Math Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


// Math Game 


enum enQuestionLevel{Easy = 1, Med =2, Hard = 3, Mix = 4};

enum enOperationType {Add =1 , Sub =2 , Mul = 3, Div = 4, mix = 5};


struct stQuestion {

	short QuestionNumber;
	short Number1;
	short Number2;
	enOperationType Operation;

};

struct stFinalResult {

	short NumberOfQuestion;
	enQuestionLevel Level;
	enOperationType Operation;
	short RightAnswers = 0;
	short WrongAnswers = 0;

};

int RandomGenerator(int From, int To) {  // Random Generator Function

	int RandomNumber = rand() % (To - From + 1) + From;

	return RandomNumber;
}  

int HowManyQuestionsToAnswer() {

	int Questions; 

	cout << "How many Questions you want to answer ?  ";
	cin >> Questions;
	
	return Questions;
}


enQuestionLevel ChooseLevel() {

	short Level;

	do {
		cout << "Enter questions level [1] Easy [2] Med [3] Hard [4] Mix ?      ";
		cin >> Level;

	} while (Level < 1 || Level > 4);

	return (enQuestionLevel)Level;
}


int GetNumberFromEachLevel(enQuestionLevel Level) {

	if (Level == enQuestionLevel::Easy) {

		return RandomGenerator(1, 10);
	}
	else if (Level == enQuestionLevel::Med){

		return RandomGenerator(11, 30);
	}
	else if (Level == enQuestionLevel::Hard) {

		return RandomGenerator(31, 100);
	}
	else {

		return RandomGenerator(1, 100);
	}

}


enOperationType ChooseOperator() {

	short Operator =1;

	do {

		if (Operator == 5) {

			return (enOperationType)RandomGenerator(1, 4);

		}
		
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div,[5] Mix ?      ";

		cin >> Operator;

		


	} while (Operator < 1 || Operator >5);
	

	return (enOperationType)Operator;
}


string OperatorSympols(enOperationType Operator) {

	string OperatorSympol[5] = { "+", "-", "*", "/" };

	return OperatorSympol[Operator - 1];

}

string LevelName(enQuestionLevel Level) {

	string LevelName[4] = { "Easy" , "Med" , "Hard", "Mix" };

	return LevelName[Level - 1];
}

string OperationName(enOperationType Operation) {

	string OperationName[5] = { "Add", "Sub", "Mul", "Div", "Mix" };

	return OperationName[Operation - 1];
}

int MakeCalculation(short Num1, short Num2, enOperationType Operation) {

	if (Operation == enOperationType::Add) {

		return Num1 + Num2;
	}
	else if (Operation == enOperationType::Sub) {

		return Num1 - Num2;
	}
	else if (Operation == enOperationType::Mul) {

		return Num1 * Num2;
	}
	else {

		return Num1 / Num2;
	}
}

void CheckCorrect(int Result, int UserAnswer) {

	if (Result == UserAnswer) {

		cout << "Right Answer :)\n\n";
		system("color 2F");
	}
	else {

		cout << "Wrong Answer :(\n\n";
		cout << "\a";
		system("color 4F");

		cout << "The right answer is : " << Result << endl;
	}
}

void FinalResultScreen(int UserRightAnswers, int UserWrongAnswers) {


	cout << "\n\n__________________________________________________________\n\n";

	cout << "\t\tFinal Resutl is :  ";
	if (UserRightAnswers >= UserWrongAnswers) {
		
		cout << "Pass :)\n\n";
		system("color 2F");

	}
	else {
		cout << "Fail :(\n\n";
		system("color 4F");
	}

	cout << "__________________________________________________________\n";

}


stFinalResult FillFinalResult(int NoOfQuestions, enQuestionLevel QuestionLevel, enOperationType OperationType, int NoOfRightAnswer, int NoOfWrongAnswer) {

	stFinalResult FinalResults;

	FinalResults.NumberOfQuestion = NoOfQuestions;
	FinalResults.Level = QuestionLevel;
	FinalResults.Operation = OperationType;
	FinalResults.RightAnswers = NoOfRightAnswer;
	FinalResults.WrongAnswers = NoOfWrongAnswer;

	return FinalResults;
}


stFinalResult StartQuestions(int HowManyQuestions) {

	stQuestion Question;

	int RightAnswers = 0;
	int WrongAnswers = 0;

	enQuestionLevel Level = ChooseLevel();
	
	enOperationType Operator = ChooseOperator();

	string OperatorSympol = OperatorSympols(Operator);

	int UserAnswer;


	for (int QuestionNo = 1; QuestionNo <= HowManyQuestions; QuestionNo++) {

		cout << "\n\n\nQuestion [" << QuestionNo << "/" << HowManyQuestions << "] \n\n";

		Question.Number1 = GetNumberFromEachLevel(Level);
		Question.Number2 = GetNumberFromEachLevel(Level);
		if (Operator == enOperationType::mix) {

			Question.Operation =(enOperationType)RandomGenerator(1, 4);
		}
		else {
			Question.Operation = Operator;

		}


		cout <<Question.Number1<< endl;


		cout << Question.Number2<<"      " << OperatorSympols(Question.Operation) << endl;

		cout << "_______________________ \n\n";

		cin >> UserAnswer;

		int RealAnswer = MakeCalculation(Question.Number1, Question.Number2, Question.Operation);

		CheckCorrect(RealAnswer, UserAnswer);

		cout << "\n\n\n";


		// Track Counters 

		if (RealAnswer == UserAnswer) {

			RightAnswers++;
		}
		else {

			WrongAnswers++;
		}

	}


	FinalResultScreen(RightAnswers, WrongAnswers);

	return FillFinalResult(HowManyQuestions, Level, Operator, RightAnswers, WrongAnswers);
	

}



void ResetGameScreen() {


	system("color 0F");
	system("cls");

}


void PrintFinalResults(stFinalResult FinalResults) {

	cout << "Number of questions  : " << FinalResults.NumberOfQuestion << endl;
	cout << "Question Level       : " << LevelName(FinalResults.Level) << endl;
	cout << "OP Type              : " << OperationName(FinalResults.Operation) << endl;
	cout << "No of right answers  : " << FinalResults.RightAnswers << endl;
	cout << "No of wrong answers  : " << FinalResults.WrongAnswers << endl;

	cout << "________________________________________________\n";
}




void StartGame() {

	char PlayAgain = 'y';

	do {

		ResetGameScreen();


		
		PrintFinalResults(StartQuestions(HowManyQuestionsToAnswer()));

		cout << "\n\nDo you want to play again ? Y/N ";
		cin >> PlayAgain;
	} while (PlayAgain == 'y' || PlayAgain == 'Y');

}


int main()
{
	// To seed random function
	srand((unsigned)time(NULL));


	StartGame();


}

