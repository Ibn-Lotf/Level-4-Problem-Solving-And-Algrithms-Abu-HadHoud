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

string ReplaceWordInString(string NewWord,string Word,string txt)
{
    int pos = txt.find(Word);

    while (pos != string::npos)
    {
        txt.replace(pos,Word.length() ,NewWord);
        pos = txt.find(Word);
    }

    return txt;
}

string HappyDate(stDate_2 Date,string DateFrem = "dd/mm/yyyy")
{
    string DateNew = "";
    DateNew = ReplaceWordInString(to_string(Date.Day),"dd",DateFrem);
    DateNew = ReplaceWordInString(to_string(Date.Month),"mm",DateNew);
    DateNew = ReplaceWordInString(to_string(Date.Year),"yyyy",DateNew);
    return DateNew;
}

int main()
{
    string STR = InputString("Date: ");
    stDate_2 Date = StringToDate(STR);

    cout << HappyDate(Date,"yyyy/dd/mm");
    return 0;
}