#include <iostream>
#include <cstring>
using namespace std;

string obfuscateName(string name)
{
    int strLength = name.size();
    string obfuscatedString;

    for (int i = 0; i < strLength; i++)
    {
        if (i != 0)
        {
            obfuscatedString += "#";
        }
        else
        {
            obfuscatedString += name[i];
        }
    }

    return obfuscatedString;
}

void shiftName(char *nameChar)
{
    if (*nameChar >= 'a' && *nameChar <= 'z')
    {
        *nameChar = *nameChar + 1;
        if (*nameChar > 'z')
        {
            *nameChar = *nameChar - 'z' + 'a' - 1;
        }
    }
    else if (*nameChar >= 'A' && *nameChar <= 'Z')
    {
        *nameChar = *nameChar + 1;
        if (*nameChar > 'Z')
        {
            *nameChar = *nameChar - 'Z' + 'A' - 1;
        }
    }
    // symbols
    else
    {
        *nameChar = *nameChar;
    }
}

int main(void)
{
    string name;
    cout << "What's your name? ";
    // for 0-length inputs
    // getline discards delimitation characters
    // such as '\n', '\0', etc.
    getline(cin, name);

    if (name.size() > 0)
    {
        // print name
        cout << "1. " << name << endl;
        // print name with #
        cout << "2. " << obfuscateName(name) << endl;
        //  shift name
        for (int i = 0; i < name.size(); i++)
        {
            shiftName(&name[i]);
        }
        cout << "3. " << name << endl;
    }
    return 0; // non-zero means an error
}