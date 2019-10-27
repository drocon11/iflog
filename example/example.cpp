
#define IFLOG_ENABLE_FEATURE_THREAD_SAFE
#define IFLOG_HEADER_TO_OSTREAM "LOG" << level << ":" << IFLOG_FILENAME(file) << ":" << func << " | " << std::boolalpha << std::showpoint << std::showbase
#include <sstream>
std::ostringstream g_oss;
#define IFLOG_CUSTOM_OSTREAM g_oss
//#define IFLOG_DISABLE_LOG
//#define IFLOG_ENABLE_FEATURE_LOG_LEVEL
//#define IFLOG_FUNCMACRO __FUNCSIG__
#include "iflog.hpp"
#include <iostream>
#include <string>
#include <memory>

//int iflog::iflog::loglevel = 3;
std::mutex iflog::iflog::mtx;

bool is_error()
{
    return true;
}

void void_func()
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
        AAA aaa = IFLOG_MOVE(AAA());
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

extern void test_iflog();

int main()
{
    const char* a = "v";
    bool iserror;
    IFLOG(a);
    IFLOG(a, a, a, a, a, a, a, a, a, a, a);
    IFLOG("abc");
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

    std::unique_ptr<hoge> p0(IFLOG(new hoge()));
#ifndef IFLOG_DISABLE_LOG
    std::unique_ptr<hoge> p1  = IFLOG_MOVE(p0);
    std::unique_ptr<hoge> p2  = IFLOG_MOVE(p1 , 1);
    std::unique_ptr<hoge> p3  = IFLOG_MOVE(p2 , 1, 2);
    std::unique_ptr<hoge> p4  = IFLOG_MOVE(p3 , 1, 2, 3);
    std::unique_ptr<hoge> p5  = IFLOG_MOVE(p4 , 1, 2, 3, 4);
    std::unique_ptr<hoge> p6  = IFLOG_MOVE(p5 , 1, 2, 3, 4, 5);
    std::unique_ptr<hoge> p7  = IFLOG_MOVE(p6 , 1, 2, 3, 4, 5, 6);
    std::unique_ptr<hoge> p8  = IFLOG_MOVE(p7 , 1, 2, 3, 4, 5, 6, 7);
    std::unique_ptr<hoge> p9  = IFLOG_MOVE(p8 , 1, 2, 3, 4, 5, 6, 7, 8);
    std::unique_ptr<hoge> p10 = IFLOG_MOVE(p9 , 1, 2, 3, 4, 5, 6, 7, 8, 9);
    std::unique_ptr<hoge> p   = IFLOG_MOVE(p10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
#endif

    IFLOG_VOID(void_func());
    IFLOG_VOID(void_func(), 1);
    IFLOG_VOID(void_func(), 1, 2);
    IFLOG_VOID(void_func(), 1, 2, 3);
    IFLOG_VOID(void_func(), 1, 2, 3, 4);
    IFLOG_VOID(void_func(), 1, 2, 3, 4, 5);
    IFLOG_VOID(void_func(), 1, 2, 3, 4, 5, 6);
    IFLOG_VOID(void_func(), 1, 2, 3, 4, 5, 6, 7);
    IFLOG_VOID(void_func(), 1, 2, 3, 4, 5, 6, 7, 8);
    IFLOG_VOID(void_func(), 1, 2, 3, 4, 5, 6, 7, 8, 9);
    IFLOG_VOID(void_func(), 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

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
    IFLOG_VOID(delete runner);

    std::cout << g_oss.str();
    g_oss.str("");

    test_iflog();
}
