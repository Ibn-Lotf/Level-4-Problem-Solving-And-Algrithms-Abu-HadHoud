#include <iostream>
using namespace std;

int InputNum(string Hl)
{
    int Number = 0;
    cout << Hl;
    cin >> Number;
    return Number;
}

bool CheckLeapYear(short Year)
{
    if (Year % 400 == 0)
        return true;

    if (Year % 100 == 0)
        return false;
    
    if (Year % 4 == 0)
        return true;

    return false;
}

int main()
{
    short Year = InputNum("Year: ");
    cout << (CheckLeapYear(Year) ? "Yes, Leap Year" : "No, Not Leap Year");
    return 0;
}
