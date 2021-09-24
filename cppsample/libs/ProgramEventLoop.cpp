
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
#include "ProgramEventLoop.h"

class ProgramEventLoop
{
    std::mutex __lockEventLoop;
    std::queue<std::function<void()>> __qVoid;
    int __stop=1;
    int __runing=0;

    int thread_queue_action_invoke()
    {
        std::function<void()> a = NULL;

        while (true)
        {
            if (__stop==1)
            {
                break;
            }

            if (__lockEventLoop.try_lock())
            {
                if (__qVoid.size() > 0)
                {
                    a = __qVoid.front();
                    __qVoid.pop();
                }
                __lockEventLoop.unlock();
            }
           
           // std::cout << "\r\n"<<__qVoid.size() <<"\r\n";

            if (a != NULL)
            {
                a();
                a = NULL;
            }

            std::this_thread::sleep_for(std::chrono::microseconds(1));
            //std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        if (__lockEventLoop.try_lock())
        {
            if (__runing)
            {
                __runing = 0;
            }
            __lockEventLoop.unlock();
        }

        return 0;
    }

    std::thread __thread;

public:
    ProgramEventLoop() : __thread()
    {
    }
    ~ProgramEventLoop()
    {
        stop();

        delete[] & __thread;
    }

    int queue_action(std::function<void()> a)
    {
        if (__lockEventLoop.try_lock())
        {
            __qVoid.push(a);
            __lockEventLoop.unlock();

        }

        return 0;
    }
    int start()
    {
      
        if (__lockEventLoop.try_lock())
        {
            if (__runing==1)
            {
                return 0;
            }

            __runing = 1;
            __lockEventLoop.unlock();
        }

        __stop = 0;

        __thread = std::thread(&ProgramEventLoop::thread_queue_action_invoke, this);

        return 0;
    }
    int stop()
    {
        if (__lockEventLoop.try_lock())
        {
            __stop = 1;
            __lockEventLoop.unlock();
        }

        if (__thread.joinable())
            __thread.join();

        return 0;
    }
};
