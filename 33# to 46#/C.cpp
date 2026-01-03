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

bool CheckDayOfMonthStart(short Day)
{
    return  Day == 1;
}

bool CheckMonthOfYearStart(short Month)
{
    return Month == 1;
}


stDate MinusDayInDate(stDate& Date)
{
    if (CheckDayOfMonthStart(Date.Day))
    {
        if (CheckMonthOfYearStart(Date.Month))
        {
            Date.Month = 1;
            Date.Day = 31;
            Date.Year--;
        }
        else
        {
            Date.Month--;
            Date.Day = MonthInYear(Date.Year,Date.Month);
        }
    }else
    {
        Date.Day--;
    }
    return Date;
}

stDate MinusDayInDate(stDate& Date,short Days)
{
    for (short i = 1;i <= Days;i++)  MinusDayInDate(Date);
    return Date;
}

stDate MinusWeekInDate(stDate& Date)
{
    MinusDayInDate(Date,7);
    return Date;
}

stDate MinusWeekInDate(stDate& Date,short Weeks)
{
    for(short i = 1;i <= Weeks;i++)MinusDayInDate(Date,7);
    return Date;
}

stDate MinusMonthInDate(stDate &Date)
{
    if (CheckDayOfMonthStart(Date.Month))
    {
        Date.Month = 12;
        Date.Year--;
    }else
    {
        Date.Month--;
    }

    short NumbDayInMonth = MonthDayInYear(Date.Month);
    if (Date.Day > NumbDayInMonth)
        Date.Day = NumbDayInMonth;

    return Date;
}

stDate MinusMonthInDate(stDate &Date,short Months)
{
    for (short i = 1;i <= Months;i++) MinusMonthInDate(Date);
    return Date;
}

stDate MinusYearInDate(stDate &Date,short Year = 1)
{
    Date.Year -= Year;
    return Date;
}

stDate MinusDecadeInDate(stDate &Date,short Decade = 1)
{
    Date.Year -= Decade * 10;
    return Date;
}

stDate MinusCentryInDate(stDate &Date)
{
    Date.Year -= 100;
    return Date;
}

stDate MinusMillenniumInDate(stDate &Date)
{
    Date.Year -= 1000;
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

    Date = MinusDayInDate(Date);
    cout << "\n Minus Day Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = MinusDayInDate(Date,10);
    cout << "\n Minus Day 10 Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = MinusWeekInDate(Date);
    cout << "\n Minus Week Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = MinusWeekInDate(Date,10);
    cout << "\n Minus Week 10 Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = MinusMonthInDate(Date);
    cout << "\n Minus Month Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = MinusMonthInDate(Date,5);
    cout << "\n Minus Month 5 Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = MinusYearInDate(Date);
    cout << "\n Minus Year Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = MinusYearInDate(Date,10);
    cout << "\n Minus Year 10 Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = MinusDecadeInDate(Date);
    cout << "\n Minus Decade Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = MinusDecadeInDate(Date,10);
    cout << "\n Minus Decade 10 Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = MinusCentryInDate(Date);
    cout << "\n Minus Centry Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;

    Date = MinusMillenniumInDate(Date);
    cout << "\n Minus Centry Of Date: " << Date.Day << '/' << Date.Month << '/' << Date.Year;
}