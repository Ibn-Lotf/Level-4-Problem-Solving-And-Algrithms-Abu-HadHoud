#include <iostream>
using namespace std;

int InputNum(string Hl)
{
    int Number = 0;
    cout << Hl;
    cin >> Number;
    return Number;
}

void Number_M_Y_(short Year,short Month,int& y,int& m)
{
    short a = (14 - Month)/12;

    y = Year-a;
    m = Month + 12*a + - 2;
}

short NumberNameDay(short Year,short Month,short Day)
{
    int y,m;
    Number_M_Y_(Year,Month,y,m);
    return (Day + y + y/4 - y/100 + y/400 + (31*m)/12) % 7;
}

string DayTxT(short DayNumber)
{
    string Days[] = {"SunDay","ManDay","TuesDay","WednesDay","ThirstDay","FriDay","SaturDay"};
    return Days[DayNumber];
}

int main()
{
    short Year = InputNum("Year: ");
    short Month = InputNum("Month: ");
    short Day = InputNum("Day: ");

    cout << "\nDate : " << Day << '/' << Month << '/' << Year;
    cout << "\nDay Number: " << NumberNameDay(Year,Month,Day);
    cout << "\nDay Name: " << DayTxT(NumberNameDay(Year,Month,Day));
    return 0;
}