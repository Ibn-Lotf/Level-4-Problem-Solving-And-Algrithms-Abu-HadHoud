#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
// Hello world!
using namespace std;
const string ClientsFileName = "DATA_USER.txt";
const string UserFileName = "DATA_USER_APP.txt";
short PwerUserGloble = 0;

void ShowMainMenue();
void ManageUsersMenuScreen();
void AppTransactions();
void ApplockScreen(bool Error = false);

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

struct sUser
{
    string UserName;
    string Passwoed;
    int Root = 0;
    bool Delete = false;
};

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);
    if (vClientData.size() == 5)
    {
        Client.AccountNumber = vClientData[0];
        Client.PinCode = vClientData[1];
        Client.Name = vClientData[2];
        Client.Phone = vClientData[3];
        Client.AccountBalance = stod(vClientData[4]);//cast string to double
    }
    return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{

    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);
        }

        MyFile.close();

    }
    return false;
}

sClient ReadNewClient()
{
    sClient Client;
    cout << "Enter Account Number? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

void PrintClientRecordLine(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreen()
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

void ShowAllClientsScreen(int BalansSum)
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "                   Totale = " << BalansSum << endl;
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client)
{
    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }

    }
    return false;
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    for (sClient& C : vClients)
    {

        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }

    }

    return false;
}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }

        }

        MyFile.close();
    }

    return vClients;
}

void AddDataLineToFile(string FileName, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }
}

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        //system("cls");
        cout << "Adding New Client:\n\n";

        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');

}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);

            //Refresh Clients 
            vClients = LoadCleintsDataFromFile(ClientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{

    sClient Client;
    char Answer = 'n';

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveCleintsDataToFile(ClientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }

    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;

}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);

}

void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    AddNewClients();
}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}

// Transactions
void GoBackTransactions()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    AppTransactions();
}

void AppDeposit()
{
    cout << "--------------------\n";
    cout << "       Deposit      \n";
    cout << "--------------------\n";

    string Acount = "";
    vector<sClient> vClinte;
    sClient Client;
    while (true)
    {
        Acount = ReadClientAccountNumber();
        if (ClientExistsByAccountNumber(Acount, ClientsFileName))
        {
            vClinte = LoadCleintsDataFromFile(ClientsFileName);
            FindClientByAccountNumber(Acount, vClinte, Client);
            PrintClientCard(Client);

            double Num = 0;
            cout << "\nBlanas: ";
            cin >> Num;

            char Y = 'n';
            cout << "[Y/N]: ";
            cin >> Y;

            if (tolower(Y) == 'y')
            {
                for (sClient& C : vClinte)
                {
                    if (Acount == C.AccountNumber)
                    {
                        C.AccountBalance += Num;
                        break;
                    }
                }
                SaveCleintsDataToFile(ClientsFileName, vClinte);
                break;
            }
            else
                break;
        }
        else
        {
            cout << "No Find";
        }
    }
}

void AppWithDraw()
{
    cout << "--------------------\n";
    cout << "       WithDraw      \n";
    cout << "--------------------\n";

    string Acount = "";
    vector<sClient> vClinte;
    sClient Client;
    while (true)
    {
        Acount = ReadClientAccountNumber();
        if (ClientExistsByAccountNumber(Acount, ClientsFileName))
        {
            vClinte = LoadCleintsDataFromFile(ClientsFileName);
            FindClientByAccountNumber(Acount, vClinte, Client);
            PrintClientCard(Client);

            double Num = 0;
            cout << "\nBlanas: ";
            cin >> Num;

            char Y = 'n';
            cout << "[Y/N]: ";
            cin >> Y;

            if (tolower(Y) == 'y')
            {
                for (sClient& C : vClinte)
                {
                    if (Acount == C.AccountNumber)
                    {
                        C.AccountBalance -= Num;
                        break;
                    }
                }
                SaveCleintsDataToFile(ClientsFileName, vClinte);
                break;
            }
            else
                break;
        }
        else
        {
            cout << "No Find";
        }
    }
}

void AppTotale()
{
    vector<sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
    double SumTotale = 0;
    for (sClient& C : vClient)
    {
        SumTotale += C.AccountBalance;
    }
    ShowAllClientsScreen(SumTotale);
}

enum enTransactions { Deposit = 1, WithDraw = 2, TotalBlance = 3, MineMenue };


enTransactions InputTransactions()
{

    short N;
    cout << "Transation: ";
    cin >> N;

    return enTransactions(N);
}

void PrintTransactions()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransation Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] WhithDraw.\n";
    cout << "\t[3] Totale Balance.\n";
    cout << "\t[4] Mine Menue.\n";
    cout << "===========================================\n";
}

void AppTransactions()
{
    PrintTransactions();

    switch (InputTransactions())
    {
    case Deposit:
        system("cls");
        AppDeposit();
        GoBackTransactions();
        break;
    case WithDraw:
        system("cls");
        AppWithDraw();
        GoBackTransactions();
        break;
    case TotalBlance:
        system("cls");
        AppTotale();
        GoBackTransactions();
        break;
    case MineMenue:
        return;
        break;
    }
}

enum enMainMenueOptions
{
    eListClients = 1, eAddNewClient = 2,
    eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, eTransations = 6, eUser = 7, eLogIn = 8
};

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();

}

short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 7]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

bool CheckPwerUserenum(enMainMenueOptions MainMenueOption)
{
    return (PwerUserGloble & 1 << (MainMenueOption - 1));
}

void PrintNotHaveTheAuthority()
{
    cout << "****** (►__◄) ********" << endl;
    cout << "You do not have the authority" << endl;
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");
        if (CheckPwerUserenum(MainMenueOption))
            ShowAllClientsScreen();
        else
            PrintNotHaveTheAuthority();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
        system("cls");
        if (CheckPwerUserenum(MainMenueOption))
            ShowAddNewClientsScreen();
        else
            PrintNotHaveTheAuthority();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eDeleteClient:
        system("cls");
        if (CheckPwerUserenum(MainMenueOption))
            ShowDeleteClientScreen();
        else
            PrintNotHaveTheAuthority();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eUpdateClient:
        system("cls");
        if (CheckPwerUserenum(MainMenueOption))
            ShowUpdateClientScreen();
        else
            PrintNotHaveTheAuthority();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eFindClient:
        system("cls");
        if (CheckPwerUserenum(MainMenueOption))
            ShowFindClientScreen();
        else
            PrintNotHaveTheAuthority();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eTransations:
        system("cls");
        if (CheckPwerUserenum(MainMenueOption))
            AppTransactions();
        else
            PrintNotHaveTheAuthority();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eUser:
        system("cls");
        if (CheckPwerUserenum(MainMenueOption))
            ManageUsersMenuScreen();
        else
            PrintNotHaveTheAuthority();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eLogIn:
        system("cls");
        ApplockScreen();
        break;
    default:
        system("cls");
        ShowEndScreen();
    }
}

void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transations.\n";
    cout << "\t[7] User Main.\n";
    cout << "\t[8] LogIn.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

void GobckeInMangeUserMenuo();


sUser ConvertLineToUser(string Line,string Splite = "#//#")
{
    sUser User;
    vector<string> Center;
    Center = SplitString(Line, Splite);
    if (Center.size() == 3)
    {
        User.UserName = Center[0];
        User.Passwoed = Center[1];
        User.Root = stoi(Center[2]);
    }

    return User;
}

string ConvertUserToLine(sUser User, string Splite = "#//#")
{
    return User.UserName + Splite + User.Passwoed + Splite + to_string(User.Root);
}

vector<sUser> LoadAllUser()
{
    fstream MyFile;
    vector<sUser> AllUser;
    MyFile.open(UserFileName, ios::in);

    if (MyFile.is_open())
    {
        sUser User;
        string Line;
        while (getline(MyFile, Line))
        {
            User = ConvertLineToUser(Line);
            AllUser.push_back(User);
        }
    }
    return AllUser;
}

void SaveAllUseres(vector<sUser>& AllUsers)
{
    fstream MyFile;
    
    MyFile.open(UserFileName, ios::out);

    if (MyFile.is_open())
    {
        string Line = "";
        for (short i = 0; i < AllUsers.size(); i++)
        {
            Line = ConvertUserToLine(AllUsers[i]);
            MyFile << Line << endl;
        }
        MyFile.close();
    }
}

sUser ReadUser()
{
    sUser User;
    
    cout << "UserName: ";
    getline(cin >> ws, User.UserName);

    cout << "Password: ";
    getline(cin >> ws, User.Passwoed);

    return User;
}

bool CheckUserInDate(sUser User,bool AndPassword = false)
{
    vector<sUser> AllUser;
    AllUser = LoadAllUser();
    
    if (AndPassword)
    {
        for (short i = 0; i < AllUser.size(); i++)
        {
            if (User.UserName == AllUser[i].UserName && User.Passwoed == AllUser[i].Passwoed)
                return true;
        }
    }
    else
    {
        for (short i = 0; i < AllUser.size(); i++)
        {
            if (User.UserName == AllUser[i].UserName)
                return true;
        }
    }
    return false;
}

int CheckUserInDatePOS(string name)
{
    vector<sUser> AllUser;
    AllUser = LoadAllUser();

    for (short i = 0; i < AllUser.size(); i++)
    {
        if (name == AllUser[i].UserName)
            return i;
    }
    return -1;
}

void PrintUserRecordLine(sUser User)
{
    cout << "| " << setw(15) << left << User.UserName;
    cout << "| " << setw(10) << left << User.Passwoed;
    cout << "| " << setw(40) << left << User.Root;
}

void ListlUserScreen()
{
    vector <sUser> vUsers = LoadAllUser();

    cout << "\n\t\t\t\t\tClient List (" << vUsers.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(20) << "Pwers";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vUsers.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sUser User : vUsers)
        {

            PrintUserRecordLine(User);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

int PwersUser()
{
    int Rank = 0;
    char Y;
    cout << "Are you sure to give the user Root rank [Y/N]? ";
    cin >> Y;
    if (tolower(Y) != 'y')
    {
        cout << "Are you sure to give the user Show Clinte Rank [Y/N]? ";
        cin >> Y;
        Rank += (tolower(Y) == 'y' ? pow(2, 0) : 0);

        cout << "Are you sure to give the user Add Clinte Rank [Y/N]? ";
        cin >> Y;
        Rank += (tolower(Y) == 'y' ? pow(2, 1) : 0);

        cout << "Are you sure to give the user Delete Clinte Rank [Y/N]? ";
        cin >> Y;
        Rank += (tolower(Y) == 'y' ? pow(2, 2) : 0);

        cout << "Are you sure to give Update of clinte Rank [Y/N]? ";
        cin >> Y;
        Rank += (tolower(Y) == 'y' ? pow(2, 3) : 0);

        cout << "Are you sure to give Search of clinte Rank [Y/N]? ";
        cin >> Y;
        Rank += (tolower(Y) == 'y' ? pow(2, 4) : 0);

        cout << "Are you sure to give Trancation Rank [Y/N]? ";
        cin >> Y;
        Rank += (tolower(Y) == 'y' ? pow(2, 5) : 0);

        cout << "Are you sure to give Add User Rank [Y/N]";
        cin >> Y;
        Rank += (tolower(Y) == 'y' ? pow(2, 6) : 0);
    }
    else
    {
        Rank = -1;
    }

    return Rank;
}

void AddNewUserScreen(bool Error = false);

sUser UserNew()
{
    sUser User;
    cout << "User Name: ";
    getline(cin >> ws, User.UserName);
    if (CheckUserInDate(User))
    {
        AddNewUserScreen(true);
        GobckeInMangeUserMenuo();
    }
    cout << "User PassWord: ";
    getline(cin >> ws, User.Passwoed);

    User.Root = PwersUser();
    return User;
}

void AddNewUser()
{
    fstream MyFile;
    sUser User;
    string Line;
    User = UserNew();
    Line = ConvertUserToLine(User);

    MyFile.open(UserFileName, ios::out | ios::app);

    if (MyFile.is_open())
    {
        MyFile << Line << endl;
        MyFile.close();
    }
}

void AddNewUserScreen(bool Error)
{
    system("cls");
    cout << "===================" << endl;
    cout << "**** Add User New *****" << endl;
    cout << "===================" << endl;
    char Y;
    do
    {
        if (Error) cout << "(Inc)\n";
        AddNewUser();
        cout << "\nAre you sure to Add User New [Y,N]? ";
        cin >> Y;
    } while (tolower(Y) == 'y');
}

void DeleteUsersScreen(bool Error = false);

void PrintUser(sUser User)
{
    cout << "-----------------------\n";
    cout << User.UserName << endl;
    cout << User.Passwoed << endl;
    cout << User.Root << endl;
    cout << "-----------------------\n";
}

void UserDelete(vector<sUser> &AllUser)
{
    string name;
    int POS = 0;
    cout << "User Name: ";
    getline(cin >> ws, name);
    if (!(POS = CheckUserInDatePOS(name)))
    {
        DeleteUsersScreen(true);
        GobckeInMangeUserMenuo();
    }
    PrintUser(AllUser[POS]);
    
    char Y;
    cout << "\nAre you sure to Delete [Y/N] : ";
    cin >> Y;
    if (tolower(Y) != 'y') GobckeInMangeUserMenuo();
    else AllUser[POS].Delete = true;
}

void DeleteUsers()
{
    fstream MyFile;
    vector<sUser> AllUser;
    AllUser = LoadAllUser();
    UserDelete(AllUser);

    MyFile.open(UserFileName, ios::out);

    if (MyFile.is_open())
    {
        string Line;
        for (short i = 0; i < AllUser.size(); i++)
        {
            if (!AllUser[i].Delete)
            {
                Line = ConvertUserToLine(AllUser[i]);
                MyFile << Line << endl;
            }
        }
        MyFile.close();
    }
}

void DeleteUsersScreen(bool Error)
{
    system("cls");
    cout << "===================" << endl;
    cout << "**** Delete User *****" << endl;
    cout << "===================" << endl;
    char Y;
    do
    {
        if (Error) cout << "(Inc)\n";
        DeleteUsers();
        cout << "\nAre you sure to Add User Delete [Y,N]? ";
        cin >> Y;
    } while (tolower(Y) == 'y');
}

void UpdateUsersScreen(bool Error = false);

void UserUpdate(vector<sUser> &AllUser,int POS)
{
    cout << "User PassWord: ";
    getline(cin >> ws, AllUser[POS].Passwoed);

    AllUser[POS].Root = PwersUser();
    SaveAllUseres(AllUser);
}

void UpdateUsers()
{
    string name;
    int POS = 0;
    cout << "User Name: ";
    getline(cin >> ws, name);
    if (!(POS = CheckUserInDatePOS(name)))
    {
        UpdateUsersScreen(true);
        GobckeInMangeUserMenuo();
    }
    vector<sUser> AllUser;
    AllUser = LoadAllUser();
    
    PrintUser(AllUser[POS]);
    
    char Y;
    cout << "\nAre you sure to Update [Y,N]? ";
    cin >> Y;
    if (tolower(Y) == 'y')
        UserUpdate(AllUser,POS);
}

void UpdateUsersScreen(bool Error)
{
    system("cls");
    cout << "===================" << endl;
    cout << "**** Update User *****" << endl;
    cout << "===================" << endl;
    char Y;
    do
    {
        if (Error) cout << "(Inc)\n";
        UpdateUsers();
        cout << "\nAre you sure to Add User Update [Y,N]? ";
        cin >> Y;
    } while (tolower(Y) == 'y');
}

void SearchScreen()
{
    string name;
    int POS = 0;
    cout << "User Name: ";
    getline(cin >> ws, name);
    if (POS = CheckUserInDatePOS(name) != -1)
    {
        vector<sUser> AllUser;
        AllUser = LoadAllUser();
        PrintUser(AllUser[POS]);
    }
    else
    {
        cout << "%%%Not available%%%";
    }
}

void SearchUserScreen()
{
    char Y;
    do
    {
        system("cls");
        cout << "====================\n";
        cout << "       Search       \n";
        cout << "====================\n";
        SearchScreen();
        cout << "\nAre you sure to Search User [Y,N]? ";
        cin >> Y;
    } while (tolower(Y) == 'y');
}

enum enUsersMenuo {uList = 1,uAdd = 2,uDelete = 3,uUpdate = 4,uFinde = 5};

void ManageUsersMenuo(enUsersMenuo UsersMenuo)
{
    switch (UsersMenuo)
    {
    case enUsersMenuo::uList:
        system("cls");
        ListlUserScreen();
        GobckeInMangeUserMenuo();
        break;
    case enUsersMenuo::uAdd:
        AddNewUserScreen();
        GobckeInMangeUserMenuo();
        break;
    case enUsersMenuo::uDelete:
        DeleteUsersScreen();
        GobckeInMangeUserMenuo();
        break;
    case enUsersMenuo::uUpdate:
        UpdateUsersScreen();
        GobckeInMangeUserMenuo();
        break;
    case enUsersMenuo::uFinde:
        SearchUserScreen();
        GobckeInMangeUserMenuo();
    default:
        ShowMainMenue();
        break;
    }
}

void ManageUsersMenuScreen()
{
    cout << "==================================\n";
    cout << "     Manage Users Menuo Screen    \n";
    cout << "==================================\n";
    cout << "       [1] List Users.    \n";
    cout << "       [2] Add Users.     \n";
    cout << "       [3] Delete Users.  \n";
    cout << "       [4] Update Users.  \n";
    cout << "       [5] Find Users.    \n";
    cout << "       [6] Mian Menuo.    \n";
    cout << "===================================" << endl;
    short UN;
    cout << "Chose from 1 to 6 : ";
    cin >> UN;
    ManageUsersMenuo(enUsersMenuo(UN));
}

void GobckeInMangeUserMenuo()
{
    system("pause>0");
    system("cls");
    ManageUsersMenuScreen();
}



void Applouk()
{
    sUser User;
    User = ReadUser();
    if (CheckUserInDate(User, true))
    {
        vector<sUser> AllUser = LoadAllUser();
        PwerUserGloble = AllUser[CheckUserInDatePOS(User.UserName)].Root;
        ShowMainMenue();
    }
    else
        ApplockScreen(true);
}

void ApplockScreen(bool Error)
{
    system("cls");
    cout << "===============" << endl;
    cout << ")( Login )(" << endl;
    cout << "===============" << endl;
    if (Error)
        cout << "The UserName and Password are (incorrect) " << endl;
    Applouk();
}

int main()
{
    ApplockScreen();
    return 0;
}