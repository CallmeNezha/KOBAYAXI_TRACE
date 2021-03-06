/*****************************************************************************************
 **
 **  @author    ZiJian Jiang
 **  @date      2017
 **  @brief     KOBAKAXI DEBUGGING
 **  @version   1.0
 **
 **   <!--#//         ______    _____            _________       _____   _____    -->
 **   <!--#//        /     /_  /    /            \__     /      /    /__/    /      -->
 **   <!--#//       /        \/    /    ___        /    /      /            /    ___ -->
 **   <!--#//      /     / \      /    /\__\      /    /___   /    ___     /    /   \ -->
 **   <!--#//    _/____ /   \___ /    _\___     _/_______ / _/___ / _/___ /    _\___/\_-->
 **
 **  @copyright Copyright (C) 2017. All rights reserved.
 **
 *****************************************************************************************/

#ifndef KOBAYAXI_H_HEADER_GUARD
#define KOBAYAXI_H_HEADER_GUARD


#define KOBAYAXI_CONFIG_DEBUG

#ifdef _WIN32
#include <windows.h>
#define KOBAYAXI_PLATFORM_WIN
#elif __APPLE__ || __linux__ || __unix__
#define KOBAYAXI_PLATFORM_UNIX
#include <algorithm>
#include <iostream>
#endif
#include "macros.h"

///
#define KOBAYAXI_COUNTOF(_x) sizeof(KOBAYAXI::COUNTOF_REQUIRES_ARRAY_ARGUMENT(_x) )

namespace KOBAYAXI
{
	void trace(const char* _filePath, uint16_t _line, const char* _format, ...);

    // http://cnicholson.net/2011/01/stupid-c-tricks-a-better-sizeof_array/
    template<typename T, size_t N>
    char(&COUNTOF_REQUIRES_ARRAY_ARGUMENT(const T(&)[N]))[N];
}

#endif
