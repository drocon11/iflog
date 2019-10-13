
//#define IFLOG_ENABLE_FEATURE_LOG_LEVEL
#define IFLOG_HEADER_TO_OSTREAM "LOG" << level << ":" << IFLOG_FILENAME(file) << ":" << func << " | " << std::boolalpha << std::showpoint << std::showbase
//#define IFLOG_HEADER_TO_OSTREAM "LOG" << level << ":" << IFLOG_FILENAME(file) << ":" << func << "@" << line << " | " << std::boolalpha << std::showpoint << std::showbase
#include <sstream>
std::ostringstream g_oss;
#define IFLOG_CUSTOM_OSTREAM g_oss
#define IFLOG_ENABLE_FEATURE_THREAD_SAFE
//#define IFLOG_DISABLE_LOG
//#define IFLOG_ENABLE_FEATURE_LOG_LEVEL
//#define IFLOG_FUNCMACRO __FUNCSIG__
#include "iflog.hpp"
#include <iostream>
#include <string>
#include <memory>
#include <cassert>

int iflog::iflog::loglevel = 3;

//int iflog::iflog::loglevel = 3;
//std::mutex iflog::iflog::mtx;

static bool is_error()
{
    return true;
}

static void void_func()
{
}

class AAA
{
public:
    bool send(){ return true; }
    bool done(){ return true; }
    bool has_error(){ return true; }
    int get_error(){ return -127; }
};

class Runner
{
public:
    int run()
    {
        AAA aaa = IFLOG(AAA());
        if (!IFLOG(aaa.send()))
        {
            return -1;
        }
        if (IFLOG(aaa.done()))
        {
            if (IFLOG(aaa.has_error()))
            {
                return IFLOG(aaa.get_error());
            }
            return 0;
        }
        return 1;
    }
};


struct hoge {};

void test_iflog()
{
    const char* a = "v";
    bool iserror;

    assert(a == IFLOG(a));
    assert(g_oss.str() == "LOG3:test_iflog.cpp:test_iflog | a => v\n");
    g_oss.str("");

    assert(a == IFLOG(a, a, a, a, a, a, a, a, a, a, a));
    assert(g_oss.str() == "LOG3:test_iflog.cpp:test_iflog | a => v , a => v , a => v , a => v , a => v , a => v , a => v , a => v , a => v , a => v , a => v\n");
    g_oss.str("");

    AAA aaa = IFLOG(AAA());
    assert(g_oss.str() == "LOG3:test_iflog.cpp:test_iflog | AAA()\n");
    g_oss.str("");

    std::cout << g_oss.str();
//  IFLOG("abc");
    iserror = IFLOG(is_error());
    iserror = IFLOG(is_error(), 1);
    iserror = IFLOG(is_error(), 1, 2);
    iserror = IFLOG(is_error(), 1, 2, 3);
    iserror = IFLOG(is_error(), 1, 2, 3, 4);
    iserror = IFLOG(is_error(), 1, 2, 3, 4, 5);
    iserror = IFLOG(is_error(), 1, 2, 3, 4, 5, 6);
    iserror = IFLOG(is_error(), 1, 2, 3, 4, 5, 6, 7);
    iserror = IFLOG(is_error(), 1, 2, 3, 4, 5, 6, 7, 8);
    iserror = IFLOG(is_error(), 1, 2, 3, 4, 5, 6, 7, 8, 9);
    iserror = IFLOG(is_error(), 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    int abc = 789;
    int def = IFLOG(static_cast<int&&>(abc));
    std::unique_ptr<hoge> p0(IFLOG(new hoge()));

    IFLOG(void_func());
    IFLOG(void_func(), 1);
    IFLOG(void_func(), 1, 2);
    IFLOG(void_func(), 1, 2, 3);
    IFLOG(void_func(), 1, 2, 3, 4);
    IFLOG(void_func(), 1, 2, 3, 4, 5);
    IFLOG(void_func(), 1, 2, 3, 4, 5, 6);
    IFLOG(void_func(), 1, 2, 3, 4, 5, 6, 7);
    IFLOG(void_func(), 1, 2, 3, 4, 5, 6, 7, 8);
    IFLOG(void_func(), 1, 2, 3, 4, 5, 6, 7, 8, 9);
    IFLOG(void_func(), 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    iserror = IFLOG2(is_error());
    iserror = IFLOG2(is_error(), 1);
    iserror = IFLOG2(is_error(), 1, 2);
    iserror = IFLOG2(is_error(), 1, 2, 3);
    iserror = IFLOG2(is_error(), 1, 2, 3, 4);
    iserror = IFLOG2(is_error(), 1, 2, 3, 4, 5);
    iserror = IFLOG2(is_error(), 1, 2, 3, 4, 5, 6);
    iserror = IFLOG2(is_error(), 1, 2, 3, 4, 5, 6, 7);
    iserror = IFLOG2(is_error(), 1, 2, 3, 4, 5, 6, 7, 8);
    iserror = IFLOG2(is_error(), 1, 2, 3, 4, 5, 6, 7, 8, 9);
    iserror = IFLOG2(is_error(), 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

    Runner* runner = IFLOG(new Runner());
    IFLOG(runner->run());
    IFLOG(delete runner);

//    std::cout << g_oss.str();
}
