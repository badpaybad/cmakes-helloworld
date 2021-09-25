
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
/**
 * @brief 
 * class for queue action do in other thread, no block current
 */
class ProgramEventLoop
{
    std::mutex __lockEventLoop;
    std::queue<std::function<void()>> __qVoid;
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

            std::function<void()> a = NULL;

            if (__lockEventLoop.try_lock())
            {
                if (__qVoid.size() > 0)
                {
                    a = __qVoid.front();
                    __qVoid.pop();
                }
                __lockEventLoop.unlock();
            }

            if (a != NULL)
            {   
                // do fire and forget, if too much can overheat CPU, can do semarphore lock to keep concurrent thread runing
                //std::thread ta(a); 

                //do block one by one
                a();                
                a = NULL;
            }

            std::this_thread::sleep_for(std::chrono::nanoseconds(1));
            //std::this_thread::sleep_for(std::chrono::seconds(1));
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
    }

    ~ProgramEventLoop()
    {
        stop();

        delete[] & __thread;
    }
    /**
     * @brief 
     * queue_action
     * @param a void function callable
     * @return int 
     */
    void queue_action(std::function<void()> a)
    {
        if (__lockEventLoop.try_lock())
        {
            __qVoid.push(a);
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
