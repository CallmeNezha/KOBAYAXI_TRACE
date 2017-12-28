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

#include "kobayaxi/kobayaxi.h"

namespace KOBAYAXI
{
    /// Cross-platform config
#ifdef KOBAYAXI_PLATFORM_WIN
#   define KOBAYAXI_DEBUG_OUTPUT(_out)   OutputDebugStringA(_out);
#endif
#ifdef KOBAYAXI_PLATFORM_UNIX
#   define KOBAYAXI_DEBUG_OUTPUT(_out)   printf("%s", _out);
#endif


    void memCopy(void* _dst, const void* _src, size_t _numBytes)
    {
        ::memcpy(_dst, _src, _numBytes);
    }

#ifdef KOBAYAXI_PLATFORM_WIN
    int32_t vsnprintf(char* _out, int32_t _max, const char* _format, va_list _argList)
    {
        int32_t len = -1;
        if (NULL != _out)
        {
            va_list argListCopy;
            va_copy(argListCopy, _argList);
            len = ::vsnprintf_s(_out, _max, size_t(-1), _format, argListCopy);
            va_end(argListCopy);
        }
        return -1 == len ? ::_vscprintf(_format, _argList) : len;
    }
#endif

    int32_t snprintf(char* _out, int32_t _max, const char* _format, ...)
    {
        va_list argList;
        va_start(argList, _format);
        int32_t len = vsnprintf(_out, _max, _format, argList);
        va_end(argList);
        return len;
    }

    /// Only output information
    void debugPrintfVargs(const char* _format, va_list _argList)
    {
        char temp[8192];
        char* out = temp;
        int32_t len = vsnprintf(out, sizeof(temp), _format, _argList);
        if ((int32_t)sizeof(temp) < len)
        {
            out = (char*)alloca(len + 1);
            len = vsnprintf(out, len, _format, _argList);
        }
        out[len] = '\0';
        KOBAYAXI_DEBUG_OUTPUT(out);
    }

    /// Output information and __FILE__ __LINE__ information that can easily trace on.
    void traceVargs(const char* _filePath, uint16_t _line, const char* _format, va_list _argList)
    {
        char temp[2048];
        char* out = temp;
        va_list argListCopy;
        va_copy(argListCopy, _argList);
        int32_t len = snprintf(out, sizeof(temp), "%s (%d): ", _filePath, _line);
        int32_t total = len + vsnprintf(out + len, sizeof(temp) - len, _format, argListCopy);
        va_end(argListCopy);
        if ((int32_t)sizeof(temp) < total)
        {
            out = (char*)alloca(total + 1);
            memCopy(out, temp, len);
            vsnprintf(out + len, total - len, _format, _argList);
        }
        out[total] = '\0';
        KOBAYAXI_DEBUG_OUTPUT(out);
    }

    void trace(const char* _filePath, uint16_t _line, const char* _format, ...)
    {
        va_list argList;
        va_start(argList, _format);
        //debugPrintfVargs(_format, argList);
        traceVargs(_filePath, _line, _format, argList);
        va_end(argList);
    }


}
