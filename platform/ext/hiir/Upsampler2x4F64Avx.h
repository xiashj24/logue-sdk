/*****************************************************************************

        Upsampler2x4F64Avx.h
        Port of Upsampler2x4Sse.h from float to double by Dario Mambro
        Upsampler2x4Sse.h by Laurent de Soras, 2015

Upsamples the input signal by a factor 2, using the AVX instruction set.
Works on vectors of 4 double.

This object must be aligned on a 32-byte boundary!

Template parameters:
	- NC: number of coefficients, > 0

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://sam.zoy.org/wtfpl/COPYING for more details.

*Tab=3***********************************************************************/



#pragma once
#if ! defined (hiir_Upsampler2x4F64Avx_HEADER_INCLUDED)
#define hiir_Upsampler2x4F64Avx_HEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "hiir/def.h"
#include "hiir/StageDataF64Avx.h"

#include <immintrin.h> 

#include <array>



namespace hiir
{



template <int NC>
class Upsampler2x4F64Avx
{

	static_assert ((NC > 0), "Number of coefficient must be positive.");

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

	typedef double DataType;
	static constexpr int _nbr_chn  = 4;
	static constexpr int NBR_COEFS = NC;
	static constexpr double _delay = 0;

	               Upsampler2x4F64Avx () noexcept;
	               Upsampler2x4F64Avx (const Upsampler2x4F64Avx <NC> &other) = default;
	               Upsampler2x4F64Avx (Upsampler2x4F64Avx <NC> &&other)      = default;
	               ~Upsampler2x4F64Avx ()                            = default;

	Upsampler2x4F64Avx <NC> &
	               operator = (const Upsampler2x4F64Avx <NC> &other) = default;
	Upsampler2x4F64Avx <NC> &
	               operator = (Upsampler2x4F64Avx <NC> &&other)      = default;

	void				set_coefs (const double coef_arr [NBR_COEFS]) noexcept;
	hiir_FORCEINLINE void
	               process_sample (__m256d &out_0, __m256d &out_1, __m256d input) noexcept;
	void				process_block (double out_ptr [], const double in_ptr [], long nbr_spl) noexcept;
	void				clear_buffers () noexcept;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	// Stages 0 and 1 contain only input memories
	typedef std::array <StageDataF64Avx, NBR_COEFS + 2> Filter;

	// Should be the first member (thus easier to align)
	Filter         _filter;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	bool           operator == (const Upsampler2x4F64Avx <NC> &other) const = delete;
	bool           operator != (const Upsampler2x4F64Avx <NC> &other) const = delete;

}; // class Upsampler2x4F64Avx



}  // namespace hiir



#include "hiir/Upsampler2x4F64Avx.hpp"



#endif   // hiir_Upsampler2x4F64Avx_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
