//
// iflog - C++ interface logging library. Easy to insert into if condition.
// vesion 0.0.1
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

#include <vector>       // std::vector
#include <tuple>        // std::tuple
#include <type_traits>  // std::enable_if
#include <utility>      // std::move, std::declval, std::get
#include <iostream>     // std::cout
#include <sstream>      // std::ostringstream
#include <ostream>      // std::ostream, std::endl
#include <iomanip>      // std::setw
#include <ios>          // std::left, std::boolalpha, std::showpoint, std::showbase
#include <cstddef>      // std::size_t
#include <cstring>      // std::strrchr

// IFLOG      : alias for IFLOG_RETV.
// IFLOG_RETV : log for function returning copyable value.
// IFLOG_MOVE : log for function returning value that must be moved.
// IFLOG_VOID : log for function returning void type.

#ifndef IFLOG_FUNCMACRO
    #define IFLOG_FUNCMACRO __FUNCTION__
//  #define IFLOG_FUNCMACRO __func__
//  #define IFLOG_FUNCMACRO __PRETTY_FUNCTION__
//  #define IFLOG_FUNCMACRO __FUNCSIG__
#endif

#ifndef IFLOG_ENABLE_FEATURE_LOG_LEVEL
    #define IFLOG_ENABLE_FEATURE_LOG_LEVEL 0
#endif

// Logging level of IFLOG, IFLOG_RETV, IFLOG_MOVE, IFLOG_VOID.
#ifndef IFLOG_DEFAULT_LOG_LEVEL
    #define IFLOG_DEFAULT_LOG_LEVEL 3
#endif

#ifndef IFLOG_HEADER_TO_OSTREAM
    #if IFLOG_ENABLE_FEATURE_LOG_LEVEL
        #define IFLOG_HEADER_TO_OSTREAM "LOG" << level << ":" << IFLOG_FILENAME(file) << ":" << func << "@" << line << " | " << std::boolalpha << std::showpoint << std::showbase
    #else
        #define IFLOG_HEADER_TO_OSTREAM "LOG:" << std::left << std::setw(32) << func << " | " << std::boolalpha << std::showpoint << std::showbase
//      #define IFLOG_HEADER_TO_OSTREAM "LOG:" << func << " | " << std::boolalpha << std::showpoint << std::showbase
    #endif
#endif

#ifndef IFLOG_PARAM_SEPARATOR
    #define IFLOG_PARAM_SEPARATOR " , "
#endif

#ifndef IFLOG_VALUE_SEPARATOR
    #define IFLOG_VALUE_SEPARATOR " => "
#endif

#if defined(_MSC_VER)
    #define IFLOG_DIRECTORY_SEPARATOR_CHAR '\\'
#else // defined(_MSC_VER)
    #define IFLOG_DIRECTORY_SEPARATOR_CHAR '/'
#endif // defined(_MSC_VER)

#define IFLOG_FILENAME(file) (std::strrchr(file, IFLOG_DIRECTORY_SEPARATOR_CHAR) ? std::strrchr(file, IFLOG_DIRECTORY_SEPARATOR_CHAR) + 1 : file)

#ifndef IFLOG_USE
    #define IFLOG_USE 1
#endif

#if IFLOG_USE
    #define IFLOG(...)          IFLOGx_RETV(IFLOG_DEFAULT_LOG_LEVEL,__VA_ARGS__)
    #define IFLOG_RETV(...)     IFLOGx_RETV(IFLOG_DEFAULT_LOG_LEVEL,__VA_ARGS__)
    #define IFLOG_MOVE(...)     IFLOGx_MOVE(IFLOG_DEFAULT_LOG_LEVEL,__VA_ARGS__)
    #define IFLOG_VOID(...)     IFLOGx_VOID(IFLOG_DEFAULT_LOG_LEVEL,__VA_ARGS__)
    #define IFLOG0(...)         IFLOGx_RETV(0,__VA_ARGS__)
    #define IFLOG1(...)         IFLOGx_RETV(1,__VA_ARGS__)
    #define IFLOG2(...)         IFLOGx_RETV(2,__VA_ARGS__)
    #define IFLOG3(...)         IFLOGx_RETV(3,__VA_ARGS__)
    #define IFLOG4(...)         IFLOGx_RETV(4,__VA_ARGS__)
    #define IFLOG5(...)         IFLOGx_RETV(5,__VA_ARGS__)
    #define IFLOG6(...)         IFLOGx_RETV(6,__VA_ARGS__)
    #define IFLOG7(...)         IFLOGx_RETV(7,__VA_ARGS__)
    #define IFLOG8(...)         IFLOGx_RETV(8,__VA_ARGS__)
    #define IFLOG9(...)         IFLOGx_RETV(9,__VA_ARGS__)
    #define IFLOG0_RETV(...)    IFLOGx_RETV(0,__VA_ARGS__)
    #define IFLOG1_RETV(...)    IFLOGx_RETV(1,__VA_ARGS__)
    #define IFLOG2_RETV(...)    IFLOGx_RETV(2,__VA_ARGS__)
    #define IFLOG3_RETV(...)    IFLOGx_RETV(3,__VA_ARGS__)
    #define IFLOG4_RETV(...)    IFLOGx_RETV(4,__VA_ARGS__)
    #define IFLOG5_RETV(...)    IFLOGx_RETV(5,__VA_ARGS__)
    #define IFLOG6_RETV(...)    IFLOGx_RETV(6,__VA_ARGS__)
    #define IFLOG7_RETV(...)    IFLOGx_RETV(7,__VA_ARGS__)
    #define IFLOG8_RETV(...)    IFLOGx_RETV(8,__VA_ARGS__)
    #define IFLOG9_RETV(...)    IFLOGx_RETV(9,__VA_ARGS__)
    #define IFLOG0_MOVE(...)    IFLOGx_MOVE(0,__VA_ARGS__)
    #define IFLOG1_MOVE(...)    IFLOGx_MOVE(1,__VA_ARGS__)
    #define IFLOG2_MOVE(...)    IFLOGx_MOVE(2,__VA_ARGS__)
    #define IFLOG3_MOVE(...)    IFLOGx_MOVE(3,__VA_ARGS__)
    #define IFLOG4_MOVE(...)    IFLOGx_MOVE(4,__VA_ARGS__)
    #define IFLOG5_MOVE(...)    IFLOGx_MOVE(5,__VA_ARGS__)
    #define IFLOG6_MOVE(...)    IFLOGx_MOVE(6,__VA_ARGS__)
    #define IFLOG7_MOVE(...)    IFLOGx_MOVE(7,__VA_ARGS__)
    #define IFLOG8_MOVE(...)    IFLOGx_MOVE(8,__VA_ARGS__)
    #define IFLOG9_MOVE(...)    IFLOGx_MOVE(9,__VA_ARGS__)
    #define IFLOG0_VOID(...)    IFLOGx_VOID(0,__VA_ARGS__)
    #define IFLOG1_VOID(...)    IFLOGx_VOID(1,__VA_ARGS__)
    #define IFLOG2_VOID(...)    IFLOGx_VOID(2,__VA_ARGS__)
    #define IFLOG3_VOID(...)    IFLOGx_VOID(3,__VA_ARGS__)
    #define IFLOG4_VOID(...)    IFLOGx_VOID(4,__VA_ARGS__)
    #define IFLOG5_VOID(...)    IFLOGx_VOID(5,__VA_ARGS__)
    #define IFLOG6_VOID(...)    IFLOGx_VOID(6,__VA_ARGS__)
    #define IFLOG7_VOID(...)    IFLOGx_VOID(7,__VA_ARGS__)
    #define IFLOG8_VOID(...)    IFLOGx_VOID(8,__VA_ARGS__)
    #define IFLOG9_VOID(...)    IFLOGx_VOID(9,__VA_ARGS__)
    #if defined(_MSC_VER)
        #define IFLOGx_RETV(lv,...) IFLOG_MSVC_EXPAND_VA_ARGS(IFLOG_GET_MACRONAME(__VA_ARGS__,IFLOG_RETV_10,IFLOG_RETV_09,IFLOG_RETV_08,IFLOG_RETV_07,IFLOG_RETV_06,IFLOG_RETV_05,IFLOG_RETV_04,IFLOG_RETV_03,IFLOG_RETV_02,IFLOG_RETV_01,IFLOG_RETV_00)(lv,__VA_ARGS__))
        #define IFLOGx_MOVE(lv,...) IFLOG_MSVC_EXPAND_VA_ARGS(IFLOG_GET_MACRONAME(__VA_ARGS__,IFLOG_MOVE_10,IFLOG_MOVE_09,IFLOG_MOVE_08,IFLOG_MOVE_07,IFLOG_MOVE_06,IFLOG_MOVE_05,IFLOG_MOVE_04,IFLOG_MOVE_03,IFLOG_MOVE_02,IFLOG_MOVE_01,IFLOG_MOVE_00)(lv,__VA_ARGS__))
        #define IFLOGx_VOID(lv,...) IFLOG_MSVC_EXPAND_VA_ARGS(IFLOG_GET_MACRONAME(__VA_ARGS__,IFLOG_VOID_10,IFLOG_VOID_09,IFLOG_VOID_08,IFLOG_VOID_07,IFLOG_VOID_06,IFLOG_VOID_05,IFLOG_VOID_04,IFLOG_VOID_03,IFLOG_VOID_02,IFLOG_VOID_01,IFLOG_VOID_00)(lv,__VA_ARGS__))
    #else // defined(_MSC_VER)
        #define IFLOGx_RETV(lv,...) IFLOG_GET_MACRONAME(__VA_ARGS__,IFLOG_RETV_10,IFLOG_RETV_09,IFLOG_RETV_08,IFLOG_RETV_07,IFLOG_RETV_06,IFLOG_RETV_05,IFLOG_RETV_04,IFLOG_RETV_03,IFLOG_RETV_02,IFLOG_RETV_01,IFLOG_RETV_00)(lv,__VA_ARGS__)
        #define IFLOGx_MOVE(lv,...) IFLOG_GET_MACRONAME(__VA_ARGS__,IFLOG_MOVE_10,IFLOG_MOVE_09,IFLOG_MOVE_08,IFLOG_MOVE_07,IFLOG_MOVE_06,IFLOG_MOVE_05,IFLOG_MOVE_04,IFLOG_MOVE_03,IFLOG_MOVE_02,IFLOG_MOVE_01,IFLOG_MOVE_00)(lv,__VA_ARGS__)
        #define IFLOGx_VOID(lv,...) IFLOG_GET_MACRONAME(__VA_ARGS__,IFLOG_VOID_10,IFLOG_VOID_09,IFLOG_VOID_08,IFLOG_VOID_07,IFLOG_VOID_06,IFLOG_VOID_05,IFLOG_VOID_04,IFLOG_VOID_03,IFLOG_VOID_02,IFLOG_VOID_01,IFLOG_VOID_00)(lv,__VA_ARGS__)
    #endif // defined(_MSC_VER)
#else // IFLOG_USE
    #define IFLOG(f,...)        f
    #define IFLOG_RETV(f,...)   f
    #define IFLOG_MOVE(f,...)   f
    #define IFLOG_VOID(f,...)   f
    #define IFLOG0(f,...)       f
    #define IFLOG1(f,...)       f
    #define IFLOG2(f,...)       f
    #define IFLOG3(f,...)       f
    #define IFLOG4(f,...)       f
    #define IFLOG5(f,...)       f
    #define IFLOG6(f,...)       f
    #define IFLOG7(f,...)       f
    #define IFLOG8(f,...)       f
    #define IFLOG9(f,...)       f
    #define IFLOG0_RETV(f,...)  f
    #define IFLOG1_RETV(f,...)  f
    #define IFLOG2_RETV(f,...)  f
    #define IFLOG3_RETV(f,...)  f
    #define IFLOG4_RETV(f,...)  f
    #define IFLOG5_RETV(f,...)  f
    #define IFLOG6_RETV(f,...)  f
    #define IFLOG7_RETV(f,...)  f
    #define IFLOG8_RETV(f,...)  f
    #define IFLOG9_RETV(f,...)  f
    #define IFLOG0_MOVE(f,...)  f
    #define IFLOG1_MOVE(f,...)  f
    #define IFLOG2_MOVE(f,...)  f
    #define IFLOG3_MOVE(f,...)  f
    #define IFLOG4_MOVE(f,...)  f
    #define IFLOG5_MOVE(f,...)  f
    #define IFLOG6_MOVE(f,...)  f
    #define IFLOG7_MOVE(f,...)  f
    #define IFLOG8_MOVE(f,...)  f
    #define IFLOG9_MOVE(f,...)  f
    #define IFLOG0_VOID(f,...)  f
    #define IFLOG1_VOID(f,...)  f
    #define IFLOG2_VOID(f,...)  f
    #define IFLOG3_VOID(f,...)  f
    #define IFLOG4_VOID(f,...)  f
    #define IFLOG5_VOID(f,...)  f
    #define IFLOG6_VOID(f,...)  f
    #define IFLOG7_VOID(f,...)  f
    #define IFLOG8_VOID(f,...)  f
    #define IFLOG9_VOID(f,...)  f
#endif // IFLOG_USE

#define IFLOG_MSVC_EXPAND_VA_ARGS(x) x
#define IFLOG_GET_MACRONAME(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,MACRONAME,...) MACRONAME

#define IFLOG_RETV_00(lv,f)                                iflog::log_return_value<decltype(f)                                                                                                                                   >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f                                         },{f                               })
#define IFLOG_RETV_01(lv,f,a1)                             iflog::log_return_value<decltype(f),decltype(a1)                                                                                                                      >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1                                     },{f,a1                            })
#define IFLOG_RETV_02(lv,f,a1,a2)                          iflog::log_return_value<decltype(f),decltype(a1),decltype(a2)                                                                                                         >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2                                 },{f,a1,a2                         })
#define IFLOG_RETV_03(lv,f,a1,a2,a3)                       iflog::log_return_value<decltype(f),decltype(a1),decltype(a2),decltype(a3)                                                                                            >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3                             },{f,a1,a2,a3                      })
#define IFLOG_RETV_04(lv,f,a1,a2,a3,a4)                    iflog::log_return_value<decltype(f),decltype(a1),decltype(a2),decltype(a3),decltype(a4)                                                                               >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4                         },{f,a1,a2,a3,a4                   })
#define IFLOG_RETV_05(lv,f,a1,a2,a3,a4,a5)                 iflog::log_return_value<decltype(f),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5)                                                                  >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5                     },{f,a1,a2,a3,a4,a5                })
#define IFLOG_RETV_06(lv,f,a1,a2,a3,a4,a5,a6)              iflog::log_return_value<decltype(f),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6)                                                     >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5,#a6                 },{f,a1,a2,a3,a4,a5,a6             })
#define IFLOG_RETV_07(lv,f,a1,a2,a3,a4,a5,a6,a7)           iflog::log_return_value<decltype(f),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7)                                        >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5,#a6,#a7             },{f,a1,a2,a3,a4,a5,a6,a7          })
#define IFLOG_RETV_08(lv,f,a1,a2,a3,a4,a5,a6,a7,a8)        iflog::log_return_value<decltype(f),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8)                           >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8         },{f,a1,a2,a3,a4,a5,a6,a7,a8       })
#define IFLOG_RETV_09(lv,f,a1,a2,a3,a4,a5,a6,a7,a8,a9)     iflog::log_return_value<decltype(f),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8),decltype(a9)              >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8,#a9     },{f,a1,a2,a3,a4,a5,a6,a7,a8,a9    })
#define IFLOG_RETV_10(lv,f,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10) iflog::log_return_value<decltype(f),decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10)>(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8,#a9,#a10},{f,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10})

#define IFLOG_MOVE_00(lv,f)                                iflog::log_return_move<decltype(f)&&                                                                                                                                   >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f                                         },{std::move(f)                               })
#define IFLOG_MOVE_01(lv,f,a1)                             iflog::log_return_move<decltype(f)&&,decltype(a1)                                                                                                                      >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1                                     },{std::move(f),a1                            })
#define IFLOG_MOVE_02(lv,f,a1,a2)                          iflog::log_return_move<decltype(f)&&,decltype(a1),decltype(a2)                                                                                                         >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2                                 },{std::move(f),a1,a2                         })
#define IFLOG_MOVE_03(lv,f,a1,a2,a3)                       iflog::log_return_move<decltype(f)&&,decltype(a1),decltype(a2),decltype(a3)                                                                                            >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3                             },{std::move(f),a1,a2,a3                      })
#define IFLOG_MOVE_04(lv,f,a1,a2,a3,a4)                    iflog::log_return_move<decltype(f)&&,decltype(a1),decltype(a2),decltype(a3),decltype(a4)                                                                               >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4                         },{std::move(f),a1,a2,a3,a4                   })
#define IFLOG_MOVE_05(lv,f,a1,a2,a3,a4,a5)                 iflog::log_return_move<decltype(f)&&,decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5)                                                                  >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5                     },{std::move(f),a1,a2,a3,a4,a5                })
#define IFLOG_MOVE_06(lv,f,a1,a2,a3,a4,a5,a6)              iflog::log_return_move<decltype(f)&&,decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6)                                                     >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5,#a6                 },{std::move(f),a1,a2,a3,a4,a5,a6             })
#define IFLOG_MOVE_07(lv,f,a1,a2,a3,a4,a5,a6,a7)           iflog::log_return_move<decltype(f)&&,decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7)                                        >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5,#a6,#a7             },{std::move(f),a1,a2,a3,a4,a5,a6,a7          })
#define IFLOG_MOVE_08(lv,f,a1,a2,a3,a4,a5,a6,a7,a8)        iflog::log_return_move<decltype(f)&&,decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8)                           >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8         },{std::move(f),a1,a2,a3,a4,a5,a6,a7,a8       })
#define IFLOG_MOVE_09(lv,f,a1,a2,a3,a4,a5,a6,a7,a8,a9)     iflog::log_return_move<decltype(f)&&,decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8),decltype(a9)              >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8,#a9     },{std::move(f),a1,a2,a3,a4,a5,a6,a7,a8,a9    })
#define IFLOG_MOVE_10(lv,f,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10) iflog::log_return_move<decltype(f)&&,decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10)>(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8,#a9,#a10},{std::move(f),a1,a2,a3,a4,a5,a6,a7,a8,a9,a10})

#define IFLOG_VOID_00(lv,f)                                iflog::log_non_return<nullptr_t                                                                                                                                   >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f                                         },{nullptr                               })
#define IFLOG_VOID_01(lv,f,a1)                             iflog::log_non_return<nullptr_t,decltype(a1)                                                                                                                      >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1                                     },{nullptr,a1                            })
#define IFLOG_VOID_02(lv,f,a1,a2)                          iflog::log_non_return<nullptr_t,decltype(a1),decltype(a2)                                                                                                         >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2                                 },{nullptr,a1,a2                         })
#define IFLOG_VOID_03(lv,f,a1,a2,a3)                       iflog::log_non_return<nullptr_t,decltype(a1),decltype(a2),decltype(a3)                                                                                            >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3                             },{nullptr,a1,a2,a3                      })
#define IFLOG_VOID_04(lv,f,a1,a2,a3,a4)                    iflog::log_non_return<nullptr_t,decltype(a1),decltype(a2),decltype(a3),decltype(a4)                                                                               >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4                         },{nullptr,a1,a2,a3,a4                   })
#define IFLOG_VOID_05(lv,f,a1,a2,a3,a4,a5)                 iflog::log_non_return<nullptr_t,decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5)                                                                  >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5                     },{nullptr,a1,a2,a3,a4,a5                })
#define IFLOG_VOID_06(lv,f,a1,a2,a3,a4,a5,a6)              iflog::log_non_return<nullptr_t,decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6)                                                     >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5,#a6                 },{nullptr,a1,a2,a3,a4,a5,a6             })
#define IFLOG_VOID_07(lv,f,a1,a2,a3,a4,a5,a6,a7)           iflog::log_non_return<nullptr_t,decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7)                                        >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5,#a6,#a7             },{nullptr,a1,a2,a3,a4,a5,a6,a7          })
#define IFLOG_VOID_08(lv,f,a1,a2,a3,a4,a5,a6,a7,a8)        iflog::log_non_return<nullptr_t,decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8)                           >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8         },{nullptr,a1,a2,a3,a4,a5,a6,a7,a8       })
#define IFLOG_VOID_09(lv,f,a1,a2,a3,a4,a5,a6,a7,a8,a9)     iflog::log_non_return<nullptr_t,decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8),decltype(a9)              >(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8,#a9     },{nullptr,a1,a2,a3,a4,a5,a6,a7,a8,a9    })
#define IFLOG_VOID_10(lv,f,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10) iflog::log_non_return<nullptr_t,decltype(a1),decltype(a2),decltype(a3),decltype(a4),decltype(a5),decltype(a6),decltype(a7),decltype(a8),decltype(a9),decltype(a10)>(lv,__FILE__,IFLOG_FUNCMACRO,__LINE__,{#f,#a1,#a2,#a3,#a4,#a5,#a6,#a7,#a8,#a9,#a10},{nullptr,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10})

namespace iflog {

struct iflog
{
    static int loglevel;
};

void output_header(std::ostream& os, int level, const char* file, const char* func, int line)
{
    os << IFLOG_HEADER_TO_OSTREAM;
}

template<typename Value>
auto output_param(std::ostream& os, const char* separator, const char* name, const Value& printable_value)
-> decltype(std::declval<std::ostream&>() << std::declval<const Value&>(), void())
{
    os << separator << name << IFLOG_VALUE_SEPARATOR << printable_value;
}

auto output_param(std::ostream& os, const char* separator, const char* name, ...)
-> void
{
    os << separator << name;
}

template<std::size_t Index, typename... Values>
inline typename std::enable_if<Index >= sizeof...(Values), void>::type
output_params(std::ostream& os, const std::vector<const char*>& names, const std::tuple<Values...>& values) {}

template<std::size_t Index, typename... Values>
inline typename std::enable_if<Index < sizeof...(Values), void>::type
output_params(std::ostream& os, const std::vector<const char*>& names, const std::tuple<Values...>& values)
{
    output_param(os, IFLOG_PARAM_SEPARATOR, names[Index], std::get<Index>(values));
    output_params<Index+1, Values...>(os, names, values);
}

template<typename... Values>
auto log_return_value(int level, const char* file, const char* func, int line, std::vector<const char*> names, std::tuple<Values...> values)
{
#if IFLOG_ENABLE_FEATURE_LOG_LEVEL
    if (level > iflog::iflog::loglevel)
    {
        return std::get<0>(values);
    }
#endif
    std::ostringstream oss;
    output_header(oss, level, file, func, line);
    output_param(oss, "", names[0], std::get<0>(values));
    output_params<1, Values...>(oss, names, values);
    std::cout << oss.str() << std::endl;
    return std::get<0>(values);
}

template<typename... Values>
auto log_return_move(int level, const char* file, const char* func, int line, std::vector<const char*> names, std::tuple<Values...> values)
{
#if IFLOG_ENABLE_FEATURE_LOG_LEVEL
    if (level > iflog::iflog::loglevel)
    {
        return std::move(std::get<0>(values));
    }
#endif
    std::ostringstream oss;
    output_header(oss, level, file, func, line);
    output_param(oss, "", names[0]);
    output_params<1, Values...>(oss, names, values);
    std::cout << oss.str() << std::endl;
    return std::move(std::get<0>(values));
}

template<typename... Values>
void log_non_return(int level, const char* file, const char* func, int line, std::vector<const char*> names, std::tuple<Values...> values)
{
#if IFLOG_ENABLE_FEATURE_LOG_LEVEL
    if (level > iflog::iflog::loglevel)
    {
        return;
    }
#endif
    std::ostringstream oss;
    output_header(oss, level, file, func, line);
    output_param(oss, "", names[0]);
    output_params<1, Values...>(oss, names, values);
    std::cout << oss.str() << std::endl;
}

} // namespace iflog

#endif // IFLOG_HPP
