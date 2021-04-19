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
        // int pos1;
        // int pos2;
        // scanf("%d %d %s", &pos1, &pos2, s);
        char s[80]; // limit of 80 characters
        fgets(s, 80, stdin);
        printf("You typed: %s", s);
        // printf("Agent #%d is at (%d, %d)\n", i + 1, pos1, pos2);
        // sprintf("Says: %d %d", s[0], s[2]);
    }

    return 0;
}
