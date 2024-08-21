/*****************************************************************************

        StageProcF64Neon.hpp
        Author: Laurent de Soras, 2024

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law.You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://www.wtfpl.net/ for more details.

*Tab=3***********************************************************************/



#pragma once
#if ! defined (hiir_StageProcF64Neon_CODEHEADER_INCLUDED)
#define hiir_StageProcF64Neon_CODEHEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace hiir
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



template <int CUR>
void	StageProcF64Neon <CUR>::process_sample_pos (float64x2_t &x, StageDataF64Neon *stage_arr) noexcept
{
	StageProcF64Neon <CUR>::process_sample_pos_rec (x, stage_arr);
	storea (stage_arr [CUR]._mem, x);
}



template <int CUR>
void	StageProcF64Neon <CUR>::process_sample_neg (float64x2_t &x, StageDataF64Neon *stage_arr) noexcept
{
	StageProcF64Neon <CUR>::process_sample_neg_rec (x, stage_arr);
	storea (stage_arr [CUR]._mem, x);
}



template <int CUR>
void	StageProcF64Neon <CUR>::process_sample_pos_rec (float64x2_t &x, StageDataF64Neon *stage_arr) noexcept
{
	StageProcF64Neon <CUR - 1>::process_sample_pos_rec (x, stage_arr);

	const auto     tmp = load2f64a (stage_arr [CUR - 1]._mem);
	storea (stage_arr [CUR - 1]._mem, x);

	x -= load2f64a (stage_arr [CUR]._mem );
	x *= load2f64a (stage_arr [CUR]._coef);
	x += tmp;
}

template <>
hiir_FORCEINLINE void	StageProcF64Neon <0>::process_sample_pos_rec (float64x2_t & /*x*/, StageDataF64Neon * /*stage_arr*/) noexcept
{
	// Nothing, stops the recursion
}



template <int CUR>
void	StageProcF64Neon <CUR>::process_sample_neg_rec (float64x2_t &x, StageDataF64Neon *stage_arr) noexcept
{
	StageProcF64Neon <CUR - 1>::process_sample_neg_rec (x, stage_arr);

	const auto     tmp = load2f64a (stage_arr [CUR - 1]._mem);
	storea (stage_arr [CUR - 1]._mem, x);

	x += load2f64a (stage_arr [CUR]._mem );
	x *= load2f64a (stage_arr [CUR]._coef);
	x -= tmp;
}

template <>
hiir_FORCEINLINE void	StageProcF64Neon <0>::process_sample_neg_rec (float64x2_t & /*x*/, StageDataF64Neon * /*stage_arr*/) noexcept
{
	// Nothing, stops the recursion
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace hiir



#endif // hiir_StageProcF64Neon_CODEHEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
