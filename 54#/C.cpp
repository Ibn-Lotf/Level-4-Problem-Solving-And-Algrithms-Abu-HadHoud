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

short CalculatingTheDaysOfPatience(short Year,short Month,short Day)
{
    short YDay = (CheckLeapYear(Year) ? 366 : 365);
    short MDay = MonthDayInYear(Month) - Day;
    for (short i = Month+1;i <= 12;i++) MDay += MonthDayInYear(Year,i);
    return YDay - MDay;
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

stDate FillDate()
{
    stDate Date;
    Date.Year = InputNum("Year: ");
    Date.Month = InputNum("Month: ");
    Date.Day = InputNum("Day: ");
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

void SwapDate(stDate& Date1,stDate& Date2)
{
    stDate Temp;
    Temp = Date1;
    Date1 = Date2;
    Date2 = Temp;
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

int DifferenceDate1ToDate2(stDate Date1,stDate Date2,bool In = false)
{
    int Difference = 0;
    short Minus = 1;
    
    if (CheckLessDate(Date1,Date2))
    {
        SwapDate(Date1,Date2);
        Minus = -1;
    }

    while (true)
    {
        if (Date2.Year > Date1.Year)
        {
            Difference += (CheckLeapYear(Date1.Year) ? 366 : 365);
            Date1.Year++;
        }
        else if(Date2.Month > Date1.Month)
        {
            Difference += MonthDayInYear(Date1.Year,Date1.Month);
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
    return (In ? (Difference+1)*Minus : Difference*Minus);
}

int ActualVacationDays(stDate Date1,stDate Date2)
{
    int Counter = 0;
    int Diff = DifferenceDate1ToDate2(Date1,Date2);
    for (short i = Date1.DayName;Diff > 0;Diff--)
    {
        if (IsBusinessDay(i))
            Counter++;
        if (i == 6)
            i = 0;
        else
            i++;
    }
    return Counter;
}

int main()
{
    stDate Date1,Date2;
    cout << "Vacation Start:\n";
    Date1 = FillDate();

    cout << "Vacation End:\n";
    Date2 = FillDate();

    cout << "Vacation From: " << Date1.Day << '/' << Date1.Month << '/' << Date1.Year << endl;
    cout << "Vacation To: " << Date2.Day << '/' << Date2.Month << '/' << Date2.Year << endl;
    cout << "Actual Vacation is Days: " << ActualVacationDays(Date1,Date2);
    return 0;
}