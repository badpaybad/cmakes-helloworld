
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

#include "ProgramContext.cpp"

#ifndef __class__ProgramEventLoop
#define __class__ProgramEventLoop

struct task_json
{
    std::string jsonData = NULL;
    std::function<void(std::string)> handle = NULL;
    
    task_json( std::string jsonDataToHandle=NULL, std::function<void(std::string)> actionHandle=NULL)
    : jsonData(jsonDataToHandle),handle(actionHandle){

    }

    bool operator==(task_json &input)
    {
        return jsonData == input.jsonData && &handle == &input.handle;
    }

    bool operator!=(task_json &input)
    {
        return jsonData != input.jsonData || &handle != &input.handle;
    }

} __taskNull{NULL, NULL};

/**
 * @brief 
 * class for queue action do in other thread, no block current
 */
class ProgramEventLoop
{
    //std::mutex &__lockGlobal;
    std::mutex __lockEventLoop;
    std::queue<task_json> __qVoid;
    int __stop = 1;
    int __runing = 0;
    std::thread __thread;

    void thread_queue_action_invoke()
    {
        while (true)
        {
            if (__stop == 1)
            {
                break;
            }

            task_json t = __taskNull;

            if (__lockEventLoop.try_lock())
            {
                if (__qVoid.size() > 0)
                {
                    t = __qVoid.front();
                    __qVoid.pop();
                }
                __lockEventLoop.unlock();
            }

            if (t != __taskNull)
            {
                // do fire and forget, if too much can overheat CPU, can do semarphore lock to keep concurrent thread runing
                //std::thread ta(a);

                //do block one by one
                t.handle(t.jsonData);

                delete &t;
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

public:
    ProgramEventLoop() : __thread()
    {
        ProgramContext::__version = "version 2";
    }

    ~ProgramEventLoop()
    {
        stop();

        delete[] & __thread;
    }
    /**
     * @brief 
     * queue_action , void func will run in other thread, no block current
     * @param a void function callable
     * @return int 
     */
    void queue_action(task_json task)
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

        __thread = std::thread(&ProgramEventLoop::thread_queue_action_invoke, this);
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

        if (__thread.joinable())
        {
            __thread.join();
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