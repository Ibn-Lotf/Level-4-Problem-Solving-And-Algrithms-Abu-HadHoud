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
    int NumDay;
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

int CalculatingTheDaysOfPatience(short Year,short Month,short Day)
{
    short YDay = (CheckLeapYear(Year) ? 366 : 365);
    short MDay = MonthInYear(Year,Month) - Day;
    for (short i = Month+1;i <= 12;i++) MDay += MonthInYear(Year,i);
    return YDay - MDay;
}

stDate FillDate()
{
    stDate Date;
    Date.Year = InputNum("Year: ");
    Date.Month = InputNum("Month: ");
    Date.Day = InputNum("Day: ");
    Date.NumDay = CalculatingTheDaysOfPatience(Date.Year,Date.Month,Date.Day);
    return Date;
}
bool CheckLessDate(stDate Date1,stDate Date2)
{
    if (Date1.Year < Date2.Year) return false;
    if (Date1.Year > Date2.Year)
    {
        return true;
    }else if(Date1.Month > Date2.Month)
    {
        return true;
    }else if (Date1.Day > Date2.Day)
    {
        return true;
    }
    return false;
}

int main()
{
    stDate Date1,Date2;
    Date1 = FillDate();
    cout << endl;
    Date2 = FillDate();

    cout << endl;

    cout << (CheckLessDate(Date2,Date1) ? "Yes, Date1 Less Date2" : "No, ");
}