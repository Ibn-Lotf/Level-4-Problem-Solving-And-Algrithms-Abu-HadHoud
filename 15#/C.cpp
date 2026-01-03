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

bool CheckDayOfMonthEnd(short Day,short Month,short Year)
{
    return  Day == MonthInYear(Year,Month);
}

bool CheckMonthOfYearEnd(short Month)
{
    return Month == 12;
}

int main()
{
    short Year = InputNum("Year: ");
    short Month = InputNum("Month: ");
    short Day = InputNum("Day: ");

    cout << (CheckDayOfMonthEnd(Day,Month,Year) ? "Yes, True Day" : "No, ") << endl;
    cout << (CheckMonthOfYearEnd(Month) ? "Yes, True Month" : "No, ") << endl;
}