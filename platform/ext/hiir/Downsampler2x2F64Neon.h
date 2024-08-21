/*****************************************************************************

        Downsampler2x2F64Neon.h
        Author: Laurent de Soras, 2024

Downsamples the input signal by a factor 2, using NEON instruction set.
Works on vectors of 2 double.

This object must be aligned on a 16-byte boundary!

Template parameters:
	- NC: number of coefficients, > 0

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law.You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://www.wtfpl.net/ for more details.

*Tab=3***********************************************************************/



#pragma once
#if ! defined (hiir_Downsampler2x2F64Neon_HEADER_INCLUDED)
#define hiir_Downsampler2x2F64Neon_HEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "hiir/def.h"
#include "hiir/StageDataF64Neon.h"

#include <arm_neon.h>

#include <array>



namespace hiir
{



template <int NC>
class Downsampler2x2F64Neon
{

	static_assert ((NC > 0), "Number of coefficient must be positive.");

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

	typedef double DataType;
	static constexpr int _nbr_chn  = 2;
	static constexpr int NBR_COEFS = NC;
	static constexpr double _delay = -1;

	               Downsampler2x2F64Neon () noexcept;
	               Downsampler2x2F64Neon (const Downsampler2x2F64Neon <NC> &other) = default;
	               Downsampler2x2F64Neon (Downsampler2x2F64Neon <NC> &&other) = default;
	               ~Downsampler2x2F64Neon ()                            = default;

	Downsampler2x2F64Neon <NC> &
	               operator = (const Downsampler2x2F64Neon <NC> &other) = delete;
	Downsampler2x2F64Neon <NC> &
	               operator = (Downsampler2x2F64Neon <NC> &&other)      = delete;

	void           set_coefs (const double coef_arr []) noexcept;

	hiir_FORCEINLINE float64x2_t
	               process_sample (const double in_ptr [_nbr_chn * 2]) noexcept;
	hiir_FORCEINLINE float64x2_t
	               process_sample (float64x2_t in_0, float64x2_t in_1) noexcept;
	void           process_block (double out_ptr [], const double in_ptr [], long nbr_spl) noexcept;

	hiir_FORCEINLINE void
	               process_sample_split (float64x2_t &low, float64x2_t &high, const double in_ptr [_nbr_chn * 2]) noexcept;
	hiir_FORCEINLINE void
	               process_sample_split (float64x2_t &low, float64x2_t &high, float64x2_t in_0, float64x2_t in_1) noexcept;
	void           process_block_split (double out_l_ptr [], double out_h_ptr [], const double in_ptr [], long nbr_spl) noexcept;

	void           clear_buffers () noexcept;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	// Stages 0 and 1 contain only input memories
	typedef std::array <StageDataF64Neon, NBR_COEFS + 2> Filter;

	// Should be the first member (thus easier to align)
	Filter         _filter;



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	bool           operator == (const Downsampler2x2F64Neon <NC> &other) const = delete;
	bool           operator != (const Downsampler2x2F64Neon <NC> &other) const = delete;

}; // class Downsampler2x2F64Neon



}  // namespace hiir



#include "hiir/Downsampler2x2F64Neon.hpp"



#endif // hiir_Downsampler2x2F64Neon_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
