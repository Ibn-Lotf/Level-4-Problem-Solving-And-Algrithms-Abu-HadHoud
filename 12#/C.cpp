#include <iostream>
using namespace std;

int InputNum(string Hl)
{
    int Number = 0;
    cout << Hl;
    cin >> Number;
    return Number;
}

struct stDate
{
    short Year;
    short Month;
    short Day;
};

bool CheckLeapYear(short Year)
{
    return ((Year % 4 == 0) && (Year % 100 != 0)) || ((Year % 400 == 0));
}

short MonthDayInYear(short Month)
{
    short arr[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    return arr[Month-1];
}

short MonthInYear(short Year, short Month)
{
    if (Month < 1 || Month > 12)
        return 0;
    if (Month == 2) return (CheckLeapYear(Year) ? 29 : 28);
    return MonthDayInYear(Month);
}

stDate POSYearToDate(short POSDay,short &Year)
{
    stDate Date;

    Date.Month = 1;
    short Experience = POSDay;

    while (true)
    {
        short DayMonth = MonthDayInYear(Date.Month);
        short DayYear = (CheckLeapYear(Year) ? 366 : 365);
        if (Experience > DayYear)
        {
            Year++;
            Experience -= DayMonth;
        }
        else if (Experience > DayMonth)
        {
            Date.Month++;
            Experience -= DayYear;
        }
        else
        {
            Date.Day = Experience;
            break;
        }
    }
    return Date;
}

void PrintPOSDateToDate(short Year,short POSDay)
{
    stDate Date = POSYearToDate(POSDay,Year);
    Date.Year = Year;

    cout << endl << Date.Day << '/' << Date.Month << '/' << Date.Year;
}

short CalculatingTheDaysOfPatience(short Year,short Month,short Day)
{
    short YDay = (CheckLeapYear(Year) ? 366 : 365);
    short MDay = MonthInYear(Year,Month) - Day;
    for (short i = Month+1;i <= 12;i++) MDay += MonthInYear(Year,i);
    return YDay - MDay;
}

int main()
{
    short Year = InputNum("Year: ");
    short Month = InputNum("Month: ");
    short Day = InputNum("Day: ");
    short DayBlas = InputNum("Day ++: ");

    PrintPOSDateToDate(Year,CalculatingTheDaysOfPatience(Year,Month,Day)+DayBlas);
}