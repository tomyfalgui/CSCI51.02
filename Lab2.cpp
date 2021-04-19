#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main(void)
{
    int numLines;
    string s;
    getline(cin, s);
    numLines = atoi(s.c_str());

    for (int i = 0; i < numLines; i++)
    {
        int pos1;
        int pos2;
        string restOfLine;
        scanf("%d %d", &pos1, &pos2);
        getline(cin, restOfLine);
        printf("Agent #%d is at (%d, %d)\n", i + 1, pos1, pos2);
        cout << "Says:" << restOfLine << endl;
    }

    return 0;
}
