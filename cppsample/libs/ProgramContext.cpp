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
#include "common.h"

#include <nlohmann/json.hpp>
//keyboard inject
#ifdef _WIN32

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#endif

#ifdef linux
#include <unistd.h>
#include <stdlib.h>

#include <curses.h>
//./vcpkg install ncurses
//sudo apt-get install libncurses5-dev libncursesw5-dev
//sudo yum install ncurses-devel ncurses
#endif

#ifndef NAMESPACE_PROGRAM_CONTEXT
#define NAMESPACE_PROGRAM_CONTEXT

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

    //need thread safe with lock for queue
    std::queue<int> __qKeyboardInput;
    std::stack<int> __stackTest;
    std::map<std::string, std::string> __mapTest;

    int thread_show_keyboardInput()
    {
        size_t qsize = 0;

        while (true)
        {
            if (ProgramContext::__stop == 1)
            {
                break;
            }
            char c = NULL;
            if (ProgramContext::__lockGlobal.try_lock())
            {
                qsize = __qKeyboardInput.size();
                if (qsize > 0)
                {
                    c = __qKeyboardInput.front();
                    __qKeyboardInput.pop();
                    qsize = qsize - 1;

                    //__stackTest.top();
                    //__stackTest.pop();
                }

                ProgramContext::__lockGlobal.unlock();
            }

            if (c != NULL)
            {
                std::cout << "\r\n char: " << (char)c << " ascii: " << (int)c << ": Pressed, " << qsize << ": remain in queue, press Enter key for menu\r\n";
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        return 0;
    };

    int infinity_loop_read_keyboard(std::function<void(std::string)> voidCallback)
    {

        auto baseDir = ProgramContext::__baseDir;

        __mapTest["baseDir"] = baseDir;
        //test use map
        //todo: may lack here cause thread may not safe, __mapTest assign key baseDir in thread thread_main_async, but queue_action will run in thread thrEventLoop(thread_queue_action_invoke)
        auto find = __mapTest.find("baseDir");

        if (find != __mapTest.end())
            std::cout << "\r\n__mapTest Found: " << find->first << ": " << find->second << "\r\n";

        while (true)
        {
            if (ProgramContext::__stop == 1)
            {
                break;
            }
            // prevent close main thread
            // to run services as single thread (main thread)
            // event loop services using queue to do message transfer

            if (_kbhit() != 0)
            {
                //read any key input from keyboard
                int input = _getch();
                if (ProgramContext::__lockGlobal.try_lock())
                {
                    ProgramContext::__qKeyboardInput.push(input);
                    ProgramContext::__stackTest.push(input);
                    ProgramContext::__lockGlobal.unlock();
                }
                //if(input==32) break; //space pressed
                if (input == 13)
                {
                    std::cout << "\r\nPress 'q' key to quit\r\n";
                    std::cout << "Press 'a' key to call _programEventLoop->queue_action\r\n";

                    int q = _getch();

                    if (q == (int)'q')
                    {
                        ProgramContext::exit();
                    }

                    if (q == (int)'a')
                    {
                        //about
                        time_t now = time(0);
                        char *dt = ctime(&now);

                        nlohmann::json data;
                        data["name"] = "nguyen phan du";
                        data["datenow"] = dt;
                        auto jsonData = data.dump();

                        voidCallback(jsonData);
                    }
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        return 0;
    }
    // void test()
    // {

    //     TaskJson t1{"t1", [](std::string i1) {

    //                 }};

    //     TaskJson t2(t1.jsonData, t1.handle);

    //     std::function<void(std::string)> h = [](std::string i2)
    //     {
    //         std::cout << "Same function: h, data: " << i2;
    //     };

    //     std::function<void(std::string)> *h4 = &h;

    //     TaskJson t3{"t3", h};

    //     TaskJson t4{"t4", *h4};

    //     auto t3_t4 = t3 == t4;

    //     std::cout << t3_t4;

    //     _programEventLoop->queue_action(t3);
    //     _programEventLoop->queue_action(t4);

    //     // std::cout << (__taskJsonNull == __taskJsonNull) << "  __taskJsonNull == __taskJsonNull \n";

    //     // TaskJson tj1{"du", [](std::string x)
    //     //              { std::cout << "tj1 handle inside---"; }};

    //     // TaskJson tj2{"du", [](std::string x)
    //     //              { std::cout << "tj2 handle inside---"; }};

    //     // TaskJson tj3 = tj1;
    //     // //{tj1.jsonData, tj1.handle};

    //     // std::cout << (tj1 == tj2) << "  tj1 == tj2 \n"
    //     //           << (tj3.jsonData) << "------\r\n";
    //     // std::cout << (tj1 == tj3) << "  tj1 == tj3 \n";

    //     // std::string myname = "Du";
    //     // std::cout << myname << " myname\n";

    //     // std::cout << &myname << " &myname\n";

    //     // std::string *addrof_myname = &myname;
    //     // std::cout << addrof_myname << " std::string *addrof_myname = &myname; \n";

    //     // std::cout << *addrof_myname << " *addrof_myname \n";
    //     // std::string addrof__myname = *&myname;
    //     // std::cout << addrof__myname << " addrof__myname = *&myname\n";

    //     // std::cout << &addrof__myname << " &addrof__myname \n";
    // };

}

#endif