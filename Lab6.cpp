#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <chrono>
#include <ctime>
using namespace std;

using chrono::system_clock;

// Snippet taken from: https://www.programmersought.com/article/52904383003/
std::string current_time()
{
    system_clock::time_point tp = system_clock::now();

    time_t raw_time = system_clock::to_time_t(tp);

    // tm* does not need to be deleted after use, because tm* is created by localtime, and there will be one in each thread
    struct tm *timeinfo = std::localtime(&raw_time);

    char buf[24] = {0};
    // "%F %X," can also be used in standard c++, but not in VC2017
    strftime(buf, 24, "[%Y-%m-%d] %H:%M:%S", timeinfo);

    return std::string(buf);
}

int main(int argc, char *argv[])
{
    int forkRet = fork();
    if (forkRet < 0)
    { //error
        exit(1);
    }
    else if (forkRet == 0)
    { //Child process
        if (execl("/usr/bin/xclock", "myXclock", NULL) == -1)
        {

            // error
            exit(1);
        }
    }
    else
    { //Parent process
        int i = 0;
        while (true)
        {
            i += 1;
            cout << current_time() << endl;
            if (i % 3 == 0)
            {
                cout << "\"This program has gone on for far too long. Type Ctrl+C to abort this timer application.\"" << endl;
            }
            sleep(10);
        }
    }
    return 0;
}
