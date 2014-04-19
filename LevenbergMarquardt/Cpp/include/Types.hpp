/**
 * \file Types.hpp
 * \author Damien Hilloulin (ziple)
 * \date 19/04/2014
 * \brief Essential file where the types used by the library are defined.
 */
#ifndef __LMTYPES_HPP__
#define __LMTYPES_HPP__

#include "Build.hpp"
#include <limits.h>

#if UCHAR_MAX ==  0xFF
    typedef char                lmi8;
    typedef unsigned char        lmu8;
#else
    #error No 8 bits types on this platform!
#endif

#if USHRT_MAX == 0xFFFF
    typedef short                lmi16;
    typedef unsigned short        lmu16;
#elif UINT_MAX == 0xFFFF
    typedef int                    lmi16;
    typedef unsigned int        lmu16;
#elif ULONG_MAX == 0xFFFF
    typedef long                lmi16;
    typedef unsigned long        lmu16;
#else
    #error No 16 bits types on this platform!
#endif

#if USHRT_MAX == 0xFFFFFFFF
    typedef short                lmi32;
    typedef unsigned short        lmu32;
#elif UINT_MAX == 0xFFFFFFFF
    typedef int                    lmi32;
    typedef unsigned int        lmu32;
#elif ULONG_MAX == 0xFFFFFFFF
    typedef long                lmi32;
    typedef unsigned long        lmu32;
#else
    #error No 32 bits types on this platform!
#endif

#if UINT_MAX == 0xFFFFFFFFFFFFFFFF
    typedef int                 lmi64;
    typedef unsigned int        lmu64;
#elif ULONG_MAX == 0xFFFFFFFFFFFFFFFF
    typedef long                lmi64;
    typedef unsigned long        lmu64;
#elif ULLONG_MAX == 0xFFFFFFFFFFFFFFFF
    typedef long long            lmi64;
    typedef unsigned long long  lmu64;
#else
    #warning No 64 bits integers on this platform!
    #define KT_NO_64BITS_INTEGERS
#endif

    typedef float                lmf32;
    typedef double                lmf64;

#endif /* __LMTYPES_HPP__ */
