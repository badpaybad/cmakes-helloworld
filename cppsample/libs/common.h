
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

#ifndef GLOBAL_STRING_EMTPY
#define GLOBAL_STRING_EMTPY
#define __stringEmpty std::string("")
#endif
#ifndef GLOBAL_VOID_EMPTY
#define GLOBAL_VOID_EMPTY
#define __voidEmpty std::function<void(std::string)>()
#endif

#ifndef CLASS_TASK_JSON
#define CLASS_TASK_JSON

struct MyLatLng
{
    int x, y;
    MyLatLng(int x1, int y1)
    {
        x = x1;
        y = y1;
    }
};

struct TaskJson
{
public:
    std::string jsonData;
    std::function<void(std::string)> handle;

    TaskJson()
    {
        jsonData = __stringEmpty;
        handle = NULL;
    }

    TaskJson(std::string jsonDataToHandle, std::function<void(std::string)> actionHandle)
    {
        jsonData = jsonDataToHandle;

        handle = actionHandle;
    }
    bool operator==(TaskJson input)
    {
        // std::cout << "\r\n--------------\r\n";
        // std::cout << (jsonData);
        // std::cout << "\r\n";
        // std::cout << (&handle);
        // std::cout << "\r\n";
        // std::cout << (input.jsonData);        
        // std::cout << "\r\n";
        // std::cout << (&input.handle);
        // std::cout << "\r\n-----------\r\n";

        //compare value
        return jsonData == input.jsonData
               //function dont have value, compare address
               && &handle == &input.handle;
    }

    bool operator!=(TaskJson input)
    {
        return jsonData != input.jsonData || &handle != &input.handle;
    }

    // TaskJson &operator=(const TaskJson &other)
    // {
    //     std::cout << "fuk";
    //     // Guard self assignment
    //     if (this == &other)
    //         return *this;

    //     jsonData = other.jsonData;
    //     handle = other.handle;

    //     return *this;
    // }
};

#define __taskJsonNull TaskJson(__stringEmpty, __voidEmpty)

#define __myLatLngNull MyLatLng(NULL, NULL)
#endif
