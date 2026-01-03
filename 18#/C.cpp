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

short CalculatingTheDaysOfPatience(short Year,short Month,short Day)
{
    short YDay = (CheckLeapYear(Year) ? 366 : 365);
    short MDay = MonthInYear(Year,Month) - Day;
    for (short i = Month+1;i <= 12;i++) MDay += MonthInYear(Year,i);
    return YDay - MDay;
}

stDate SystemToDate()
{
    stDate Date;

    time_t t = time(0);
    tm* now = localtime(&t);

    Date.Year = now->tm_year + 1900;
    Date.Month = now->tm_mon + 1;
    Date.Day = now->tm_mday;

    return Date;
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

int DifferenceDate1ToDate2(stDate Date1,stDate Date2,bool In = false)
{
    int Difference = 0;

    while (true)
    {
        if (Date2.Year > Date1.Year)
        {
            Difference += (CheckLeapYear(Date1.Year) ? 366 : 365);
            Date1.Year++;
        }
        else if(Date2.Month > Date1.Month)
        {
            Difference += MonthInYear(Date1.Year,Date1.Month);
            Date1.Month++;
        }
        else if(Date2.Day > Date1.Day)
        {
            Difference += Date2.Day - Date1.Day;
            Date1.Day = Date2.Day;
        }
        else
            break;
    }
    
    return (In ? Difference+1 : Difference);
}


int main()
{
    stDate Date1,DateSystem;
    Date1 = FillDate();
    cout << endl;
    DateSystem = SystemToDate();

    cout << endl;

    cout << "Difference (In) Day -<(Agu): " << DifferenceDate1ToDate2(Date1,DateSystem,true) << " Day(s)\n";
}