#include <iostream>
#include <string>
using namespace std;

string InputString(string Hl)
{
    cout << Hl;
    cin >> Hl;
    return Hl;
}

struct stDate_2
{
    int Day;
    int Month;
    int Year;
};

stDate_2 StringToDate(string txt)
{
    int pos = txt.find('/');
    stDate_2 Date;

    Date.Day = stoi(txt.substr(0,pos));
    txt.erase(0,pos+1);

    pos = txt.find('/');
    Date.Month = stoi(txt.substr(0,pos));
    txt.erase(0,pos+1);

    Date.Year = stoi(txt);

    return Date;
}

string DateToString(stDate_2 Date)
{
    return (to_string(Date.Day) + '/' 
    + to_string(Date.Month) + '/' + to_string(Date.Year));
}

int main()
{
    string STR = InputString("Date: ");
    stDate_2 Date = StringToDate(STR);
    cout << "\n Struc \n";
    cout << "Day: " << Date.Day << endl;
    cout << "Month: " << Date.Month << endl;
    cout << "Year: " << Date.Year << endl;

    cout << DateToString(Date);
    return 0;
}