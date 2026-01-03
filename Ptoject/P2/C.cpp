#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;
const string ClientsFileName = "../../P1/output/DATA_USER.txt";

void LogIn(bool Erorr = false);
void ATMManueScreen();
struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

sClient Clinent;
int POS;
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

void ShowEndScreen()
{
    system("cls");
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}


void GoBackATM()
{
    vector<sClient> AllClient;
    AllClient = LoadCleintsDataFromFile(ClientsFileName);
    AllClient[POS] = Clinent;
    SaveCleintsDataToFile(ClientsFileName, AllClient);
    cout << "....: ";
    system("pause>0");
    ATMManueScreen();
}

void CheckBalance()
{
    system("cls");
    cout << "=====================\n";
    cout << "Balance: " << Clinent.AccountBalance << '$' << endl;
    cout << "=====================\n";
}

void Deposit()
{
    system("cls");
    cout << "=====================\n";
    cout << "     Deposit WithDraw  \n";
    cout << "=====================\n";
    cout << "Balance: " << Clinent.AccountBalance << endl;
    cout << "===========================" << endl;
    double UN;
    cout << "Deposit : ";
    cin >> UN;
    char Y;
    cout << "[Y/N]: ";
    cin >> Y;
    if (tolower(Y) == 'y')
        Clinent.AccountBalance += UN;
    
}

void NarmalWithDraw(bool Erorr = false);

void Narmal(double Many)
{
    if (Many > Clinent.AccountBalance)
        NarmalWithDraw(true);
    else
        Clinent.AccountBalance -= Many;
}

void NarmalWithDraw(bool Erorr)
{
    system("cls");
    cout << "=====================\n";
    cout << "     Narmal WithDraw  \n";
    cout << "=====================\n";
    cout << "Balance: " << Clinent.AccountBalance << '$' << endl;
    cout << "===========================" << endl;
    double UN;
    if (Erorr)
    {
        cout << "----------------\nThe amount is not enough.\n-------------\n";
        char Y;
        cout << "Are you sure to Quick WithDraw[Y,N]";
        cin >> Y;
        if (tolower(Y) != 'y') ATMManueScreen();
    }
    cout << "Narmal : ";
    cin >> UN;
    Narmal(UN);
}

enum enQuickWithDraw {e10 = 1,e20 = 2,e50 = 3,
e100 = 4,e200 = 5,e250 = 6,e500 = 7,e700 = 8,e1000 = 9,e10000 = 10};

void QuickWithDraw(bool Erorr = false);

void WithDraw(enQuickWithDraw Quick)
{
    switch (Quick)
    {
    case e10:
        if (Clinent.AccountBalance > 10)
            Clinent.AccountBalance -= 10;
        else
            QuickWithDraw(true);
        break;
    case e20:
        if (Clinent.AccountBalance > 20)
            Clinent.AccountBalance -= 20;
        else
            QuickWithDraw(true);
        break;
    case e50:
        if (Clinent.AccountBalance > 50)
            Clinent.AccountBalance -= 50;
        else
            QuickWithDraw(true);
        break;
    case e100:
        if (Clinent.AccountBalance > 100)
            Clinent.AccountBalance -= 100;
        else
            QuickWithDraw(true);
        break;
    case e200:
        if (Clinent.AccountBalance > 200)
            Clinent.AccountBalance -= 200;
        else
            QuickWithDraw(true);
        break;
    case e250:
        if (Clinent.AccountBalance > 250)
            Clinent.AccountBalance -= 250;
        else
            QuickWithDraw(true);
        break;
    case e500:
        if (Clinent.AccountBalance > 500)
            Clinent.AccountBalance -= 500;
        else
            QuickWithDraw(true);
        break;
    case e700:
        if (Clinent.AccountBalance > 700)
            Clinent.AccountBalance -= 700;
        else
            QuickWithDraw(true);
        break;
    case e1000:
        if (Clinent.AccountBalance > 1000)
            Clinent.AccountBalance -= 1000;
        else
            QuickWithDraw(true);
        break;
    case e10000:
        if (Clinent.AccountBalance > 10000)
            Clinent.AccountBalance -= 10000;
        else
            QuickWithDraw(true);
        break;
    default:
        ATMManueScreen();
        break;
    }
}

void QuickWithDraw(bool Erorr)
{
    system("cls");
    cout << "=====================\n";
    cout << "     Quick WithDraw  \n";
    cout << "=====================\n";
    cout << "[1] 10$  " << "[6]250$" << endl;
    cout << "[2] 20$  " << "[7]500$" << endl;
    cout << "[3] 50$  " << "[8]700%" << endl;
    cout << "[4] 100$  " << "[9]1000$" << endl;
    cout << "[5] 200$  " << "[10]10000$" << endl;
    cout << "===========================" << endl;
    cout << "Balance: " << Clinent.AccountBalance << '$' << endl;
    cout << "===========================" << endl;
    short UN;
    if (Erorr)
    {
        cout << "----------------\nThe amount is not enough.\n-------------\n";
        char Y;
        cout << "Are you sure to Quick WithDraw[Y,N]";
        cin >> Y;
        if (tolower(Y) != 'y') ATMManueScreen();
    }
    cout << "Chose from 1 to 10 : ";
    cin >> UN;
    WithDraw(enQuickWithDraw(UN));
}

enum enManueATM {eQuickWithdraw = 1,eNarmalWithDraw = 2,
eDeposit = 3, eCheckBlance = 4,eLogIn = 5};

void ATMApp(enManueATM ManueATM)
{
    switch (ManueATM)
    {
    case eQuickWithdraw:
        QuickWithDraw();
        GoBackATM();
        break;
    case eNarmalWithDraw:
        NarmalWithDraw();
        GoBackATM();
        break;
    case eDeposit:
        Deposit();
        GoBackATM();
        break;
    case eCheckBlance:
        CheckBalance();
        GoBackATM();
        break;
    case eLogIn:
        LogIn();
        break;
    default:
        ShowEndScreen();
        system("pause>0");
        break;
    }
}

void ATMManueScreen()
{
    system("cls");
    cout << "==================================\n";
    cout << "        ATM Main Menue Screen     \n";
    cout << "==================================\n";
    cout << "       [1] Quick WithDraw.        \n";
    cout << "       [2] Narmal WithDraw.       \n";
    cout << "       [3] Deposit.               \n";
    cout << "       [4] Check Blance.          \n";
    cout << "       [5] LogIn.                 \n";
    cout << "===================================" << endl;
    short UN;
    cout << "Chose from 1 to 5 : ";
    cin >> UN;
    ATMApp(enManueATM(UN));
}

int CheckLogIn(string Account,string Pincode)
{
    vector<sClient> AllClient;
    AllClient = LoadCleintsDataFromFile(ClientsFileName);

    for (short i = 0; i < AllClient.size(); i++)
    {
        if (AllClient[i].AccountNumber == Account && AllClient[i].PinCode == Pincode)
            return i;
    }
    return -1;
}

void LogIn(bool Erorr)
{
    do
    {
        system("cls");
        cout << "    )(LogIn)(    " << endl;
        cout << "=================\n";

        string Account;
        string Pincode;
        if (Erorr) cout << "---------\nDoesn't match\n--------\n";
        cout << "Name: ";
        getline(cin >> ws, Account);
        cout << "Pincode: ";
        getline(cin >> ws, Pincode);
        POS = CheckLogIn(Account, Pincode);
        if (POS != -1)
        {
            vector<sClient> AllClient;
            AllClient = LoadCleintsDataFromFile(ClientsFileName);
            Clinent = AllClient[POS];
            ATMManueScreen();
        }
        else
            Erorr = true;

    } while (Erorr);
}

int main()
{
    LogIn();
    return 0;
}