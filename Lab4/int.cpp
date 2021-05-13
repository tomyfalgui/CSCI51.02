#include <iostream>
using namespace std;

int adderShifter(int x, int sum1, int y)
{
    while (x)
    {

        if (x & 1)
        {

            sum1 = sum1 + y;
        }

        x = x >> 1;
        y = y << 1;
    }
    return sum1;
}

int mul(int x, int y)
{
    int sum1 = 0;
    int newNum = 0;
    if (x < 0)
    {
        x = 0 - x;
        sum1 = adderShifter(x, sum1, y);
        sum1 = 0 - sum1;
        return sum1;
    }
    else
    {
        return adderShifter(x, sum1, y);
    }
}

int main(void)
{

    cout << mul(19, 3) << endl;
    cout << mul(45, -2) << endl;
    cout << mul(-5, -3) << endl;
    cout << mul(5, 0) << endl;
    cout << mul(0, 0) << endl;
    return 0;
}