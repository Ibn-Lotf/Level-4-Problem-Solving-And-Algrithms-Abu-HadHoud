#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int InputNum(string Hl)
{
    int Number = 0;
    cout << Hl;
    cin >> Number;
    return Number;
}

void Number_M_Y_(short Year, short Month, int& y, int& m)
{
    short a = (14 - Month) / 12;

    y = Year - a;
    m = Month + 12 * a + -2;
}

short NumberNameDay(short Year, short Month, short Day)
{
    int y, m;
    Number_M_Y_(Year, Month, y, m);
    return (Day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
}

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


void PrintDayMonth(short NumbersOfDay,short DayNum)
{
    printf(" Sun Mun Tue Wed Thi Fir Sat");
    cout << endl;
    
    short i;
    for (i = 0 ;i < DayNum;i++) cout << "    ";

    for (short j = 1; j <= NumbersOfDay; j++)
    {
        cout << setw(4) << j;

        if (++i == 7)
        {
            cout << endl;
            i = 0;
        }
    }
}

void PrintDate(short Year, short Month)
{
    string MonthName[] = { "Jan","Feb","Mar",
        "Apr","May","Jun","Jul","Aug","Sep","Oct",
        "Nov","Dec" };
    cout << "===========" << MonthName[Month-1] << "===========" << endl;
    PrintDayMonth(MonthDayInYear(Month),NumberNameDay(1,Year,Month));
    cout << "\n=============================";
}

int main()
{
    short Year = InputNum("Year: ");
    short Month = InputNum("Month: ");

    PrintDate(Year,Month);
    return 0;
}