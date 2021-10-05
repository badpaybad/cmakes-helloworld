
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>

#include <chrono>
#include <ctime>
#include <thread>
#include <mutex>
#include <functional>

#include <stack>
#include <map>
#include <queue>
#include <tuple>

#ifndef __global_log
#define __global_log
void __log(std::string msg)
{
    std::cout << msg;
}
#endif
