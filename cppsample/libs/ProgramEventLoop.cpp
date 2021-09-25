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
#include <tuple>

#include "common.h"

#include "ProgramContext.cpp"

#ifndef CLASS_PROGRAM_EVENT_LOOP
#define CLASS_PROGRAM_EVENT_LOOP

/**
 * @brief 
 * class for queue action do in other thread, no block current
 */
class ProgramEventLoop
{
    //std::mutex &__lockGlobal;
    std::mutex __lockEventLoop;
    std::queue<TaskJson> __qVoid;
    int __stop = 1;
    int __runing = 0;
    std::thread __threadEventLoop;

    void thread_queue_action_invoke()
    {

        TaskJson t(__taskJsonNull.jsonData, __taskJsonNull.handle);
        int shouldInvoke = 0;

        while (true)
        {
            if (__stop == 1)
            {
                break;
            }

            if (__lockEventLoop.try_lock())
            {
                if (__qVoid.size() > 0)
                {
                    t = __qVoid.front();
                    __qVoid.pop();
                    shouldInvoke = 1;
                }
                else
                {
                    shouldInvoke = 0;
                }
                __lockEventLoop.unlock();
            }

            if (shouldInvoke == 1 && t != __taskJsonNull)
            {
                if (t.handle)
                {
                    // do fire and forget, if too much can overheat CPU, can do semarphore lock to keep concurrent thread runing
                    //std::thread ta(a);

                    //do block one by one
                    //t->handle(&t->jsonData);
                    t.handle(t.jsonData);
                    // try
                    // {
                    //     delete[] & t;
                    // }
                    // catch (char *ex)
                    // {
                    //     __log(ex);
                    // }
                }
            }

            //std::this_thread::sleep_for(std::chrono::nanoseconds(1));//this stress CPU
            std::this_thread::sleep_for(std::chrono::microseconds(1)); // this oki
        }

        if (__lockEventLoop.try_lock())
        {
            __runing = 0;
            __lockEventLoop.unlock();
        }
    }
;
public:
    ProgramEventLoop() : __threadEventLoop()
    {
    }

    ~ProgramEventLoop()
    {
        stop();

        delete[] & __threadEventLoop;
    }
    /**
     * @brief 
     * queue_action , void func will run in other thread, no block current
     * @param a void function callable
     * @return int 
     */
    void queue_action(TaskJson task)
    {
        if (__lockEventLoop.try_lock())
        {
            __qVoid.push(task);
            __lockEventLoop.unlock();
        }
    }
    /**
     * @brief 
     * 
     */
    void start()
    {
        if (__lockEventLoop.try_lock())
        {
            if (__runing == 1)
            {
                return;
            }

            __runing = 1;
            __lockEventLoop.unlock();
        }

        __stop = 0;

        __threadEventLoop = std::thread(&ProgramEventLoop::thread_queue_action_invoke, this);
    }
    /**
     * @brief 
     * 
     */
    void stop()
    {
        if (__lockEventLoop.try_lock())
        {
            __stop = 1;
            __lockEventLoop.unlock();
        }

        if ( __threadEventLoop.joinable())
        {
            __threadEventLoop.join();
            __runing = 0;
        }
    }

    /**
     * @brief Get the State object
     * 
     * @return std::string 
     */
    std::string GetState()
    {
        if (__runing == 1)
            return "RUNING";
        if (__stop == 1)
            return "STOPED";
        if (__stop == 0)
            return "STARTED";

        return "";
    }
};

#endif