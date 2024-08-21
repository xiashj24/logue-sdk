/*****************************************************************************

        HalfBand2F64Neon.h
        Author: Laurent de Soras, 2024

Half-band filter, low-pass or high-pass, using NEON instruction set.
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
#if ! defined (hiir_HalfBand2F64Neon_HEADER_INCLUDED)
#define hiir_HalfBand2F64Neon_HEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "hiir/def.h"
#include "hiir/StageDataF64Neon.h"

#include <arm_neon.h>

#include <array>



namespace hiir
{



template <int NC>
class HalfBand2F64Neon
{

	static_assert ((NC > 0), "Number of coefficient must be positive.");

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

	typedef double DataType;
	static constexpr int _nbr_chn  = 2;
	static constexpr int NBR_COEFS = NC;
	static constexpr double _delay = 0;

	               HalfBand2F64Neon () noexcept;
	               HalfBand2F64Neon (const HalfBand2F64Neon <NC> &other) = default;
	               HalfBand2F64Neon (HalfBand2F64Neon <NC> &&other)      = default;
	               ~HalfBand2F64Neon ()                                  = default;

	HalfBand2F64Neon <NC> &
	               operator = (const HalfBand2F64Neon <NC> &other) = default;
	HalfBand2F64Neon <NC> &
	               operator = (HalfBand2F64Neon <NC> &&other)      = default;

	void           set_coefs (const double coef_arr []) noexcept;

	hiir_FORCEINLINE float64x2_t
	               process_sample (float64x2_t input) noexcept;
	void           process_block (double out_ptr [], const double in_ptr [], long nbr_spl) noexcept;

	hiir_FORCEINLINE float64x2_t
	               process_sample_hpf (float64x2_t input) noexcept;
	void           process_block_hpf (double out_ptr [], const double in_ptr [], long nbr_spl) noexcept;

	hiir_FORCEINLINE void
	               process_sample_split (float64x2_t &low, float64x2_t &high, float64x2_t input) noexcept;
	void           process_block_split (double out_l_ptr [], double out_h_ptr [], const double in_ptr [], long nbr_spl) noexcept;

	void           clear_buffers () noexcept;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	static constexpr int _nbr_phases = 2;

	// Stages 0 and 1 contain only input memories
	typedef std::array <StageDataF64Neon, NBR_COEFS + 2> Filter;

	typedef	std::array <Filter, _nbr_phases>	FilterBiPhase;

	struct EvenOdd
	{
		alignas (16) float64x2_t _e;
		alignas (16) float64x2_t _o;
	};

	hiir_FORCEINLINE EvenOdd
	               process_2_paths (float64x2_t input) noexcept;
	template <typename FL, typename FH>
	hiir_FORCEINLINE void
	               process_block_2_paths (double out_l_ptr [], double out_h_ptr [], const double in_ptr [], long nbr_spl, FL fnc_l, FH fnc_h) noexcept;

	hiir_FORCEINLINE static void
	               store_low (double *ptr, float64x2_t tmp_0, float64x2_t tmp_1) noexcept;
	hiir_FORCEINLINE static void
	               store_high (double *ptr, float64x2_t tmp_0, float64x2_t tmp_1) noexcept;
	hiir_FORCEINLINE static void
	               bypass (double *, float64x2_t, float64x2_t) noexcept {}

	FilterBiPhase  _bifilter;
	alignas (16) double
	               _prev [_nbr_chn];
	int            _phase;			// 0 or 1



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	bool           operator == (const HalfBand2F64Neon <NC> &other) const = delete;
	bool           operator != (const HalfBand2F64Neon <NC> &other) const = delete;

}; // class HalfBand2F64Neon



}  // namespace hiir



#include "hiir/HalfBand2F64Neon.hpp"



#endif // hiir_HalfBand2F64Neon_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
