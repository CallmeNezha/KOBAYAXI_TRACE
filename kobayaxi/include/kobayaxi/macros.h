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

#ifndef KOBAYAXI_MACROS_H_HEADER_GUARD
#define KOBAYAXI_MACROS_H_HEADER_GUARD

#define KOBAYAXI_CONFIG_DEBUG

/// Cross-platform config
#ifdef KOBAYAXI_PLATFORM_WIN

#define KOBAYAXI_NO_VTABLE __declspec(novtable)
#define KOBAYAXI_NO_INLINE __declspec(noinline)
#define KOBAYAXI_THREAD_LOCAL __declspec(thread)

#endif
#ifdef KOBAYAXI_PLATFORM_UNIX
#endif


/// Macro routine helper
#define KOBAYAXI_MACRO_BLOCK_BEGIN for(;;) {
#define KOBAYAXI_MACRO_BLOCK_END   break;  }
#define KOBAYAXI_NOOP(...) KOBAYAXI_MACRO_BLOCK_BEGIN KOBAYAXI_MACRO_BLOCK_END


/// Macro syntax helper
#define KOBAYAXI_UNLIKELY(_x)   (_x)
#define KOBAYAXI_LIKELY(_x)     (_x)

#ifdef KOBAYAXI_CONFIG_DEBUG
#	define KOBAYAXI_CHECK _KOBAYAXI_CHECK
#	define KOBAYAXI_TRACE _KOBAYAXI_TRACE
#else
#	define KOBAYAXI_CHECK KOBAYAXI_NOOP
#	define KOBAYAXI_TRACE KOBAYAXI_NOOP
#endif // _DEBUG


#define _KOBAYAXI_CHECK(_condition, _format, ...) \
				KOBAYAXI_MACRO_BLOCK_BEGIN \
                    if (!(_condition)) \
					{ \
                        KOBAYAXI_TRACE("[!!!] KOBAYAXI_CHECK " _format, ##__VA_ARGS__); \
					} \
				KOBAYAXI_MACRO_BLOCK_END


#define _KOBAYAXI_TRACE(_format, ...) \
				KOBAYAXI_MACRO_BLOCK_BEGIN \
					KOBAYAXI::trace(__FILE__, uint16_t(__LINE__), "KOBAYAXI " _format "\n", ##__VA_ARGS__); \
				KOBAYAXI_MACRO_BLOCK_END






#endif
