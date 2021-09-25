
#include <stdio.h>
#include <iostream>
#include <string>

#include <chrono>
#include <ctime>
#include <thread>
#include <mutex>
#include <functional>

#include <stack>
#include <map>
#include <queue>

#ifndef __namespace__ProgramContext
#define __namespace__ProgramContext

namespace ProgramContext
{
    std::mutex __lockGlobal;
    std::string __version = "version 1";

    int __stop = 0;
    std::string __baseDir = ".";

    void init(int argc, char *argv[])
    {
        int __stop = 0;
        std::string argv_str(argv[0]);
        std::replace(argv_str.begin(), argv_str.end(), '\\', '/');
        __baseDir = argv_str.substr(0, argv_str.find_last_of("/"));
    }

    int exit()
    {
        if (ProgramContext::__lockGlobal.try_lock())
        {
            ProgramContext::__stop = 1;
            ProgramContext::__lockGlobal.unlock();
        }
        return 0;
    }

}

#endif