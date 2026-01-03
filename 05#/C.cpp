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

short MonthInYear(short Year,short Month)
{
    if (Month < 1 || Month > 12)
        return 0;

    if (Month == 2)
        return (CheckLeapYear(Year) ? 29 : 28);
    
    short arr[] = {1,3,5,7,8,10,12};

    for (short a : arr)
    {
        if (Month == a)
            return 31;
    }

    return 30;
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
