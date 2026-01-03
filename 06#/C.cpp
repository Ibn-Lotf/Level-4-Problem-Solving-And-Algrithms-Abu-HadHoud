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

short MonthDayInYear(short Month)
{
    short arr[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    return arr[Month-1];
}

short MonthInYear(short Year,short Month)
{
    if (Month < 1 || Month > 12)
        return 0;
    if (Month == 2) return (CheckLeapYear(Year) ? 29 : 28);
    return MonthDayInYear(Month);
}

int DayToHour(short Year,short Month)
{
    return MonthInYear(Year,Month) * 24;
}

int HourToMinutes(int Year,short Month)
{
    return DayToHour(Year,Month) * 60;
}

int MinutesToSeconde(int Year,short Month)
{
    return HourToMinutes(Year,Month) * 60;
}



int main()
{
    short Year = InputNum("Year: ");
    short Month = InputNum("Month: ");
    
    cout << "Day [" << Year << "] : " << MonthInYear(Year,Month) << endl;
    cout << "Hour [" << Year << "] : " << DayToHour(Year,Month) << endl;
    cout << "Minutes [" << Year << "] : " << HourToMinutes(Year,Month) << endl;
    cout << "Seconde [" << Year << "] : " << MinutesToSeconde(Year,Month);
    return 0;
}
