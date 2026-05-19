// Bank  Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


const string FileName = "Clients.txt";



enum enMainMenueOptions { // This enum to select Main Menue option clearly
	eListClients =1, eAddNewClient =2,
	eDeleteClient =3, eUpdateClient =4,
	eFindClient =5, Exit =6
};

// Banck project [ Course No.7 ] 

int ReadMainMenueOption(int From, int To) {

	int Number;
	cout << "\n Choose what you want to do? [1 to 6]?   ";
	cin >> Number;

	while (Number<From || Number > To) {

		cout << "\nPlease Enter a valid number [1 to 6]? ";
		cin >> Number;
	}

	return Number;
}

struct stClient {

	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double Balance;
	bool MarkForDelete = false;
};

void MainMenuSceeen(vector <stClient> vClients); // We declair this in the beggining to let the compilar know that this function is available
// to not get any errors if we used the function before it is wrote 



stClient ConvertLineToRecord(string Line, string Delim = "#//#") { // This converts every line record to structrue record 

	stClient Client;

	if (Line == "") {

		return Client;
	}
	
	Client.AccountNumber = Line.substr(0, Line.find(Delim));
	Line = Line.erase(0, Line.find(Delim) + Delim.length());
	Client.PinCode = Line.substr(0, Line.find(Delim));
	Line = Line.erase(0, Line.find(Delim) + Delim.length());
	Client.Name = Line.substr(0, Line.find(Delim));
	Line = Line.erase(0, Line.find(Delim) + Delim.length());
	Client.Phone = Line.substr(0, Line.find(Delim));
	Line = Line.erase(0, Line.find(Delim) + Delim.length());
	Client.Balance = stod(Line.substr(0, Line.find(Delim)));
	Line = Line.erase(0, Line.find(Delim) + Delim.length());

	return Client;

}

vector <stClient> SaveFileDataToVecrtor(string FileName) {   // This function to store file content to vector [ Store All Clients Data to Vectro ]

	fstream MyFile;
	string Line; // This to store every line of our file to manipulate it 
	stClient Client; // We will convert each line to record structure to be able to stroe every client to vector 
	vector <stClient> vClients; // I will stroe Clients as structure with all its data in this vector

	MyFile.open(FileName, ios::in); // ios::in --> Read mode [ just read data from file ]

	if (MyFile.is_open()) {


		while (getline(MyFile, Line)) { // getline used to read the file and return true and save first line of the file to  Line  when reach \n , and if we have finished it will return false 


			Client = ConvertLineToRecord(Line); 

			vClients.push_back(Client);

		}

		MyFile.close();
	}

	return vClients;
}



// [1] Show Clients List
void HeaderOfClientsList() {
	cout << left;
	cout << "\n-----------------------------------------------------------------------------------------------\n\n";
	cout << "|" << setw(20) << "Account Number";
	cout << "|" << setw(15) << "PinCode";
	cout << "|" << setw(30) << "Client Name";
	cout << "|" << setw(15) << "Phone";
	cout << "|" << setw(15) << "Balance";
	cout << "\n\n-----------------------------------------------------------------------------------------------\n\n";
}


void ShowClientsList(vector <stClient> vClients) {

	system("cls");

	cout << "\n\t\t\t\tClient List (" << vClients.size() << ") Client(s)." << endl;
	HeaderOfClientsList();


	for (stClient& C : vClients) {

		cout << "|" << setw(20) << C.AccountNumber;
		cout << "|" << setw(15) << C.PinCode;
		cout << "|" << setw(30) << C.Name;
		cout << "|" << setw(15) << C.Phone;
		cout << "|" << setw(15) << C.Balance;
		cout << endl;
	}

	cout << "\n\n-----------------------------------------------------------------------------------------------\n\n";

}



// [2] Add New Client

 // IMPORTANT : I will use Account number as an [ID], so this will be unique number for every Client

void AddNewClientScreen() {

	cout << "\n-----------------------------------\n";
	cout << "\t AddNew Clients Screen\n";
	cout << "\n-----------------------------------\n";
	cout << "Adding New Client: \n\n";
}

bool CheckIfAccountNumberAvailable(string AccountNumber, vector <stClient> vClients) { // check if account number is exists

	for (stClient& C : vClients) {

		if (C.AccountNumber == AccountNumber) {

			return true;
		}
	}

	return false;
}

stClient FillNewClientData(string AccountNumber) { // filling new client data

	stClient Client;

	Client.AccountNumber = AccountNumber;
	cout << "\nEnter PinCode?  ";
	getline(cin >> ws, Client.PinCode);
	cout << "\nEnter Name?  ";
	getline(cin, Client.Name);
	cout << "\nEnter Phone?  ";
	getline(cin, Client.Phone);
	cout << "\nEnter Balance?  ";
	cin >> Client.Balance;

	return Client;
}

string ConvertRecordToLine(stClient Client,string Delim = "#//#") { // Converting structure to Line Record

	string Line = "";

	Line = Client.AccountNumber + Delim + Client.PinCode + Delim + Client.Name + Delim + Client.Phone + Delim + to_string(Client.Balance);

	return Line;
}

void UpdateFileWithNewClient(string FileName, stClient Client) {

	fstream MyFile;
	string Line; // To stroe every line record in file
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open()) {

		Line = ConvertRecordToLine(Client);
		MyFile << Line << endl;

	}

	MyFile.close();

}

void AddNewClient(vector <stClient> &vClients) { 

	system("cls");

	stClient Client; // Fill New Client Details
	string AccountNumber; // Account Number to check if its already exists or no
	char AddMoreClients = 'N'; // Checks if we want to add more Clients after adding One already

	AddNewClientScreen(); 
	cout << "Enter Account Number?  ";
	cin >> AccountNumber;

	while(CheckIfAccountNumberAvailable(AccountNumber, vClients)) { // Check if Account number is exists 

		cout << "\n\n Client with [" << AccountNumber << "] already exists, Enter another Account Number?    ";
		cin >> AccountNumber;
	}

	Client = FillNewClientData(AccountNumber); // Fill Client with all details


	// Update Vector and File 

	vClients.push_back(Client); // Add New Client to vector 

	UpdateFileWithNewClient(FileName, Client); // Add New Client to File



	cout << "Client Added Successfully, do you want to add more Clients? Y/N?   ";
	cin >> AddMoreClients;


	if (toupper(AddMoreClients) == 'Y') {

		AddNewClient(vClients);
	}



}


// [3] Delete Client 

void DeleteClientScreen() {

	cout << "\n-----------------------------------\n";
	cout << "\t Delete Client Screen\n";
	cout << "\n-----------------------------------\n";
}

stClient SaveSpecificClientData(string AccountNumber, vector <stClient> vClients) { // get specific client data and return it 
	stClient Client;

	for (stClient& C : vClients) {

		if (C.AccountNumber == AccountNumber) {

			Client = C;
		}
	}

	return Client;
}

void PrintClientCard(stClient Client) { // printing client detail to screen 

	cout << "\n\nThe following are the client details:\n";
	cout << "-------------------------------------\n";
	cout << "Account Number :" << Client.AccountNumber << endl;
	cout << "PinCode        :" << Client.PinCode << endl;
	cout << "Name           :" << Client.Name << endl;
	cout << "Phone          :" << Client.Phone << endl;
	cout << "Account Balance:" << Client.Balance << endl;
	cout << "-------------------------------------\n";

}

bool MarkClientForDelete(string AccountNumber, vector <stClient> &vClients) { // turinng MarkForDeleteMark to true to be able to easily detect

	for (stClient& C : vClients) {

		if (C.AccountNumber == AccountNumber) {

			C.MarkForDelete = true;
			return true;
		}
	}

	return false;
}

void UpdateClientsFile(string FileName, vector <stClient> vClients) { // remove all file detail --> output mode [ios::out], and save all vector clients except which marked for delete

	fstream MyFile;
	string Line; // To stroe every line record in file
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open()) {

		for (stClient& C : vClients) {

			if (C.MarkForDelete == false) {

				Line = ConvertRecordToLine(C);
				MyFile << Line << endl;

			}
			

		}
		

	}

	MyFile.close();

}


bool DeleteClient(vector <stClient>& vClients) {

	system("cls");

	DeleteClientScreen();
	string AccountNumber;
	stClient Client;
	char ConfirmDeleting = 'N';

	cout << "\nPlease Enter Account Number?  ";
	cin >> AccountNumber;

	if (CheckIfAccountNumberAvailable(AccountNumber,vClients)) { // check if account number exsists

		
		Client = SaveSpecificClientData(AccountNumber, vClients); // save client data to Client

		PrintClientCard(Client); // Print Client Data on screen

		cout << "\n\n Are you sure you want to delete this client ? Y/N?   ";
		cin >> ConfirmDeleting;

		if (toupper(ConfirmDeleting) == 'Y') {


			MarkClientForDelete(AccountNumber, vClients); // Make Client mark for delete in structure true to be able to detect and delete

			UpdateClientsFile(FileName, vClients); // Remove all file data and store again without deleted client


			vClients = SaveFileDataToVecrtor(FileName); 		// Now update vector clients with new file updates

			cout << "\n\n\n\nClient Deleted Successfully.\n\n";

			return true;

		}
		else {

			return false;
		}

		
	}
	else {

		cout << "\n\nClient with Account Number (" << AccountNumber << ") is Not Found! \n\n";
		return false;
	}


}



// [4] Update Client Info
void UpdateClientScreen() {

	cout << "\n-----------------------------------\n";
	cout << "\t Update Client Screen\n";
	cout << "\n-----------------------------------\n";
}


void UpdateThisClient(string AccountNumber, vector <stClient>& vClients) {

	for (stClient& C : vClients) {

		if (C.AccountNumber == AccountNumber) {

			cout << "\n\nEnter PinCode?   ";
			getline(cin >> ws, C.PinCode);
			cout << "\nEnter Name?   ";
			getline(cin, C.Name);
			cout << "\nEnter Phone?   ";
			getline(cin, C.Phone);
			cout << "\nEnter AccountBalance?   ";
			cin >> C.Balance;
		}
	}

}

bool UpdateClientInfo(vector <stClient> &vClients) {

	system("cls");

	stClient Client;
	string AccountNumber;
	char ConfirmUpdating = 'N';

	UpdateClientScreen();

	cout << "\n\nPlease enter Account Number?  ";
	cin >> AccountNumber;

	if (CheckIfAccountNumberAvailable(AccountNumber, vClients)) {


		Client = SaveSpecificClientData(AccountNumber, vClients);

		PrintClientCard(Client);

		cout << "\n\n\nAre you sure you want to update this client?  ";
		cin >> ConfirmUpdating;

		if (toupper(ConfirmUpdating) == 'Y') {

			UpdateThisClient(AccountNumber, vClients); // Update this specific client data except account number

			UpdateClientsFile(FileName, vClients); // Updating Clients File with new Info

			// No Need to modify vector its already modified because we called it by refd

			cout << "\n\nClient updated successfully.\n";

			return true;
		}
		else {
			
			return false;
		}

	}
	else {

		cout << "\n\nClient with Account Number (" << AccountNumber << ") is Not Found! \n\n";
		return false;
	}

}



// [5] Find Client 

void FindClientScreen() {

	cout << "\n-----------------------------------\n";
	cout << "\t Find Client Screen\n";
	cout << "\n-----------------------------------\n";
}

bool FindClient(vector <stClient> vClients) {

	system("cls");

	string AccountNumber;
	stClient Client;
	FindClientScreen();

	cout << "\n\nPlease enter Account Number?  ";
	cin >> AccountNumber;

	if (CheckIfAccountNumberAvailable(AccountNumber, vClients)) {

		Client = SaveSpecificClientData(AccountNumber, vClients);

		PrintClientCard(Client);

		return true;

	}
	else {


		cout << "\n\nClient with Account Number (" << AccountNumber << ") is Not Found! \n\n";
		return false;
	}

}








//      *** Finally ***

// Put all functionalities together


void ReturnToMainMenue(vector <stClient>& vClients) {

	cout << "Press any key to go back to Main Menue...";
	system("pause");
	MainMenuSceeen(vClients);

}


void BankSystem(vector <stClient> &vClients, enMainMenueOptions MainMenuOption) {
	
	system("cls");

	switch (MainMenuOption) {

	case enMainMenueOptions::eListClients :
		ShowClientsList(vClients);
		ReturnToMainMenue(vClients);
		break;
	case enMainMenueOptions::eAddNewClient:
		AddNewClient(vClients);
		ReturnToMainMenue(vClients);
		break;

	case enMainMenueOptions::eDeleteClient:
		DeleteClient(vClients);
		ReturnToMainMenue(vClients);
		break;

	case enMainMenueOptions::eUpdateClient:
		UpdateClientInfo(vClients);
		ReturnToMainMenue(vClients);
		break;

	case enMainMenueOptions::eFindClient:
		FindClient(vClients);
		ReturnToMainMenue(vClients);
		break;

	case 6:
		system("cls");
		break;
	
	}

}


void MainMenuSceeen(vector <stClient> &vClients) {

	system("cls");
	cout << "======================================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "======================================================\n";
	cout << "\t[1] Show Client List.	 \n";
	cout << "\t[2] Add New Client.	 \n";
	cout << "\t[3] Delete Client.		 \n";
	cout << "\t[4] Update Client Info. \n";
	cout << "\t[5] Find Client.		 \n";
	cout << "\t[6] Exit.				 \n";
	cout << "======================================================\n";

	BankSystem(vClients,(enMainMenueOptions)ReadMainMenueOption(1,6));
}







int main()
{

	vector <stClient> vClients = SaveFileDataToVecrtor(FileName);

	/*BankSystem(vClients);*/
	
	MainMenuSceeen(vClients);







}
