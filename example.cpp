#define IFLOG_HEADER_TO_OSTREAM "LOG" << level << ":" << IFLOG_FILENAME(file) << ":" << func << " | " << std::boolalpha << std::showpoint << std::showbase
#define IFLOG_ENABLE_FEATURE_THREAD_SAFE
//#define IFLOG_DISABLE_LOG
//#define IFLOG_ENABLE_FEATURE_LOG_LEVEL
//#define IFLOG_FUNCMACRO __FUNCSIG__

#include <sstream>
extern std::ostringstream g_oss;
#define IFLOG_CUSTOM_OSTREAM g_oss

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

extern void test_iflog();

int main()
{
    const char* a = "v";
    bool iserror;
    IFLOG(a);
    IFLOG(a, a, a, a, a, a, a, a, a, a, a);
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

    std::cout << g_oss.str();
    g_oss.str("");

    test_iflog();
}
