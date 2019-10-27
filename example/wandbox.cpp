
#define IFLOG_ENABLE_FEATURE_THREAD_SAFE
#define IFLOG_HEADER_TO_OSTREAM "LOG" << level << ":" << IFLOG_FILENAME(file) << ":" << func << " | " << std::boolalpha << std::showpoint << std::showbase
#include <sstream>
std::ostringstream g_oss;
#define IFLOG_CUSTOM_OSTREAM g_oss

//
// iflog - C++ interface logging library. Easy to insert into if condition.
// vesion 0.0.4
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
#include <utility>      // std::move, std::declval
#include <iostream>     // std::cout
#include <sstream>      // std::ostringstream
#include <ostream>      // std::ostream, std::endl
#include <iomanip>      // std::setw
#include <ios>          // std::left, std::boolalpha, std::showpoint, std::showbase
#include <cstring>      // std::strrchr
#include <cstddef>      // std::nullptr_t
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

#ifndef IFLOG_FOOTER_TO_OSTREAM
    #define IFLOG_FOOTER_TO_OSTREAM std::endl
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

#define IFLOG(...)       IFLOGL_RETV(IFLOG_DEFAULT_LOG_LEVEL,__VA_ARGS__)
#define IFLOG_RETV(...)  IFLOGL_RETV(IFLOG_DEFAULT_LOG_LEVEL,__VA_ARGS__)
#define IFLOG_MOVE(...)  IFLOGL_MOVE(IFLOG_DEFAULT_LOG_LEVEL,__VA_ARGS__)
#define IFLOG_VOID(...)  IFLOGL_VOID(IFLOG_DEFAULT_LOG_LEVEL,__VA_ARGS__)
#define IFLOG0(...)      IFLOGL_RETV(0,__VA_ARGS__)
#define IFLOG1(...)      IFLOGL_RETV(1,__VA_ARGS__)
#define IFLOG2(...)      IFLOGL_RETV(2,__VA_ARGS__)
#define IFLOG3(...)      IFLOGL_RETV(3,__VA_ARGS__)
#define IFLOG4(...)      IFLOGL_RETV(4,__VA_ARGS__)
#define IFLOG5(...)      IFLOGL_RETV(5,__VA_ARGS__)
#define IFLOG6(...)      IFLOGL_RETV(6,__VA_ARGS__)
#define IFLOG7(...)      IFLOGL_RETV(7,__VA_ARGS__)
#define IFLOG8(...)      IFLOGL_RETV(8,__VA_ARGS__)
#define IFLOG9(...)      IFLOGL_RETV(9,__VA_ARGS__)
#define IFLOG0_RETV(...) IFLOGL_RETV(0,__VA_ARGS__)
#define IFLOG1_RETV(...) IFLOGL_RETV(1,__VA_ARGS__)
#define IFLOG2_RETV(...) IFLOGL_RETV(2,__VA_ARGS__)
#define IFLOG3_RETV(...) IFLOGL_RETV(3,__VA_ARGS__)
#define IFLOG4_RETV(...) IFLOGL_RETV(4,__VA_ARGS__)
#define IFLOG5_RETV(...) IFLOGL_RETV(5,__VA_ARGS__)
#define IFLOG6_RETV(...) IFLOGL_RETV(6,__VA_ARGS__)
#define IFLOG7_RETV(...) IFLOGL_RETV(7,__VA_ARGS__)
#define IFLOG8_RETV(...) IFLOGL_RETV(8,__VA_ARGS__)
#define IFLOG9_RETV(...) IFLOGL_RETV(9,__VA_ARGS__)
#define IFLOG0_MOVE(...) IFLOGL_MOVE(0,__VA_ARGS__)
#define IFLOG1_MOVE(...) IFLOGL_MOVE(1,__VA_ARGS__)
#define IFLOG2_MOVE(...) IFLOGL_MOVE(2,__VA_ARGS__)
#define IFLOG3_MOVE(...) IFLOGL_MOVE(3,__VA_ARGS__)
#define IFLOG4_MOVE(...) IFLOGL_MOVE(4,__VA_ARGS__)
#define IFLOG5_MOVE(...) IFLOGL_MOVE(5,__VA_ARGS__)
#define IFLOG6_MOVE(...) IFLOGL_MOVE(6,__VA_ARGS__)
#define IFLOG7_MOVE(...) IFLOGL_MOVE(7,__VA_ARGS__)
#define IFLOG8_MOVE(...) IFLOGL_MOVE(8,__VA_ARGS__)
#define IFLOG9_MOVE(...) IFLOGL_MOVE(9,__VA_ARGS__)
#define IFLOG0_VOID(...) IFLOGL_VOID(0,__VA_ARGS__)
#define IFLOG1_VOID(...) IFLOGL_VOID(1,__VA_ARGS__)
#define IFLOG2_VOID(...) IFLOGL_VOID(2,__VA_ARGS__)
#define IFLOG3_VOID(...) IFLOGL_VOID(3,__VA_ARGS__)
#define IFLOG4_VOID(...) IFLOGL_VOID(4,__VA_ARGS__)
#define IFLOG5_VOID(...) IFLOGL_VOID(5,__VA_ARGS__)
#define IFLOG6_VOID(...) IFLOGL_VOID(6,__VA_ARGS__)
#define IFLOG7_VOID(...) IFLOGL_VOID(7,__VA_ARGS__)
#define IFLOG8_VOID(...) IFLOGL_VOID(8,__VA_ARGS__)
#define IFLOG9_VOID(...) IFLOGL_VOID(9,__VA_ARGS__)

#if defined(_MSC_VER)
    #define IFLOGL_RETV(lv,...) IFLOG_MSVC_EXPAND_VA_ARGS(IFLOG_GET_MACRONAME(__VA_ARGS__,IFLOG_RETV_10,IFLOG_RETV_09,IFLOG_RETV_08,IFLOG_RETV_07,IFLOG_RETV_06,IFLOG_RETV_05,IFLOG_RETV_04,IFLOG_RETV_03,IFLOG_RETV_02,IFLOG_RETV_01,IFLOG_RETV_00)(lv,__VA_ARGS__))
    #define IFLOGL_MOVE(lv,...) IFLOG_MSVC_EXPAND_VA_ARGS(IFLOG_GET_MACRONAME(__VA_ARGS__,IFLOG_MOVE_10,IFLOG_MOVE_09,IFLOG_MOVE_08,IFLOG_MOVE_07,IFLOG_MOVE_06,IFLOG_MOVE_05,IFLOG_MOVE_04,IFLOG_MOVE_03,IFLOG_MOVE_02,IFLOG_MOVE_01,IFLOG_MOVE_00)(lv,__VA_ARGS__))
    #define IFLOGL_VOID(lv,...) IFLOG_MSVC_EXPAND_VA_ARGS(IFLOG_GET_MACRONAME(__VA_ARGS__,IFLOG_VOID_10,IFLOG_VOID_09,IFLOG_VOID_08,IFLOG_VOID_07,IFLOG_VOID_06,IFLOG_VOID_05,IFLOG_VOID_04,IFLOG_VOID_03,IFLOG_VOID_02,IFLOG_VOID_01,IFLOG_VOID_00)(lv,__VA_ARGS__))
    #define IFLOG_DIRECTORY_SEPARATOR_CHAR '\\'
#else // defined(_MSC_VER)
    #define IFLOGL_RETV(lv,...) IFLOG_GET_MACRONAME(__VA_ARGS__,IFLOG_RETV_10,IFLOG_RETV_09,IFLOG_RETV_08,IFLOG_RETV_07,IFLOG_RETV_06,IFLOG_RETV_05,IFLOG_RETV_04,IFLOG_RETV_03,IFLOG_RETV_02,IFLOG_RETV_01,IFLOG_RETV_00)(lv,__VA_ARGS__)
    #define IFLOGL_MOVE(lv,...) IFLOG_GET_MACRONAME(__VA_ARGS__,IFLOG_MOVE_10,IFLOG_MOVE_09,IFLOG_MOVE_08,IFLOG_MOVE_07,IFLOG_MOVE_06,IFLOG_MOVE_05,IFLOG_MOVE_04,IFLOG_MOVE_03,IFLOG_MOVE_02,IFLOG_MOVE_01,IFLOG_MOVE_00)(lv,__VA_ARGS__)
    #define IFLOGL_VOID(lv,...) IFLOG_GET_MACRONAME(__VA_ARGS__,IFLOG_VOID_10,IFLOG_VOID_09,IFLOG_VOID_08,IFLOG_VOID_07,IFLOG_VOID_06,IFLOG_VOID_05,IFLOG_VOID_04,IFLOG_VOID_03,IFLOG_VOID_02,IFLOG_VOID_01,IFLOG_VOID_00)(lv,__VA_ARGS__)
    #define IFLOG_DIRECTORY_SEPARATOR_CHAR '/'
#endif // defined(_MSC_VER)

#define IFLOG_FILENAME(file) (std::strrchr(file, IFLOG_DIRECTORY_SEPARATOR_CHAR) ? std::strrchr(file, IFLOG_DIRECTORY_SEPARATOR_CHAR) + 1 : file)

#define IFLOG_MSVC_EXPAND_VA_ARGS(x) x
#define IFLOG_GET_MACRONAME(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,MACRONAME,...) MACRONAME

#define IFLOG_RETV_00(lv,expr                               ) iflog::log_return_value<decltype(expr)                                                                                                                                   >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,expr,{                                        },                              }.get()
#define IFLOG_RETV_01(lv,expr,a1                            ) iflog::log_return_value<decltype(expr),decltype(a1)                                                                                                                      >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,expr,{#a1                                     },a1                            }.get()
#define IFLOG_RETV_02(lv,expr,a1,a2                         ) iflog::log_return_value<decltype(expr),decltype(a1),decltype(a2)                                                                                                         >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,expr,{#a1,#a2                                 },a1,a2                         }.get()
#define IFLOG_RETV_03(lv,expr,a1,a2,a3                      ) iflog::log_return_value<decltype(expr),decltype(a1),decltype(a2),decltype(a3)                                                                                            >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,expr,{#a1,#a2,#a3                             },a1,a2,a3                      }.get()
#define IFLOG_RETV_04(lv,expr,a1,a2,a3,a4                   ) iflog::log_return_value<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4)                                                                               >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,expr,{#a1,#a2,#a3,#a4                         },a1,a2,a3,a4                   }.get()
#define IFLOG_RETV_05(lv,expr,a1,a2,a3,a4,a5                ) iflog::log_return_value<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5)                                                                  >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,expr,{#a1,#a2,#a3,#a4,#a5                     },a1,a2,a3,a4,a5                }.get()
#define IFLOG_RETV_06(lv,expr,a1,a2,a3,a4,a5,a6             ) iflog::log_return_value<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6)                                                     >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,expr,{#a1,#a2,#a3,#a4,#a5,#a6                 },a1,a2,a3,a4,a5,a6             }.get()
#define IFLOG_RETV_07(lv,expr,a1,a2,a3,a4,a5,a6,a7          ) iflog::log_return_value<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7)                                        >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,expr,{#a1,#a2,#a3,#a4,#a5,#a6,#a7             },a1,a2,a3,a4,a5,a6,a7          }.get()
#define IFLOG_RETV_08(lv,expr,a1,a2,a3,a4,a5,a6,a7,a8       ) iflog::log_return_value<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8)                           >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,expr,{#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8         },a1,a2,a3,a4,a5,a6,a7,a8       }.get()
#define IFLOG_RETV_09(lv,expr,a1,a2,a3,a4,a5,a6,a7,a8,a9    ) iflog::log_return_value<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8),decltype(a9)              >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,expr,{#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8,#a9     },a1,a2,a3,a4,a5,a6,a7,a8,a9    }.get()
#define IFLOG_RETV_10(lv,expr,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10) iflog::log_return_value<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10)>{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,expr,{#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8,#a9,#a10},a1,a2,a3,a4,a5,a6,a7,a8,a9,a10}.get()

#define IFLOG_MOVE_00(lv,expr                               ) iflog::log_return_move<decltype(expr)                                                                                                                                   >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,std::move(expr),{                                        },                              }.get()
#define IFLOG_MOVE_01(lv,expr,a1                            ) iflog::log_return_move<decltype(expr),decltype(a1)                                                                                                                      >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,std::move(expr),{#a1                                     },a1                            }.get()
#define IFLOG_MOVE_02(lv,expr,a1,a2                         ) iflog::log_return_move<decltype(expr),decltype(a1),decltype(a2)                                                                                                         >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,std::move(expr),{#a1,#a2                                 },a1,a2                         }.get()
#define IFLOG_MOVE_03(lv,expr,a1,a2,a3                      ) iflog::log_return_move<decltype(expr),decltype(a1),decltype(a2),decltype(a3)                                                                                            >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,std::move(expr),{#a1,#a2,#a3                             },a1,a2,a3                      }.get()
#define IFLOG_MOVE_04(lv,expr,a1,a2,a3,a4                   ) iflog::log_return_move<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4)                                                                               >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,std::move(expr),{#a1,#a2,#a3,#a4                         },a1,a2,a3,a4                   }.get()
#define IFLOG_MOVE_05(lv,expr,a1,a2,a3,a4,a5                ) iflog::log_return_move<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5)                                                                  >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,std::move(expr),{#a1,#a2,#a3,#a4,#a5                     },a1,a2,a3,a4,a5                }.get()
#define IFLOG_MOVE_06(lv,expr,a1,a2,a3,a4,a5,a6             ) iflog::log_return_move<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6)                                                     >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,std::move(expr),{#a1,#a2,#a3,#a4,#a5,#a6                 },a1,a2,a3,a4,a5,a6             }.get()
#define IFLOG_MOVE_07(lv,expr,a1,a2,a3,a4,a5,a6,a7          ) iflog::log_return_move<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7)                                        >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,std::move(expr),{#a1,#a2,#a3,#a4,#a5,#a6,#a7             },a1,a2,a3,a4,a5,a6,a7          }.get()
#define IFLOG_MOVE_08(lv,expr,a1,a2,a3,a4,a5,a6,a7,a8       ) iflog::log_return_move<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8)                           >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,std::move(expr),{#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8         },a1,a2,a3,a4,a5,a6,a7,a8       }.get()
#define IFLOG_MOVE_09(lv,expr,a1,a2,a3,a4,a5,a6,a7,a8,a9    ) iflog::log_return_move<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8),decltype(a9)              >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,std::move(expr),{#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8,#a9     },a1,a2,a3,a4,a5,a6,a7,a8,a9    }.get()
#define IFLOG_MOVE_10(lv,expr,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10) iflog::log_return_move<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10)>{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,std::move(expr),{#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8,#a9,#a10},a1,a2,a3,a4,a5,a6,a7,a8,a9,a10}.get()

#define IFLOG_VOID_00(lv,expr                               ) iflog::log_non_return<decltype(expr)                                                                                                                                   >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,(expr,nullptr),{                                        },                              }.get()
#define IFLOG_VOID_01(lv,expr,a1                            ) iflog::log_non_return<decltype(expr),decltype(a1)                                                                                                                      >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,(expr,nullptr),{#a1                                     },a1                            }.get()
#define IFLOG_VOID_02(lv,expr,a1,a2                         ) iflog::log_non_return<decltype(expr),decltype(a1),decltype(a2)                                                                                                         >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,(expr,nullptr),{#a1,#a2                                 },a1,a2                         }.get()
#define IFLOG_VOID_03(lv,expr,a1,a2,a3                      ) iflog::log_non_return<decltype(expr),decltype(a1),decltype(a2),decltype(a3)                                                                                            >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,(expr,nullptr),{#a1,#a2,#a3                             },a1,a2,a3                      }.get()
#define IFLOG_VOID_04(lv,expr,a1,a2,a3,a4                   ) iflog::log_non_return<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4)                                                                               >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,(expr,nullptr),{#a1,#a2,#a3,#a4                         },a1,a2,a3,a4                   }.get()
#define IFLOG_VOID_05(lv,expr,a1,a2,a3,a4,a5                ) iflog::log_non_return<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5)                                                                  >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,(expr,nullptr),{#a1,#a2,#a3,#a4,#a5                     },a1,a2,a3,a4,a5                }.get()
#define IFLOG_VOID_06(lv,expr,a1,a2,a3,a4,a5,a6             ) iflog::log_non_return<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6)                                                     >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,(expr,nullptr),{#a1,#a2,#a3,#a4,#a5,#a6                 },a1,a2,a3,a4,a5,a6             }.get()
#define IFLOG_VOID_07(lv,expr,a1,a2,a3,a4,a5,a6,a7          ) iflog::log_non_return<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7)                                        >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,(expr,nullptr),{#a1,#a2,#a3,#a4,#a5,#a6,#a7             },a1,a2,a3,a4,a5,a6,a7          }.get()
#define IFLOG_VOID_08(lv,expr,a1,a2,a3,a4,a5,a6,a7,a8       ) iflog::log_non_return<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8)                           >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,(expr,nullptr),{#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8         },a1,a2,a3,a4,a5,a6,a7,a8       }.get()
#define IFLOG_VOID_09(lv,expr,a1,a2,a3,a4,a5,a6,a7,a8,a9    ) iflog::log_non_return<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8),decltype(a9)              >{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,(expr,nullptr),{#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8,#a9     },a1,a2,a3,a4,a5,a6,a7,a8,a9    }.get()
#define IFLOG_VOID_10(lv,expr,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10) iflog::log_non_return<decltype(expr),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10)>{lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,#expr,(expr,nullptr),{#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8,#a9,#a10},a1,a2,a3,a4,a5,a6,a7,a8,a9,a10}.get()

namespace iflog {

class iflog
{
public:
    static int loglevel;
    static std::mutex mtx;

protected:
    void output_to_ostream()
    {
#ifdef IFLOG_ENABLE_FEATURE_THREAD_SAFE
        std::lock_guard<std::mutex> lock(iflog::iflog::mtx);
#endif
        IFLOG_CUSTOM_OSTREAM << oss_.str();
    }

    void output_header(int level, const char* file, const char* func, int line)
    {
        oss_ << IFLOG_HEADER_TO_OSTREAM;
    }

    void output_footer()
    {
        oss_ << IFLOG_FOOTER_TO_OSTREAM;
    }

    template<typename Value>
    auto output_param(const char* separator, const char* name, const Value& printable_value)
    -> decltype(std::declval<std::ostream&>() << std::declval<const Value&>(), void())
    {
        oss_ << separator << name << IFLOG_VALUE_SEPARATOR << printable_value;
    }

    auto output_param(const char* separator, const char* name, ...)
    -> void
    {
        oss_ << separator << name;
    }

    void output_params(int index, const std::vector<const char*>& argsstr) {}

    template <class Head, class... Tail>
    void output_params(int index, const std::vector<const char*>& argsstr, Head&& headval, Tail&&... tailval)
    {
        output_param(IFLOG_PARAM_SEPARATOR, argsstr[index], headval);
        output_params(index + 1, argsstr, std::forward<Tail>(tailval)...);
    }

    std::ostringstream oss_;
};

template<typename Expr, typename... Args>
class log_return_value : iflog
{
public:
    log_return_value(int level, const char* file, const char* func, int line, const char* exprstr, const Expr&/*&&*/ exprval, const std::vector<const char*>& argsstr, Args...argsval) : retval_(exprval)
    {
#ifdef IFLOG_ENABLE_FEATURE_LOG_LEVEL
        if (level > iflog::iflog::loglevel) { return; }
#endif
        output_header(level, file, func, line);
        output_param("", exprstr, exprval);
        output_params(0, argsstr, argsval...);
        output_footer();
        output_to_ostream();
    }

    const Expr& get() const
    {
        return retval_;
    }

private:
    const Expr &retval_;
};

template<typename Expr, typename... Args>
class log_return_move : iflog
{
public:
    log_return_move(int level, const char* file, const char* func, int line, const char* exprstr, Expr&& exprval, const std::vector<const char*>& argsstr, Args...argsval) : retval_(std::move(exprval))
    {
#ifdef IFLOG_ENABLE_FEATURE_LOG_LEVEL
        if (level > iflog::iflog::loglevel) { return; }
#endif
        output_header(level, file, func, line);
        output_param("", exprstr);
        output_params(0, argsstr, argsval...);
        output_footer();
        output_to_ostream();
    }

    Expr get()
    {
        return std::move(retval_);
    }

private:
    Expr&& retval_;
};

template<typename Expr, typename... Args>
class log_non_return : iflog
{
public:
    log_non_return(int level, const char* file, const char* func, int line, const char* exprstr, std::nullptr_t dummyval, const std::vector<const char*>& argsstr, Args...argsval)
    {
#ifdef IFLOG_ENABLE_FEATURE_LOG_LEVEL
        if (level > iflog::iflog::loglevel) { return; }
#endif
        output_header(level, file, func, line);
        output_param("", exprstr);
        output_params(0, argsstr, argsval...);
        output_footer();
        output_to_ostream();
    }

    Expr get()
    {
        return;
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

#define IFLOG(expr,...)          expr
#define IFLOG_RETV(expr,...)     expr
#define IFLOG_MOVE(expr,...)     expr
#define IFLOG_VOID(expr,...)     expr
#define IFLOG0(expr,...)         expr
#define IFLOG1(expr,...)         expr
#define IFLOG2(expr,...)         expr
#define IFLOG3(expr,...)         expr
#define IFLOG4(expr,...)         expr
#define IFLOG5(expr,...)         expr
#define IFLOG6(expr,...)         expr
#define IFLOG7(expr,...)         expr
#define IFLOG8(expr,...)         expr
#define IFLOG9(expr,...)         expr
#define IFLOG0_RETV(expr,...)    expr
#define IFLOG1_RETV(expr,...)    expr
#define IFLOG2_RETV(expr,...)    expr
#define IFLOG3_RETV(expr,...)    expr
#define IFLOG4_RETV(expr,...)    expr
#define IFLOG5_RETV(expr,...)    expr
#define IFLOG6_RETV(expr,...)    expr
#define IFLOG7_RETV(expr,...)    expr
#define IFLOG8_RETV(expr,...)    expr
#define IFLOG9_RETV(expr,...)    expr
#define IFLOG0_MOVE(expr,...)    expr
#define IFLOG1_MOVE(expr,...)    expr
#define IFLOG2_MOVE(expr,...)    expr
#define IFLOG3_MOVE(expr,...)    expr
#define IFLOG4_MOVE(expr,...)    expr
#define IFLOG5_MOVE(expr,...)    expr
#define IFLOG6_MOVE(expr,...)    expr
#define IFLOG7_MOVE(expr,...)    expr
#define IFLOG8_MOVE(expr,...)    expr
#define IFLOG9_MOVE(expr,...)    expr
#define IFLOG0_VOID(expr,...)    expr
#define IFLOG1_VOID(expr,...)    expr
#define IFLOG2_VOID(expr,...)    expr
#define IFLOG3_VOID(expr,...)    expr
#define IFLOG4_VOID(expr,...)    expr
#define IFLOG5_VOID(expr,...)    expr
#define IFLOG6_VOID(expr,...)    expr
#define IFLOG7_VOID(expr,...)    expr
#define IFLOG8_VOID(expr,...)    expr
#define IFLOG9_VOID(expr,...)    expr
#define IFLOGL_RETV(lv,expr,...) expr
#define IFLOGL_MOVE(lv,expr,...) expr
#define IFLOGL_VOID(lv,expr,...) expr

#endif // IFLOG_DISABLE_LOG

#endif // IFLOG_HPP

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

//    test_iflog();
}
