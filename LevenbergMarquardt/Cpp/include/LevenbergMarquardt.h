#ifndef __LM_HPP__
#define __LM_HPP__

#include "Build.hpp"
#include "Types.hpp"

extern "C" {

	#define LM_SUCCESS 0
	#define LM_ARRAY_SIZES_DIFFERENT 1
	#define LM_UNKNOWN_ERROR 10

	/**
	 * \brief Finds a polynom of specified degree near the points
	 * \return Return an error code: see the error codes.
	 */
	lmu32 LM_API levenberg_marquardt(
		lmf64* yobs,
		lmu32 yobsLength,
		lmf64* xobs,
		lmu32 xobsLength,
		lmf64 e3,
		lmf64* polyptr,
		lmu32 numCoeffs,
		lmf64* e );

}

#endif /* __LM_HPP__ */