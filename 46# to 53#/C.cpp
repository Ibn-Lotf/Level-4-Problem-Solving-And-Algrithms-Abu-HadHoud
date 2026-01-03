#include <iostream>
using namespace std;


struct stDate
{
    int Year;
    short Month;
    short Day;
    short DayName;
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

void Number_M_Y_(short Year,short Month,int& y,int& m)
{
    short a = (14 - Month)/12;

    y = Year-a;
    m = Month + 12*a + - 2;
}

short NumberNameDay(stDate Date)
{
    int y,m;
    Number_M_Y_(Date.Year,Date.Month,y,m);
    return (Date.Day + y + y/4 - y/100 + y/400 + (31*m)/12) % 7;
}

string DayTxT(short DayNumber)
{
    string Days[] = {"SunDay","ManDay","TuesDay","WednesDay","ThirstDay","FriDay","SaturDay"};
    return Days[DayNumber];
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
    Date.NumDay = CalculatingTheDaysOfPatience(Date.Year,Date.Month,Date.Day);
    Date.DayName = NumberNameDay(Date);
    return Date;
}

bool IsEndOfWeek(short DayNumber)
{
    return DayNumber == 6;
}

bool IsWeekEnd(short DayNumber)
{
    return DayNumber == 4 || DayNumber == 5;
}

bool IsBusinessDay(short DayNumber)
{
    return !IsWeekEnd(DayNumber);
}

short DaysUntilTheEndOfWeek(short DayNumber)
{
    return 6 - DayNumber;
}

short DaysUntilTheEndOfMonth(stDate Date)
{
    return MonthInYear(Date.Year,Date.Month) - Date.Day;
}

short DaysUntilTheEndOfYear(stDate Date)
{
    Date.Year = (CheckLeapYear(Date.Year) ? 366 : 365);
    return Date.Year - Date.NumDay;
}


int main()
{
    stDate DateNew;
    DateNew = SystemToDate();

    cout << "Today is " << DayTxT(DateNew.DayName);
    cout << " , " << DateNew.Day << '/' << DateNew.Month << '/' << DateNew.Year << endl;

    cout << "\nIs it End Of Week?\n";
    cout << (IsEndOfWeek(DateNew.DayName) ? "Yes, " : "No, ") << endl;

    cout << "\nIs it WeekEnd?\n";
    cout << (IsWeekEnd(DateNew.DayName) ? "Yes, " : "No, ") << endl;

    cout << "\nIs it School?\n";
    cout << (IsBusinessDay(NumberNameDay(DateNew)) ? "Yes, " : "No, ") << endl;

    cout << "Days Until end Of Week: " << DaysUntilTheEndOfWeek(DateNew.DayName) << endl;
    cout << "Days Until end of Month: " << DaysUntilTheEndOfMonth(DateNew) << endl;
    cout << "Days Until end of Year: " << DaysUntilTheEndOfYear(DateNew);
    return 0;
}
