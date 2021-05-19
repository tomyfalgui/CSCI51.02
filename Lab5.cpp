#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

string sum(int x[], int y[], int z[], int setNum)
{

    string returnValue = "";

    for (int i = 0; i < setNum; i++)
    {
        for (int j = i + 1; j < setNum; j++)
        {

            returnValue += to_string(abs(x[i] - x[j]) +
                                     abs(y[i] - y[j]) + abs(z[i] - z[j])) +
                           "\n";
            i++;
        }
    }

    return returnValue;
}

int main(void)
{

    int testCases;
    scanf("%d", &testCases);
    string answer;

    for (int testCaseCount = 0; testCaseCount < testCases; testCaseCount++)
    {
        int numOfPoints;
        scanf("%d", &numOfPoints);

        int xCoords[numOfPoints];
        int yCoords[numOfPoints];
        int zCoords[numOfPoints];

        for (int pointSetCount = 0; pointSetCount < numOfPoints; pointSetCount++)
        {
            int x;
            int y;
            int z;
            scanf("%d %d %d", &x, &y, &z);
            xCoords[pointSetCount] = x;
            yCoords[pointSetCount] = y;
            zCoords[pointSetCount] = z;
        }

        answer += sum(xCoords, yCoords, zCoords, numOfPoints);
    }

    cout << answer;

    return 0;
}