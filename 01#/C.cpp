#include <iostream>
#include <string>
using namespace std;


int InputNum(string Hl)
{
    int Number = 0;
    cout << Hl;
    cin >> Number;
    return Number;
}

string NumberToWords(long Number)
{
    if (Number == 0)
    {
        return "";
    }

    if (Number > 0 && Number < 19)
    {
        string Ones[] = { "","One","Two","Three","Four"
        ,"Five","Six","Seven","Eight","Nine","Ten","Eleven"
        ,"Twelve","Thirteen","Fourteen","Fifteen","Sixteen"
        ,"Seventeen","Eighteen","Nineteen" };
        return Ones[Number] + " ";
    }

    if (Number >= 20 && 99 >= Number)
    {
        string Thans[] = { "","","Twenty","Thirty","Forty"
        ,"Fifty","Sixty","Seventy","Eighty","Ninety" };
        return Thans[Number / 10] + " " + NumberToWords(Number % 10);
    }

    if (Number >= 100 && 199 >= Number)
    {
        return "One Hundred " + NumberToWords(Number % 100);
    }

    if (Number >= 200 && Number <= 999)
    {
        return NumberToWords(Number / 100) + "Hundred " + NumberToWords(Number % 100);
    }

    if (Number >= 1000 && 1999 >= Number)
    {
        return "One Thandes " + NumberToWords(Number % 1000);
    }

    if (Number >= 2000 && Number <= 999999)
    {
        return NumberToWords(Number / 1000) + "Thandes " + NumberToWords(Number % 1000);
    }

    if (Number >= 1000000 && 1999999 >= Number)
    {
        return "One Million " + NumberToWords(Number % 1000000);
    }

    if (Number >= 2000000 && Number <= 999999999)
    {
        return NumberToWords(Number / 1000000) + "Million " + NumberToWords(Number % 1000000);
    }

    if (Number >= 1000000000 && 1999999999 >= Number)
    {
        return "One Billion " + NumberToWords(Number % 1000000000);
    }

    if (Number >= 2000000000 && Number <= 999999999)
    {
        return NumberToWords(Number / 1000000000) + "Billion " + NumberToWords(Number % 1000000000);
    }

    return "";
}

int main()
{
    cout << NumberToWords(InputNum("Num: "));
    return 0;
}