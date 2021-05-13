#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

void sum(int x[], int y[], int z[], int setNum)
{

    for (int i = 0; i < setNum; i++)
    {
        for (int j = i + 1; j < setNum; j++)
        {

            cout << (abs(x[i] - x[j]) +
                     abs(y[i] - y[j]) + abs(z[i] - z[j]))
                 << endl;
            i++;
        }
    }
}

int main(void)
{

    int testCases;
    scanf("%d", &testCases);

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

        sum(xCoords, yCoords, zCoords, numOfPoints);
    }

    return 0;
}