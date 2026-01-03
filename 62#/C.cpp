#include <iostream>
using namespace std;

enum enDateCheckTool
{
    Befor = -1,
    Equal = 0,
    After = 1
};

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

struct stPeriod
{
    stDate StartDate;
    stDate EndDate;
};

bool CheckLeapYear(short Year)
{
    return ((Year % 4 == 0) && (Year % 100 != 0)) || ((Year % 400 == 0));
}

short MonthDayInYear(short Month)
{
    short arr[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return arr[Month - 1];
}

short MonthInYear(short Year, short Month)
{
    if (Month < 1 || Month > 12)
        return 0;
    if (Month == 2)
        return (CheckLeapYear(Year) ? 29 : 28);
    return MonthDayInYear(Month);
}

short CalculatingTheDaysOfPatience(short Year, short Month, short Day)
{
    short YDay = (CheckLeapYear(Year) ? 366 : 365);
    short MDay = MonthInYear(Year, Month) - Day;
    for (short i = Month + 1; i <= 12; i++)
        MDay += MonthInYear(Year, i);
    return YDay - MDay;
}

void Number_M_Y_(short Year, short Month, int &y, int &m)
{
    short a = (14 - Month) / 12;

    y = Year - a;
    m = Month + 12 * a + -2;
}

short NumberNameDay(stDate Date)
{
    int y, m;
    Number_M_Y_(Date.Year, Date.Month, y, m);
    return (Date.Day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
}

string DayTxT(short DayNumber)
{
    string Days[] = {"SunDay", "ManDay", "TuesDay", "WednesDay", "ThirstDay", "FriDay", "SaturDay"};
    return Days[DayNumber];
}

stDate FillDate()
{
    stDate Date;
    Date.Year = InputNum("Year: ");
    Date.Month = InputNum("Month: ");
    Date.Day = InputNum("Day: ");
    Date.NumDay = CalculatingTheDaysOfPatience(Date.Year, Date.Month, Date.Day);
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

void SwapDate(stDate &Date1, stDate &Date2)
{
    stDate Temp;
    Temp = Date1;
    Date1 = Date2;
    Date2 = Temp;
}

bool CheckLessDate(stDate Date1, stDate Date2)
{
    if (Date1.Year < Date2.Year)
        return false;
    if (Date1.Year > Date2.Year)
    {
        return true;
    }
    else if (Date1.Month > Date2.Month)
    {
        return true;
    }
    else if (Date1.Day > Date2.Day)
    {
        return true;
    }
    return false;
}

int DifferenceDate1ToDate2(stDate Date1, stDate Date2, bool In = false)
{
    int Difference = 0;
    short Minus = 1;

    if (CheckLessDate(Date1, Date2))
    {
        SwapDate(Date1, Date2);
        Minus = -1;
    }

    while (true)
    {
        if (Date2.Year > Date1.Year)
        {
            Difference += (CheckLeapYear(Date1.Year) ? 366 : 365);
            Date1.Year++;
        }
        else if (Date2.Month > Date1.Month)
        {
            Difference += MonthInYear(Date1.Year, Date1.Month);
            Date1.Month++;
        }
        else if (Date2.Day > Date1.Day)
        {
            Difference += Date2.Day - Date1.Day;
            Date1.Day = Date2.Day;
        }
        else
            break;
    }
    return (In ? (Difference + 1) * Minus : Difference * Minus);
}

int ActualVacationDays(stDate Date1, stDate Date2)
{
    int Counter = 0;
    int Diff = DifferenceDate1ToDate2(Date1, Date2);
    for (short i = Date1.DayName; Diff > 0; Diff--)
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

bool CheckDayOfMonthEnd(short Day, short Month, short Year)
{
    return Day == MonthInYear(Year, Month);
}

bool CheckMonthOfYearEnd(short Month)
{
    return Month == 12;
}

bool CheckEqualDate(stDate Date1, stDate Date2)
{
    return (Date1.Year == Date2.Year ? Date1.Month == Date2.Month ? Date1.Day == Date2.Day ? true : false : false : false);
}

bool CheckDate1AfterDate2(stDate Date1, stDate Date2)
{
    return (!CheckLessDate(Date1, Date2) && !(CheckEqualDate(Date1, Date2)));
}

stDate AddDayInDate(stDate &Date)
{
    if (CheckDayOfMonthEnd(Date.Day, Date.Month, Date.Year))
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
    }
    else
    {
        Date.Day++;
    }
    return Date;
}

stDate AddDayInDate(stDate &Date, short Days)
{
    for (short i = 1; i <= Days; i++)
        AddDayInDate(Date);
    return Date;
}

stDate ActualVacationDaysRE(stDate Date, int Days)
{
    for (short i = Date.DayName; Days > 0; Days--)
    {
        AddDayInDate(Date);
        if (IsWeekEnd(i))
            Days++;
        if (i == 6)
            i = 0;
        else
            i++;
    }
    return Date;
}

enDateCheckTool CheckDateTool(stDate Date1, stDate Date2)
{
    if (CheckLessDate(Date1, Date2))
    {
        return enDateCheckTool::Befor;
    }
    else if (CheckEqualDate(Date1, Date2))
    {
        return enDateCheckTool::Equal;
    }

    return enDateCheckTool::After;
}

stPeriod FillPeriod()
{
    stPeriod Period;
    cout << "Period: \n";
    Period.StartDate = FillDate();
    Period.EndDate = FillDate();
    return Period;
}

bool CheckP2JunctionP2(stPeriod Period1, stPeriod Period2)
{
    if (CheckDateTool(Period1.EndDate, Period2.StartDate) == enDateCheckTool::After || CheckDateTool(Period1.StartDate, Period2.EndDate) == enDateCheckTool::Befor)
        return false;
    return true;
}

bool CheckDateInPeriod(stDate Date, stPeriod Period)
{
    return !(CheckDateTool(Date, Period.StartDate) == enDateCheckTool::After || CheckDateTool(Date, Period.EndDate) == enDateCheckTool::Befor);
}

int DifferencePeriod(stPeriod Period, bool DayIn = false)
{
    return DifferenceDate1ToDate2(Period.StartDate, Period.EndDate, DayIn);
}

int DaysJunction(stPeriod Period1, stPeriod Period2)
{
    if (!CheckP2JunctionP2(Period1, Period2))
        return 0;
    int DaysCount = 0;
    int DaysPeriod1 = DifferencePeriod(Period1, true);
    int DaysPeriod2 = DifferencePeriod(Period2, true);

    if (DaysPeriod1 > DaysPeriod2)
    {
        while (CheckDate1AfterDate2(Period1.StartDate, Period1.EndDate))
        {
            if (CheckDateInPeriod(Period1.StartDate, Period2))
            {
                DaysCount++;
            }
            AddDayInDate(Period1.StartDate);
        }
    }
    else
    {
        while (CheckDate1AfterDate2(Period2.StartDate, Period2.EndDate))
        {
            if (CheckDateInPeriod(Period2.StartDate, Period1))
            {
                DaysCount++;
            }
            AddDayInDate(Period2.StartDate);
        }
    }
    return DaysCount - 1;
}

bool CheckDate(stDate Date)
{
    if (Date.Day < 1 || Date.Day > MonthInYear(Date.Year,Date.Month) 
    || MonthInYear(Date.Year,Date.Month) == 0) return false;
    return true;
}

int main()
{
    stDate Date;
    Date = FillDate();

    cout << (CheckDate(Date) ? "Yes, " : "No, ");
    cout << "is Date.";
    return 0;
}