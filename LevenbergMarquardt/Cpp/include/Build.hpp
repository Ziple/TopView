/**
 * \file Build.hpp
 * \author Damien Hilloulin (ziple)
 * \date 19/04/2014
 * \brief File to tune compilation. Must be included by allmost all others headers.
 */
#ifndef __LMBUILD_HPP__
#define __LMBUILD_HPP__

#include "System.hpp"

/**
 * \ingroup lm_module
 * @{
 */

/* Portable macros for import/export */
#if defined(LM_OS_WIN) && defined(LM_DYNAMIC)

    #ifndef LM_BUILDING_LIBRARY

        #define LM_API __declspec(dllimport)

    #else

        #define LM_API __declspec(dllexport)

        // For Visual C++ compilers, we also need to turn off this annoying C4251 warning.
        // You can read lots ot different things about it, but the point is the code will
        // just work fine, and so the simplest way to get rid of this warning is to disable it
        #ifdef _MSC_VER

            #pragma warning(disable : 4251)

        #endif

    #endif

#else

    #define LM_API

#endif


/* debug mode compilation */
#if !defined(NDEBUG) || defined(_DEBUG)

    # define LM_DEBUG

#endif

/**
 * @}
 */

#endif /* __LMBUILD_HPP__ */
