/**
 * \file System.hpp
 * \author Damien Hilloulin (ziple)
 * \date 19/04/2014
 * \brief Find the targeted operating system (windows, linux, mac os etc... )
 */
#ifndef __LMSYSTEM_HPP__
#define __LMSYSTEM_HPP__

/**
 * \ingroup lm_module
 * @{
 */

/* OS detection */
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__)

    #define LM_OS_WIN
    
    /* we must make the distinction between the two versions as not the same thing at all */
    #if defined(WINCE) || defined(_WIN32_WCE)

        #define LM_OS_WINCE
        #define LM_OS LM_OS_WINCE

    #else

        #define LM_OS LM_OS_WIN

    #endif

#elif defined(linux) || defined(__linux)

    #define LM_OS_LINUX
    #define LM_OS LM_OS_LINUX

#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)

    #define LM_OS_MACOS
    #define LM_OS LM_OS_MACOS

#else

    #error Unsupported operating system, sorry...

#endif

#if defined(LM_OS_LINUX) || defined(LM_OS_MACOS) || !defined(LM_OS_WIN)

    # define LM_OS_UNIX

#endif

/**
 * @}
 */

#endif /* __LMSYSTEM_HPP__ */
