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
    int Year;
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

bool CheckDayOfMonthEnd(short Day,short Month,short Year)
{
    return  Day == MonthInYear(Year,Month);
}

bool CheckMonthOfYearEnd(short Month)
{
    return Month == 12;
}

stDate AddDayInDate(stDate& Date)
{
    if (CheckDayOfMonthEnd(Date.Day,Date.Month,Date.Year))
    {
        if (CheckMonthOfYearEnd(Date.Month))
        {
            Date.Day = 1;
            Date.Month = 1;
            Date.Year++;
        }
        else
        {
            Date.Day = 1;
            Date.Month++;
        }
    }else
    {
        Date.Day++;
    }
    return Date;
}

stDate AddDayInDate(stDate& Date,short Days)
{
    for (short i = 1;i <= Days;i++)  AddDayInDate(Date);
    return Date;
}

stDate AddWeekInDate(stDate& Date)
{
    AddDayInDate(Date,7);
    return Date;
}

stDate AddWeekInDate(stDate& Date,short Weeks)
{
    for(short i = 1;i <= Weeks;i++)AddDayInDate(Date,7);
    return Date;
}

stDate AddMonthInDate(stDate &Date)
{
    if (CheckMonthOfYearEnd(Date.Month))
    {
        Date.Month = 1;
        Date.Year++;
    }else
    {
        Date.Month++;
    }

    short NumbDayInMonth = MonthDayInYear(Date.Month);
    if (Date.Day > NumbDayInMonth)
        Date.Day = NumbDayInMonth;

    return Date;
}

stDate AddMonthInDate(stDate &Date,short Months)
{
    for (short i = 1;i <= Months;i++) AddMonthInDate(Date);
    return Date;
}

stDate AddYearInDate(stDate &Date,short Year = 1)
{
    for (short i = 1;i <= Year;i++)AddMonthInDate(Date,12);
    return Date;
}

stDate AddDecadeInDate(stDate &Date,short Decade = 1)
{
    for (short i = 1;i <= Decade;i++) AddYearInDate(Date,10);
    return Date;
}

stDate AddCentryInDate(stDate &Date)
{
    AddDecadeInDate(Date,10);
    return Date;
}

stDate AddMillenniumInDate(stDate &Date)
{
    AddDecadeInDate(Date,100);
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


int main()
{
    stDate Date;
    Date = FillDate();

    Date = AddDayInDate(Date);
    cout << "\n Add Day Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = AddDayInDate(Date,10);
    cout << "\n Add Day 10 Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = AddWeekInDate(Date);
    cout << "\n Add Week Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = AddWeekInDate(Date,10);
    cout << "\n Add Week 10 Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = AddMonthInDate(Date);
    cout << "\n Add Month Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = AddMonthInDate(Date,5);
    cout << "\n Add Month 5 Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = AddYearInDate(Date);
    cout << "\n Add Year Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = AddYearInDate(Date,10);
    cout << "\n Add Year 10 Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = AddDecadeInDate(Date);
    cout << "\n Add Decade Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = AddDecadeInDate(Date,10);
    cout << "\n Add Decade 10 Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = AddCentryInDate(Date);
    cout << "\n Add Centry Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;
}