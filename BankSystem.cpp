#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>


using namespace std;

//Enums
enum enMainMenueChoice {
	eShowClient = 1,
	eAddClient = 2,
	eDeleteClient = 3,
	eUpdateClient = 4,
	eFindClient = 5,
	eTransaction = 6,
	eManageUsers = 7,
	eLogout = 8,
};
enum enManageMenueChoice {
	eUsersList = 1,
	eAddNewUser = 2,
	eDeleteUser = 3,
	eUpdateUser = 4,
	eFindUser = 5,
	eMainMenue = 6
};
enum enTransactionMenueChoice {
	eDeposit = 1,
	eWithDraw = 2,
	eTotalBalance = 3,
	eMainMenueFromTranstionMenue = 4
};

//Structers
struct stUser {
	string UserName;
	string UserPasword;
	short UserPermision;
};
struct stClient {
	string AccountNumber;
	string PinCode;
	string ClientName;
	string Phone;
	double Balance;
};

//FILES;
const string UsersFile = "UsersFile.txt";
const string ClientsFile = "ClientFile.txt";

//CONSTANTE VARS;
const string delimator = "#//#";


//Func Ref
void ManageUsersMenue(vector<stUser>& vUsers, const stUser& MainUser, vector<stClient>& vClients);
void MainMenue(vector<stUser>& vUsers, const stUser& MainUser, vector<stClient>& vClients);
void LoginSystem(vector<stUser>& vUsers, vector<stClient>& vClients);
void TransactionsMenue(vector<stClient>& vClients, const stUser& MainUser, vector<stUser>& vUsers);



int ReadNumber(string message = "Enter a Number: ", int From = 0, int To = INT_MAX)
{
	int Number;
	cout << "\n" << message;
	cin >> Number;
	while (cin.fail() || Number < From || Number > To)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\nInvalid Input .. " << message;
		cin >> Number;
	}

	return Number;
}


void LoginSystemScreen()
{
	system("cls");
	cout << "-----------------------------------\n";
	cout << "           Login Screen\n";
	cout << "-----------------------------------\n";
}


void GoBackToManageUsersMenue(vector<stUser>& vUsers, const stUser& MainUser, vector<stClient>& vClient)
{
	cout << "\n\n\n\nPress any key to go back to Main Users Menue...";
	system("pause>0");
	ManageUsersMenue(vUsers, MainUser, vClient);
}
void GoBackToMainMenue(vector<stUser>& vUsers, const stUser& MainUser, vector<stClient>& vClient)
{
	cout << "\n\n\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	MainMenue(vUsers, MainUser, vClient);
}
void GoBackToTransactionMenue(vector<stClient>& vClients, const stUser& MainUser, vector<stUser>& vUsers)
{
	cout << "\n\n\n\nPress any key to go back to Transaction Menue...";
	system("pause>0");
	TransactionsMenue(vClients, MainUser, vUsers);
}


vector<string> SplitFunction(string S1, const string delimator = "#//#")
{
	vector<string> vString;

	string sword;
	short pos = S1.find(delimator);

	while (pos != string::npos)
	{
		sword = S1.substr(0, pos);
		if (!(sword.empty()))
		{
			vString.push_back(sword);
		}
		S1.erase(0, pos + delimator.length());
		pos = S1.find(delimator);
	}
	if (!(S1.empty()))
	{
		vString.push_back(S1);
	}

	return vString;
}


stUser ConvertUserLineToUserStruct(string UserLine, const string delimator = "#//#")
{
	vector<string> vString = SplitFunction(UserLine, delimator);
	stUser User;

	User.UserName = vString[0];
	User.UserPasword = vString[1];
	User.UserPermision = stoi(vString[2]);

	return User;
}


vector<stUser> GetUsersFromUsersFile(const string delimator = "#//#")
{
	vector<stUser> vUsers;
	fstream MyFile;

	MyFile.open(UsersFile, ios::in);

	if (MyFile.is_open())
	{
		string UserLine;
		stUser tempUser;
		while (getline(MyFile, UserLine))
		{
			if (!UserLine.empty())
			{
				tempUser = ConvertUserLineToUserStruct(UserLine);
				vUsers.push_back(tempUser);
			}

		}

		MyFile.close();
	}

	return vUsers;
}


stUser ReadUser()
{
	stUser User;
	cout << "\nEnter Username  : ";
	getline(cin >> ws, User.UserName);

	cout << "Enter Pasword   : ";
	getline(cin >> ws, User.UserPasword);

	return User;
}


bool IsUserLoggedIn(const vector<stUser>& vUsers, const stUser& UserToCheck, stUser& MainSystemUser)
{
	for (int i = 0; i < vUsers.size(); i++)
	{
		if (vUsers[i].UserName == UserToCheck.UserName)
		{
			if (vUsers[i].UserPasword == UserToCheck.UserPasword)
			{
				MainSystemUser = vUsers[i];
				return true;
			}
		}
	}
	return false;
}


stUser LogUser(const vector<stUser>& vUsers)
{
	stUser tempUser = ReadUser();
	stUser MainSystemUser;

	while (!IsUserLoggedIn(vUsers, tempUser, MainSystemUser))
	{
		LoginSystemScreen();
		cout << "\nInvalid UserName/Password:\n";
		tempUser = ReadUser();
	}

	return MainSystemUser;
}


void MainMenueScreen()
{
	system("cls");
	cout << "=========================================\n";
	cout << "           Main Menue Screen\n";
	cout << "=========================================\n";

	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.\n";

	cout << "=========================================\n";
}


void ManageUsersMenueScreen()
{
	system("cls");
	cout << "============================================\n";
	cout << "         Main Users Menue Screen\n";
	cout << "============================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menue.\n";
	cout << "============================================\n";
}


void ShowDeniedPermissionScreen()
{
	system("cls");
	cout << "=====================================\n";
	cout << "Access Denied,\n";
	cout << "You don't have permission to do this,\n";
	cout << "Please Contact Your Admin.\n";
	cout << "=====================================\n";

}


void UserListOption(const vector<stUser>& vUsers)
{
	cout << "\t\t\t\t\t Users List (" << vUsers.size() << ") User(s)\n\n";
	cout << "_________________________________________________________________________________________________\n";
	cout << left;
	cout << "|" << setw(25) << "User Name"
		<< "|" << setw(20) << "Password"
		<< "|" << setw(20) << "Permissions" << endl;
	cout << "|________________________________________________________________________________________________\n";

	for (const stUser& tempUser : vUsers)
	{
		cout << "|" << setw(25) << tempUser.UserName
			<< "|" << setw(20) << tempUser.UserPasword
			<< "|" << setw(20) << tempUser.UserPermision << endl;
		cout << "_________________________________________________________________________________________________\n";
	}
}


int IsUserExist(const vector<stUser>& vUsers, string UserName)
{
	for (int i = 0; i < vUsers.size(); i++)
	{
		if (vUsers[i].UserName == UserName)
		{
			return i;
		}
	}
	return -1;
}


short ReadUserPermission()
{
	short Permission = 0;
	char match;

	cout << "\nDo u want to give full access? (y/n): ";
	cin >> match;

	if (tolower(match) == 'y')
		return -1;

	cout << "\n----------------------------------------\n";
	cout << "Do u want to give access to:\n";

	short counter = 1;
	string arrPermissions[7] = {
		"\n[1] Show Client List  ",
		"[2] Add New Client    ",
		"[3] Delete Client     ",
		"[4] Update Client Info",
		"[5] Find Client       ",
		"[6] Transactions      ",
		"[7] Manage Users      " };

	for (short i = 0; i < 7; i++)
	{
		cout << arrPermissions[i] << " (Y/N): ";
		cin >> match;
		if (tolower(match) == 'y')
		{
			Permission += counter;
		}
		counter *= 2;
	}
	cout << "\n----------------------------------------\n";

	return Permission;
}


stUser ReadNewUser(const vector<stUser>& vUsers)
{
	stUser User;
	cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
	cout << "Adding New User:\n\n";

	cout << "Enter UserName: ";
	getline(cin >> ws, User.UserName);

	while (IsUserExist(vUsers, User.UserName) != -1)
	{
		cout << "User With [" << User.UserName << "] already exist, Enter another UserName: ";
		getline(cin >> ws, User.UserName);
	}

	cout << "\nEnter Password: ";
	getline(cin >> ws, User.UserPasword);

	User.UserPermision = ReadUserPermission();
	cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";

	return User;
}


string ConvertUserStructToString(const stUser& User, string delimator = "#//#")
{
	return User.UserName + delimator + User.UserPasword + delimator + to_string(User.UserPermision);
}


void AddNewUserToUsersFile(const stUser& User)
{
	fstream MyFile;
	MyFile.open(UsersFile, ios::out | ios::app);


	if (MyFile.is_open())
	{
		string UserLine = ConvertUserStructToString(User);
		MyFile << UserLine << endl;

		MyFile.close();
	}
}


void AddNewUsersOptionScreen()
{
	cout << "\t\t\t\t============================================\n";
	cout << "\t\t\t\t           Add New User Screen\n";
	cout << "\t\t\t\t============================================\n";
}


void AddNewUsersOption(vector<stUser>& vUsers)
{
	char more;
	stUser NewUser;
	AddNewUsersOptionScreen();

	do
	{
		NewUser = ReadNewUser(vUsers);
		AddNewUserToUsersFile(NewUser);
		vUsers.push_back(NewUser);
		//vUsers = GetUsersFromUsersFile(); // it is better to add only the New User to the vUsers instead of re-read the full UsersFile
		cout << "User Added Successfully, do you want to add more users (y/n): ";
		cin >> more;
	} while (tolower(more) == 'y');
}


void DeleteUserOptionScreen()
{
	cout << "\t\t\t\t============================================\n";
	cout << "\t\t\t\t           Delete User Screen\n";
	cout << "\t\t\t\t============================================\n";
}


void PrintUserCart(stUser User)
{
	cout << "\n===============================================\n";
	cout << "User Name         : " << User.UserName << endl;
	cout << "Password          : " << User.UserPasword << "\n";
	cout << "Permissions       : " << User.UserPermision << "\n";
	cout << "\n===============================================\n";
}


vector<stUser> DeleteUserFromVector(const vector<stUser>& vUsers, int IndexToRemove)
{
	vector<stUser> vRealUsers;

	for (int i = 0; i < vUsers.size(); i++)
	{
		if (IndexToRemove != i)
		{
			vRealUsers.push_back(vUsers[i]);
		}
	}
	return vRealUsers;
}


void SaveAllUsersInUsersFile(const vector<stUser>& vUsers)
{
	fstream MyFile;
	MyFile.open(UsersFile, ios::out);

	if (MyFile.is_open())
	{
		for (const stUser& TempUsers : vUsers)
		{
			string UserLine = ConvertUserStructToString(TempUsers);
			MyFile << UserLine << endl;
		}

		MyFile.close();
	}
}


void DeleteUserOption(vector<stUser>& vUsers, const stUser& MainUser)
{
	DeleteUserOptionScreen();
	string UserNameToDelete;

	cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
	cout << "Enter UserName: ";
	getline(cin >> ws, UserNameToDelete);

	char agree;
	int Index = IsUserExist(vUsers, UserNameToDelete);
	if (Index == -1)
	{
		cout << "\nUser with UserName [" << UserNameToDelete << "] is Not found!\n";
	}
	else if (vUsers[Index].UserName == MainUser.UserName)
	{
		cout << "\nYou can't Delete this User [" << MainUser.UserName << "] Because You're currently sing in with.\n";
	}
	else
	{
		PrintUserCart(vUsers[Index]);
		cout << "\n\nAre you sure you want to Delete this User (Y/N): ";
		cin >> agree;
		if (tolower(agree) == 'y')
		{
			vUsers = DeleteUserFromVector(vUsers, Index);
			SaveAllUsersInUsersFile(vUsers);
			cout << "\nUser Deleted Successfully.\n";
		}
		else
		{
			cout << "\nUser Does not Deleted.\n";
		}
	}
	cout << "-----------------------------------------------------------------------------------------------------------------------\n";

}


void UpdateUserOptionScreen()
{
	cout << "\t\t\t\t============================================\n";
	cout << "\t\t\t\t           Update User Screen\n";
	cout << "\t\t\t\t============================================\n";
}


void UpdateUserOption(vector<stUser>& vUsers)
{
	UpdateUserOptionScreen();

	string UserNameToUpdate;

	cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
	cout << "Enter UserName: ";
	getline(cin >> ws, UserNameToUpdate);

	int Index = IsUserExist(vUsers, UserNameToUpdate);
	if (Index == -1)
	{
		cout << "User with UserName [" << UserNameToUpdate << "] is Not found!\n";
	}
	else
	{
		PrintUserCart(vUsers[Index]);
		char Answer;

		cout << "\n\nAre you sure you want to update this User? (Y/N): ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			cout << "\nEnter Password: ";
			getline(cin >> ws, vUsers[Index].UserPasword);
			vUsers[Index].UserPermision = ReadUserPermission();

			SaveAllUsersInUsersFile(vUsers);
			cout << "\nUser Updated Successfully.\n";
		}
		else
		{
			cout << "\nUser does not Updated!\n";
		}
	}
	cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
}


void FindUserOptionScreen()
{
	cout << "\t\t\t\t============================================\n";
	cout << "\t\t\t\t           Find User Screen\n";
	cout << "\t\t\t\t============================================\n";
}


void FindUserOption(const vector<stUser>& vUsers)
{
	FindUserOptionScreen();

	string UserNameToFind;

	cout << "\nEnter UserName: ";
	getline(cin >> ws, UserNameToFind);

	int Index = IsUserExist(vUsers, UserNameToFind);
	if (Index == -1)
	{
		cout << "User with UserName [" << UserNameToFind << "] is Not found!\n";
	}
	else
	{
		PrintUserCart(vUsers[Index]);
	}
}


void ManageUsersMenue(vector<stUser>& vUsers, const stUser& MainUser, vector<stClient>& vClients)
{
	if ((MainUser.UserPermision & (1 << 6)) == 0 && MainUser.UserPermision != -1)
	{
		ShowDeniedPermissionScreen();
	}
	else
	{
		const short NUMBER_OF_MANAGE_MENUE_OPTIONS = 6;
		ManageUsersMenueScreen();
		enManageMenueChoice ManageMenueChoice = enManageMenueChoice(ReadNumber("Choose what do you want to do [1 to 6]: ", 1, NUMBER_OF_MANAGE_MENUE_OPTIONS));

		system("cls");
		switch (ManageMenueChoice)
		{
		case enManageMenueChoice::eUsersList:
			UserListOption(vUsers);
			break;
		case enManageMenueChoice::eAddNewUser:
			AddNewUsersOption(vUsers);
			break;
		case enManageMenueChoice::eDeleteUser:
			DeleteUserOption(vUsers, MainUser);
			break;
		case enManageMenueChoice::eUpdateUser:
			UpdateUserOption(vUsers);
			break;
		case enManageMenueChoice::eFindUser:
			FindUserOption(vUsers);
			break;
		case enManageMenueChoice::eMainMenue:
			MainMenue(vUsers, MainUser, vClients);
			break;
		}
		GoBackToManageUsersMenue(vUsers, MainUser, vClients);
	}
}


stClient ConvertClientLineToStruct(string ClientLine)
{
	vector<string> vClient = SplitFunction(ClientLine);

	stClient tempClient;

	tempClient.AccountNumber = vClient[0];
	tempClient.PinCode = vClient[1];
	tempClient.ClientName = vClient[2];
	tempClient.Phone = vClient[3];
	tempClient.Balance = stod(vClient[4]);

	return tempClient;
}


vector<stClient> GetClientsFromClientFile()
{
	vector<stClient> vClients;

	fstream MyFile;
	MyFile.open(ClientsFile, ios::in);

	if (MyFile.is_open())
	{
		string ClientLine;
		stClient tempClient;
		while (getline(MyFile, ClientLine))
		{
			if (!ClientLine.empty())
			{
				tempClient = ConvertClientLineToStruct(ClientLine);
				vClients.push_back(tempClient);
			}
		}
		MyFile.close();
	}

	return vClients;
}


void ShowClientOption(const vector<stClient>& vClients, const stUser& MainUser)
{
	if ((MainUser.UserPermision & (1 << 0)) == 0 && MainUser.UserPermision != -1)
	{
		ShowDeniedPermissionScreen();
	}
	else
	{
		if (vClients.size() > 0)
		{

			cout << "\n\n\t\t\t\t\t Clients List (" << vClients.size() << ") User(s)\n\n";
			cout << "___________________________________________________________________________________________________________________\n";
			cout << left;
			cout << "|" << setw(18) << "Account Number"
				<< "|" << setw(18) << "Pin Code"
				<< "|" << setw(32) << "Client Name"
				<< "|" << setw(14) << "Phone"
				<< "|" << setw(15) << "Balance";
			cout << "\n___________________________________________________________________________________________________________________\n";
			for (const stClient& tempClient : vClients)
			{
				cout << "\n|" << setw(18) << tempClient.AccountNumber
					<< "|" << setw(18) << tempClient.PinCode
					<< "|" << setw(32) << tempClient.ClientName
					<< "|" << setw(14) << tempClient.Phone
					<< "|" << setw(15) << tempClient.Balance;
				cout << "\n___________________________________________________________________________________________________________________\n";
			}
		}
		else
		{
			cout << "\n\n\t\t\tThere is no clients in the system.\n";
		}
	}
}


void AddClientOptionScreen()
{
	cout << "\t\t\t\t============================================\n";
	cout << "\t\t\t\t           Add New Client Screen\n";
	cout << "\t\t\t\t============================================\n";
}


int IsClientExist(const vector<stClient>& vClients, string AccountNumberToFind)
{
	for (int i = 0; i < vClients.size(); i++)
	{
		if (vClients[i].AccountNumber == AccountNumberToFind)
		{
			return i;
		}
	}
	return -1;
}


stClient ReadNewClient(string AccountNumber)
{
	stClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "Enter PinCode         : ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name            : ";
	getline(cin >> ws, Client.ClientName);

	cout << "Enter Phone           : ";
	getline(cin >> ws, Client.Phone);

	cout << "Enter Account Balance : ";
	cin >> Client.Balance;

	return Client;
}


stClient ReadNewClientAndCheckExisting(const vector<stClient>& vClients)
{
	stClient Client;
	cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
	cout << "Adding New Client:\n\n";

	cout << "Enter Account Number  : ";
	getline(cin >> ws, Client.AccountNumber);

	while (IsClientExist(vClients, Client.AccountNumber) != -1)
	{
		cout << "Client With [" << Client.AccountNumber << "] already exist, Enter another Account Number: ";
		getline(cin >> ws, Client.AccountNumber);
	}

	Client = ReadNewClient(Client.AccountNumber);
	cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";

	return Client;
}


string ConvertClientStructToClientLine(const stClient& Client)
{
	string ClientLine = "";

	ClientLine += Client.AccountNumber + delimator;
	ClientLine += Client.PinCode + delimator;
	ClientLine += Client.ClientName + delimator;
	ClientLine += Client.Phone + delimator;
	ClientLine += to_string(Client.Balance);

	return ClientLine;
}


void AddNewClientToClientsFile(const stClient& Client)
{
	fstream MyFile;
	MyFile.open(ClientsFile, ios::out | ios::app);

	if (MyFile.is_open())
	{
		string ClientLine = ConvertClientStructToClientLine(Client);
		MyFile << ClientLine << endl;

		MyFile.close();
	}
}


void AddClientOption(vector<stClient>& vClients, const stUser& MainUser)
{
	if ((MainUser.UserPermision & (1 << 1)) == 0 && MainUser.UserPermision != -1)
	{
		ShowDeniedPermissionScreen();
	}
	else
	{
		char more;
		stClient NewClient;
		AddClientOptionScreen();

		do
		{
			NewClient = ReadNewClientAndCheckExisting(vClients);
			AddNewClientToClientsFile(NewClient);
			vClients.push_back(NewClient);
			cout << "Client Added Successfully, do you want to add more users (Y/N) : ";
			cin >> more;
		} while (tolower(more) == 'y');
	}
}


void DeleteClientOptionScreen()
{
	cout << "\t\t\t\t============================================\n";
	cout << "\t\t\t\t           Delete Client Screen\n";
	cout << "\t\t\t\t============================================\n";
}


void PrintClientCard(const stClient& Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\n===============================================\n";
	cout << "Account Number   : " << Client.AccountNumber << endl;
	cout << "Pin Code         : " << Client.PinCode << "\n";
	cout << "Name             : " << Client.ClientName << "\n";
	cout << "Phone            : " << Client.Phone << "\n";
	cout << "Account Balance  : " << Client.Balance << "\n";
	cout << "\n===============================================\n";
}


vector<stClient> DeleteClientFromVector(const vector<stClient>& vClients, const int indexToDelete)
{
	vector<stClient> vRealClients;

	for (int i = 0; i < vClients.size(); i++)
	{
		if (i != indexToDelete)
		{
			vRealClients.push_back(vClients[i]);
		}
	}
	return vRealClients;
}


void SaveAllClientsToCLientsFile(const vector<stClient>& vClients)
{
	fstream MyFile;
	MyFile.open(ClientsFile, ios::out);

	if (MyFile.is_open())
	{
		string ClientLine;
		for (const stClient& tempClient : vClients)
		{
			ClientLine = ConvertClientStructToClientLine(tempClient);
			MyFile << ClientLine << endl;
		}

		MyFile.close();
	}
}


void DeleteClientOption(vector<stClient>& vClients, const stUser& MainUser)
{
	if ((MainUser.UserPermision & (1 << 2)) == 0 && MainUser.UserPermision != -1)
	{
		ShowDeniedPermissionScreen();
	}
	else
	{
		DeleteClientOptionScreen();
		string ClientNameToDelete;

		cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
		cout << "Enter Account Number: ";
		getline(cin >> ws, ClientNameToDelete);

		char agree;
		int Index = IsClientExist(vClients, ClientNameToDelete);
		if (Index == -1)
		{
			cout << "\nClient with UserName [" << ClientNameToDelete << "] is Not found!\n";
		}
		else
		{
			PrintClientCard(vClients[Index]);
			cout << "\n\nAre you sure you want to Delete this Client (Y/N): ";
			cin >> agree;
			if (tolower(agree) == 'y')
			{
				vClients = DeleteClientFromVector(vClients, Index);
				SaveAllClientsToCLientsFile(vClients);
				cout << "\nClient Deleted Successfully.\n";
			}
			else
			{
				cout << "\nClient Does not Deleted.\n";
			}
		}
		cout << "-----------------------------------------------------------------------------------------------------------------------\n";
	}
}


void UpdateClientOptionScreen()
{
	cout << "\t\t\t\t============================================\n";
	cout << "\t\t\t\t           Update Client Screen\n";
	cout << "\t\t\t\t============================================\n";
}


void UpdateClientOption(vector<stClient>& vClients, const stUser& MainUser)
{
	if ((MainUser.UserPermision & (1 << 3)) == 0 && MainUser.UserPermision != -1)
	{
		ShowDeniedPermissionScreen();
	}
	else
	{
		UpdateClientOptionScreen();

		string AccountNumberToUpdate;

		cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
		cout << "Enter Account Number: ";
		getline(cin >> ws, AccountNumberToUpdate);

		int Index = IsClientExist(vClients, AccountNumberToUpdate);
		if (Index == -1)
		{
			cout << "\nClient with Acount Number [" << AccountNumberToUpdate << "] is Not found!\n";
		}
		else
		{
			PrintClientCard(vClients[Index]);
			char Answer;

			cout << "\nAre you sure you want to update this Client? (Y/N): ";
			cin >> Answer;

			if (tolower(Answer) == 'y')
			{
				vClients[Index] = ReadNewClient(AccountNumberToUpdate);

				SaveAllClientsToCLientsFile(vClients);
				cout << "\nClient Updated Successfully.\n";
			}
			else
				cout << "\nClient does not Updated!\n";
		}
		cout << "-----------------------------------------------------------------------------------------------------------------------\n";
	}
}


void FindClientOptionScreen()
{
	cout << "\t\t\t\t============================================\n";
	cout << "\t\t\t\t           Find Client Screen\n";
	cout << "\t\t\t\t============================================\n";
}


void FindClientOption(const vector<stClient>& vClients, const stUser& MainUser)
{
	if ((MainUser.UserPermision & (1 << 4)) == 0 && MainUser.UserPermision != -1)
	{
		ShowDeniedPermissionScreen();
	}
	else
	{
		FindUserOptionScreen();

		string AccountNumberToFind;

		cout << "\nEnter Acount Number: ";
		getline(cin >> ws, AccountNumberToFind);

		int Index = IsClientExist(vClients, AccountNumberToFind);
		if (Index == -1)
		{
			cout << "\nClient with Account [" << AccountNumberToFind << "] is Not found!\n";
		}
		else
		{
			PrintClientCard(vClients[Index]);
		}
	}
}


void TransactionsMenueScreen()
{
	system("cls");
	cout << "=========================================\n";
	cout << "        Transactions Menue Screen\n";
	cout << "=========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balance.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "=========================================\n";
}


void DepositeOptionScreen()
{
	cout << "\t\t\t\t============================================\n";
	cout << "\t\t\t\t             Deposit Screen\n";
	cout << "\t\t\t\t============================================\n";
}


void DepositeOption(vector<stClient>& vClients)
{
	string AccountNumberToDeposit;

	DepositeOptionScreen();
	short Index;

	cout << "Enter Account Number: ";
	getline(cin >> ws, AccountNumberToDeposit);
	Index = IsClientExist(vClients, AccountNumberToDeposit);

	while (Index == -1)
	{
		cout << "Account Number [" << AccountNumberToDeposit << "] does not found! Enter Another Account Number: \n";
		getline(cin >> ws, AccountNumberToDeposit);
		Index = IsClientExist(vClients, AccountNumberToDeposit);
	}

	PrintClientCard(vClients[Index]);

	double DepositeAmount;
	cout << "\nEnter Deposit Amount: ";
	cin >> DepositeAmount;

	char Answer;
	cout << "\n\nAre you sure you want Perform this transaction (Y/N): ";
	cin >> Answer;

	if (tolower(Answer) == 'y')
	{
		vClients[Index].Balance += DepositeAmount;
		SaveAllClientsToCLientsFile(vClients);
		cout << "\nDone Successfully New Balance is: " << vClients[Index].Balance << endl;
	}
	else
	{
		cout << "\nClient Balance Does not Change!";
	}
}


void WithDrawOptionScreen()
{
	cout << "\t\t\t\t============================================\n";
	cout << "\t\t\t\t             Withdraw Screen\n";
	cout << "\t\t\t\t============================================\n";
}


void WithDrawOption(vector<stClient>& vClients)
{
	string AccountNumberToWithDraw;

	WithDrawOptionScreen();
	short Index;

	cout << "Enter Account Number: ";
	getline(cin >> ws, AccountNumberToWithDraw);
	Index = IsClientExist(vClients, AccountNumberToWithDraw);

	while (Index == -1)
	{
		cout << "Account Number [" << AccountNumberToWithDraw << "] does not found! Enter Another Account Number: \n";
		getline(cin >> ws, AccountNumberToWithDraw);
		Index = IsClientExist(vClients, AccountNumberToWithDraw);
	}

	PrintClientCard(vClients[Index]);

	double WithDrawAmount;
	cout << "\nEnter WithDraw Amount: ";
	cin >> WithDrawAmount;

	while (vClients[Index].Balance < WithDrawAmount)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to: " << vClients[Index].Balance << endl;
		cout << "\nEnter Anothe WithDraw Amount: ";
		cin >> WithDrawAmount;
	}

	char Answer;
	cout << "\n\nAre you sure you want Perform this transaction (Y/N): ";
	cin >> Answer;
	if (tolower(Answer) == 'y')
	{
		vClients[Index].Balance -= WithDrawAmount;
		SaveAllClientsToCLientsFile(vClients);
		cout << "\nDone Successfully New Balance is: " << vClients[Index].Balance << endl;
	}
	else
	{
		cout << "\nClient Balance Does not Change!\n";
	}
}


void TotalBalanceOption(vector<stClient>& vClients)
{
	if (vClients.size() == 0)
	{
		cout << "\n\nThere is no Clients on the system.\n";
	}
	else
	{
		long double Balance = 0;
		cout << "\n\n\t\t\t\t\t Balance List (" << vClients.size() << ") User(s)\n\n";
		cout << "___________________________________________________________________________________________________________________\n";
		cout << left;
		cout << "\n|" << setw(20) << "Account Number"
			<< "|" << setw(40) << "Client Name"
			<< "|" << setw(20) << "Balance";
		cout << "\n___________________________________________________________________________________________________________________\n";
		for (const stClient& tempClient : vClients)
		{
			Balance += tempClient.Balance;
			cout << "\n|" << setw(20) << tempClient.AccountNumber
				<< "|" << setw(40) << tempClient.ClientName
				<< "|" << setw(20) << tempClient.Balance;
			cout << "\n____________________________________________________________________________________________________________________\n";
		}
		cout << "\n\n\t\t\t\t\t\t\tToTal Balances = " << Balance << endl;
	}
}


// make sure about the user
void TransactionsMenue(vector<stClient>& vClients, const stUser& MainUser, vector<stUser>& vUsers)
{
	if ((MainUser.UserPermision & (1 << 5)) == 0 && MainUser.UserPermision != -1)
	{
		ShowDeniedPermissionScreen();
	}
	else
	{
		const short NUMBER_OF_TRANSACTION_MENUE_OPTIONS = 4;
		TransactionsMenueScreen();
		enTransactionMenueChoice TransactionMenueChoice = enTransactionMenueChoice(ReadNumber("Choose what do you want to do [1 to 4]: ", 1, NUMBER_OF_TRANSACTION_MENUE_OPTIONS));

		system("cls");
		switch (TransactionMenueChoice)
		{
		case enTransactionMenueChoice::eDeposit:
			DepositeOption(vClients);
			break;
		case enTransactionMenueChoice::eWithDraw:
			WithDrawOption(vClients);
			break;
		case enTransactionMenueChoice::eTotalBalance:
			TotalBalanceOption(vClients);
			break;
		case enTransactionMenueChoice::eMainMenueFromTranstionMenue:
			MainMenue(vUsers, MainUser, vClients);
			break;

		}
		GoBackToTransactionMenue(vClients, MainUser, vUsers);
	}
}


void MainMenue(vector<stUser>& vUsers, const stUser& MainUser, vector<stClient>& vClients)
{

	const short NUMBER_OF_MAIN_MENUE_OPTIONS = 8;
	MainMenueScreen();
	enMainMenueChoice MainMenueChoice = enMainMenueChoice(ReadNumber("Choose what do you want to do [1 to 8]: ", 1, NUMBER_OF_MAIN_MENUE_OPTIONS));

	system("cls");
	switch (MainMenueChoice)
	{
	case enMainMenueChoice::eShowClient:
		ShowClientOption(vClients, MainUser);
		break;
	case enMainMenueChoice::eAddClient:
		AddClientOption(vClients, MainUser);
		break;
	case enMainMenueChoice::eDeleteClient:
		DeleteClientOption(vClients, MainUser);
		break;
	case enMainMenueChoice::eUpdateClient:
		UpdateClientOption(vClients, MainUser);
		break;
	case enMainMenueChoice::eFindClient:
		FindClientOption(vClients, MainUser);
		break;
	case enMainMenueChoice::eTransaction:
		TransactionsMenue(vClients, MainUser, vUsers);
		break;
	case enMainMenueChoice::eManageUsers:
		ManageUsersMenue(vUsers, MainUser, vClients);
		break;
	case enMainMenueChoice::eLogout:
		LoginSystem(vUsers, vClients);
		break;
	}
	GoBackToMainMenue(vUsers, MainUser, vClients);
}


void LoginSystem(vector<stUser>& vUsers, vector<stClient>& vClients)
{
	stUser MainUser;
	LoginSystemScreen();

	MainUser = LogUser(vUsers);
	MainMenue(vUsers, MainUser, vClients);
}


int main()
{
	vector<stClient> vClients = GetClientsFromClientFile();
	vector<stUser> vUsers = GetUsersFromUsersFile();
	LoginSystem(vUsers, vClients);
}