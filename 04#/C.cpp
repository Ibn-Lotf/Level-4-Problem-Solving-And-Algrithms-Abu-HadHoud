#include <iostream>
using namespace std;

int InputNum(string Hl)
{
    int Number = 0;
    cout << Hl;
    cin >> Number;
    return Number;
}

bool CheckLeapYear(short Year)
{
    return ((Year % 4 == 0) && (Year % 100 != 0)) || ((Year % 400 == 0));
}

short YearToDay(short Year)
{
    return CheckLeapYear(Year) ? 366 : 365;
}

int DayToHour(short Year)
{
    return YearToDay(Year) * 24;
}

int HourToMinutes(int Year)
{
    return DayToHour(YearToDay(Year)) * 60;
}

int MinutesToSeconde(int Year)
{
    return HourToMinutes(DayToHour(YearToDay(Year))) * 60;
}


int main()
{
    short Year = InputNum("Year: ");
    
    cout << "Day [" << Year << "] : " << YearToDay(Year) << endl;
    cout << "Hour [" << Year << "] : " << DayToHour(Year) << endl;
    cout << "Minutes [" << Year << "] : " << HourToMinutes(Year) << endl;
    cout << "Seconde [" << Year << "] : " << MinutesToSeconde(Year);
    return 0;
}
