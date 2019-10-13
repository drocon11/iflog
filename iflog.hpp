//
// iflog - C++ interface logging library. Easy to insert into if condition.
// vesion 0.0.3
// https://github.com/drocon11/iflog
// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// Copyright (c) 2019 Yukinori Yamazoe
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef IFLOG_HPP
#define IFLOG_HPP

// IFLOG      : alias for IFLOG_RETV.
// IFLOG_RETV : log for function returning copyable value.
// IFLOG_MOVE : log for function returning value that must be moved.
// IFLOG_VOID : log for function returning void type.

#ifndef IFLOG_DISABLE_LOG

#include <vector>       // std::vector
#include <tuple>        // std::tuple
#include <type_traits>  // std::enable_if
#include <utility>      // std::move, std::declval, std::get
#include <iostream>     // std::cout
#include <sstream>      // std::ostringstream
#include <ostream>      // std::ostream, std::endl
#include <iomanip>      // std::setw
#include <ios>          // std::left, std::boolalpha, std::showpoint, std::showbase
#include <cstring>      // std::strrchr
#include <cstddef>      // std::size_t
#include <mutex>        // std::mutex, std::lock_guard

//#define IFLOG_ENABLE_FEATURE_THREAD_SAFE  // std::mutex iflog::iflog::mtx;
//#define IFLOG_ENABLE_FEATURE_LOG_LEVEL    // int iflog::iflog::loglevel = 3;

// Logging level of IFLOG, IFLOG_RETV, IFLOG_MOVE, IFLOG_VOID.
#ifndef IFLOG_DEFAULT_LOG_LEVEL
    #define IFLOG_DEFAULT_LOG_LEVEL 3
#endif

#ifndef IFLOG_HEADER_TO_OSTREAM
    #ifdef IFLOG_ENABLE_FEATURE_LOG_LEVEL
        #define IFLOG_HEADER_TO_OSTREAM "LOG" << level << ":" << IFLOG_FILENAME(file) << ":" << func << "@" << line << " | " << std::boolalpha << std::showpoint << std::showbase
    #else
        #define IFLOG_HEADER_TO_OSTREAM "LOG:" << std::left << std::setw(32) << func << " | " << std::boolalpha << std::showpoint << std::showbase
//      #define IFLOG_HEADER_TO_OSTREAM "LOG:" << func << " | " << std::boolalpha << std::showpoint << std::showbase
    #endif
#endif

#ifndef IFLOG_FUNCMACRO
    #define IFLOG_FUNCMACRO __FUNCTION__
//  #define IFLOG_FUNCMACRO __func__
//  #define IFLOG_FUNCMACRO __PRETTY_FUNCTION__
//  #define IFLOG_FUNCMACRO __FUNCSIG__
#endif

#ifndef IFLOG_PARAM_SEPARATOR
    #define IFLOG_PARAM_SEPARATOR " , "
#endif

#ifndef IFLOG_VALUE_SEPARATOR
    #define IFLOG_VALUE_SEPARATOR " => "
#endif

#ifndef IFLOG_CUSTOM_OSTREAM
    #define IFLOG_CUSTOM_OSTREAM std::cout
#endif

#define IFLOG(...)  IFLOGL(IFLOG_DEFAULT_LOG_LEVEL,__VA_ARGS__)
#define IFLOG0(...) IFLOGL(0,__VA_ARGS__)
#define IFLOG1(...) IFLOGL(1,__VA_ARGS__)
#define IFLOG2(...) IFLOGL(2,__VA_ARGS__)
#define IFLOG3(...) IFLOGL(3,__VA_ARGS__)
#define IFLOG4(...) IFLOGL(4,__VA_ARGS__)
#define IFLOG5(...) IFLOGL(5,__VA_ARGS__)
#define IFLOG6(...) IFLOGL(6,__VA_ARGS__)
#define IFLOG7(...) IFLOGL(7,__VA_ARGS__)
#define IFLOG8(...) IFLOGL(8,__VA_ARGS__)
#define IFLOG9(...) IFLOGL(9,__VA_ARGS__)

#if defined(_MSC_VER)
    #define IFLOGL(lv,...) IFLOG_MSVC_EXPAND_VA_ARGS(IFLOG_GET_MACRONAME(__VA_ARGS__,IFLOG_10,IFLOG_09,IFLOG_08,IFLOG_07,IFLOG_06,IFLOG_05,IFLOG_04,IFLOG_03,IFLOG_02,IFLOG_01,IFLOG_00)(lv,__VA_ARGS__))
    #define IFLOG_DIRECTORY_SEPARATOR_CHAR '\\'
#else // defined(_MSC_VER)
    #define IFLOGL(lv,...) IFLOG_GET_MACRONAME(__VA_ARGS__,IFLOG_10,IFLOG_09,IFLOG_08,IFLOG_07,IFLOG_06,IFLOG_05,IFLOG_04,IFLOG_03,IFLOG_02,IFLOG_01,IFLOG_00)(lv,__VA_ARGS__)
    #define IFLOG_DIRECTORY_SEPARATOR_CHAR '/'
#endif // defined(_MSC_VER)

#define IFLOG_FILENAME(file) (std::strrchr(file, IFLOG_DIRECTORY_SEPARATOR_CHAR) ? std::strrchr(file, IFLOG_DIRECTORY_SEPARATOR_CHAR) + 1 : file)

#define IFLOG_MSVC_EXPAND_VA_ARGS(x) x
#define IFLOG_GET_MACRONAME(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,MACRONAME,...) MACRONAME

#define IFLOG_00(lv,expr                               ) iflog::iflogger<decltype(expr)                                                                                                                                   >::log(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#expr                                         },{[&]{if constexpr(std::is_void<decltype(expr)>::value){expr; return nullptr;}else{return expr;}}()                               })
#define IFLOG_01(lv,expr,a1                            ) iflog::iflogger<decltype(expr),decltype(a1)                                                                                                                      >::log(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#expr,#a1                                     },{[&]{if constexpr(std::is_void<decltype(expr)>::value){expr; return nullptr;}else{return expr;}}(),a1                            })
#define IFLOG_02(lv,expr,a1,a2                         ) iflog::iflogger<decltype(expr),decltype(a1),decltype(a2)                                                                                                         >::log(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#expr,#a1,#a2                                 },{[&]{if constexpr(std::is_void<decltype(expr)>::value){expr; return nullptr;}else{return expr;}}(),a1,a2                         })
#define IFLOG_03(lv,expr,a1,a2,a3                      ) iflog::iflogger<decltype(expr),decltype(a1),decltype(a2),decltype(a3)                                                                                            >::log(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#expr,#a1,#a2,#a3                             },{[&]{if constexpr(std::is_void<decltype(expr)>::value){expr; return nullptr;}else{return expr;}}(),a1,a2,a3                      })
#define IFLOG_04(lv,expr,a1,a2,a3,a4                   ) iflog::iflogger<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4)                                                                               >::log(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#expr,#a1,#a2,#a3,#a4                         },{[&]{if constexpr(std::is_void<decltype(expr)>::value){expr; return nullptr;}else{return expr;}}(),a1,a2,a3,a4                   })
#define IFLOG_05(lv,expr,a1,a2,a3,a4,a5                ) iflog::iflogger<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5)                                                                  >::log(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#expr,#a1,#a2,#a3,#a4,#a5                     },{[&]{if constexpr(std::is_void<decltype(expr)>::value){expr; return nullptr;}else{return expr;}}(),a1,a2,a3,a4,a5                })
#define IFLOG_06(lv,expr,a1,a2,a3,a4,a5,a6             ) iflog::iflogger<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6)                                                     >::log(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#expr,#a1,#a2,#a3,#a4,#a5,#a6                 },{[&]{if constexpr(std::is_void<decltype(expr)>::value){expr; return nullptr;}else{return expr;}}(),a1,a2,a3,a4,a5,a6             })
#define IFLOG_07(lv,expr,a1,a2,a3,a4,a5,a6,a7          ) iflog::iflogger<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7)                                        >::log(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#expr,#a1,#a2,#a3,#a4,#a5,#a6,#a7             },{[&]{if constexpr(std::is_void<decltype(expr)>::value){expr; return nullptr;}else{return expr;}}(),a1,a2,a3,a4,a5,a6,a7          })
#define IFLOG_08(lv,expr,a1,a2,a3,a4,a5,a6,a7,a8       ) iflog::iflogger<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8)                           >::log(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#expr,#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8         },{[&]{if constexpr(std::is_void<decltype(expr)>::value){expr; return nullptr;}else{return expr;}}(),a1,a2,a3,a4,a5,a6,a7,a8       })
#define IFLOG_09(lv,expr,a1,a2,a3,a4,a5,a6,a7,a8,a9    ) iflog::iflogger<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8),decltype(a9)              >::log(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#expr,#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8,#a9     },{[&]{if constexpr(std::is_void<decltype(expr)>::value){expr; return nullptr;}else{return expr;}}(),a1,a2,a3,a4,a5,a6,a7,a8,a9    })
#define IFLOG_10(lv,expr,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10) iflog::iflogger<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10)>::log(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#expr,#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8,#a9,#a10},{[&]{if constexpr(std::is_void<decltype(expr)>::value){expr; return nullptr;}else{return expr;}}(),a1,a2,a3,a4,a5,a6,a7,a8,a9,a10})

namespace iflog {

struct iflog
{
    static int loglevel;
    static std::mutex mtx;

protected:
    static void output_line(const std::string& s)
    {
#ifdef IFLOG_ENABLE_FEATURE_THREAD_SAFE
        std::lock_guard<std::mutex> lock(iflog::iflog::mtx);
#endif
        IFLOG_CUSTOM_OSTREAM << s << std::endl;
    }

    static void output_header(std::ostream& os, int level, const char* file, const char* func, int line)
    {
        os << IFLOG_HEADER_TO_OSTREAM;
    }

    template<typename Value>
    static auto output_param(std::ostream& os, const char* separator, const char* name, const Value& printable_value)
    -> decltype(std::declval<std::ostream&>() << std::declval<const Value&>(), void())
    {
        os << separator << name << IFLOG_VALUE_SEPARATOR << printable_value;
    }

    static auto output_param(std::ostream& os, const char* separator, const char* name, ...)
    -> void
    {
        os << separator << name;
    }

    template<std::size_t Index, typename... Values>
    static typename std::enable_if<Index >= sizeof...(Values), void>::type
    output_params(std::ostream& os, const std::vector<const char*>& names, const std::tuple<Values...>& values) {}

    template<std::size_t Index, typename... Values>
    static typename std::enable_if<Index < sizeof...(Values), void>::type
    output_params(std::ostream& os, const std::vector<const char*>& names, const std::tuple<Values...>& values)
    {
        output_param(os, IFLOG_PARAM_SEPARATOR, names[Index], std::get<Index>(values));
        output_params<Index+1, Values...>(os, names, values);
    }
};

template<typename Expr, typename... Values>
struct iflogger : iflog {
    static Expr log(int level, const char* file, const char* func, int line, std::vector<const char*> names, std::tuple<Expr, Values...> values)
    {
#ifdef IFLOG_ENABLE_FEATURE_LOG_LEVEL
        if (level > iflog::iflog::loglevel) { return std::get<0>(values); }
#endif
        std::ostringstream oss;
        output_header(oss, level, file, func, line);
        output_param(oss, "", names[0], std::get<0>(values));
        output_params<1, Expr, Values...>(oss, names, values);
        output_line(oss.str());
        return std::forward<Expr>(std::get<0>(values));
    }
};

// Partial specialization
template<typename... Values>
struct iflogger<void, Values...> : iflog {
    static void log(int level, const char* file, const char* func, int line, std::vector<const char*> names, std::tuple<std::nullptr_t, Values...> values)
    {
#ifdef IFLOG_ENABLE_FEATURE_LOG_LEVEL
        if (level > iflog::iflog::loglevel) { return; }
#endif
        std::ostringstream oss;
        output_header(oss, level, file, func, line);
        output_param(oss, "", names[0]);
        output_params<1, std::nullptr_t, Values...>(oss, names, values);
        output_line(oss.str());
    }
};

} // namespace iflog

#else // IFLOG_DISABLE_LOG

namespace iflog {
struct iflog
{
    static int loglevel;
    static std::mutex mtx;
};
}

#define IFLOG(expr,...)     expr
#define IFLOG0(expr,...)    expr
#define IFLOG1(expr,...)    expr
#define IFLOG2(expr,...)    expr
#define IFLOG3(expr,...)    expr
#define IFLOG4(expr,...)    expr
#define IFLOG5(expr,...)    expr
#define IFLOG6(expr,...)    expr
#define IFLOG7(expr,...)    expr
#define IFLOG8(expr,...)    expr
#define IFLOG9(expr,...)    expr
#define IFLOGL(lv,expr,...) expr

#endif // IFLOG_DISABLE_LOG

#endif // IFLOG_HPP
