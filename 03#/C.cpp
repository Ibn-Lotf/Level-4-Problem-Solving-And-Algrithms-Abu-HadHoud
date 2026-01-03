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
    return ((Year % 4 == 0) && (Year % 100 != 0)) || ((Year % 400 == 0));
}

int main()
{
    short Year = InputNum("Year: ");
    cout << (CheckLeapYear(Year) ? "Yes, Leap Year" : "No, Not Leap Year");
    return 0;
}
