/*****************************************************************************

        StageProc2F64Neon.hpp
        Author: Laurent de Soras, 2024

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law.You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://www.wtfpl.net/ for more details.

*Tab=3***********************************************************************/



#pragma once
#if ! defined (hiir_StageProc2F64Neon_CODEHEADER_INCLUDED)
#define hiir_StageProc2F64Neon_CODEHEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "hiir/StageDataF64Neon.h"



namespace hiir
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



template <>
void	StageProc2F64Neon <1>::process_sample_pos (const int nbr_coefs, float64x2_t &spl_0, float64x2_t &spl_1, StageDataF64Neon *stage_arr) noexcept
{
	const int      cnt = nbr_coefs + 2 - 1;

	const auto     tmp_0 = vmlaq_f64 (
		        load2f64a (stage_arr [cnt - 2]._mem ),
		spl_0 - load2f64a (stage_arr [cnt    ]._mem ),
		        load2f64a (stage_arr [cnt    ]._coef)
	);

	storea (stage_arr [cnt - 2]._mem, spl_0);
	storea (stage_arr [cnt - 1]._mem, spl_1);
	storea (stage_arr [cnt    ]._mem, tmp_0);

	spl_0 = tmp_0;
}



template <>
void	StageProc2F64Neon <0>::process_sample_pos (const int nbr_coefs, float64x2_t &spl_0, float64x2_t &spl_1, StageDataF64Neon *stage_arr) noexcept
{
	const int      cnt = nbr_coefs + 2;

	storea (stage_arr [cnt - 2]._mem, spl_0);
	storea (stage_arr [cnt - 1]._mem, spl_1);
}



template <int REMAINING>
void	StageProc2F64Neon <REMAINING>::process_sample_pos (const int nbr_coefs, float64x2_t &spl_0, float64x2_t &spl_1, StageDataF64Neon *stage_arr) noexcept
{
	const int      cnt = nbr_coefs + 2 - REMAINING;

	const auto     tmp_0 = vmlaq_f64 (
		        load2f64a (stage_arr [cnt - 2]._mem ),
		spl_0 - load2f64a (stage_arr [cnt    ]._mem ),
		        load2f64a (stage_arr [cnt    ]._coef)
	);
	const auto     tmp_1 = vmlaq_f64 (
		        load2f64a (stage_arr [cnt - 1]._mem ),
		spl_1 - load2f64a (stage_arr [cnt + 1]._mem ),
		        load2f64a (stage_arr [cnt + 1]._coef)
	);

	storea (stage_arr [cnt - 2]._mem, spl_0);
	storea (stage_arr [cnt - 1]._mem, spl_1);

	spl_0 = tmp_0;
	spl_1 = tmp_1;

	StageProc2F64Neon <REMAINING - 2>::process_sample_pos (
		nbr_coefs,
		spl_0,
		spl_1,
		stage_arr
	);
}



template <>
void	StageProc2F64Neon <1>::process_sample_neg (const int nbr_coefs, float64x2_t &spl_0, float64x2_t &spl_1, StageDataF64Neon *stage_arr) noexcept
{
	const int      cnt = nbr_coefs + 2 - 1;

	auto           tmp_0 = spl_0;
	tmp_0 += load2f64a (stage_arr [cnt    ]._mem );
	tmp_0 *= load2f64a (stage_arr [cnt    ]._coef);
	tmp_0 -= load2f64a (stage_arr [cnt - 2]._mem );

	storea (stage_arr [cnt - 2]._mem, spl_0);
	storea (stage_arr [cnt - 1]._mem, spl_1);
	storea (stage_arr [cnt    ]._mem, tmp_0);

	spl_0 = tmp_0;
}



template <>
void	StageProc2F64Neon <0>::process_sample_neg (const int nbr_coefs, float64x2_t &spl_0, float64x2_t &spl_1, StageDataF64Neon *stage_arr) noexcept
{
	const int      cnt = nbr_coefs + 2;

	storea (stage_arr [cnt - 2]._mem, spl_0);
	storea (stage_arr [cnt - 1]._mem, spl_1);
}



template <int REMAINING>
void	StageProc2F64Neon <REMAINING>::process_sample_neg (const int nbr_coefs, float64x2_t &spl_0, float64x2_t &spl_1, StageDataF64Neon *stage_arr) noexcept
{
	const int      cnt = nbr_coefs + 2 - REMAINING;

	auto           tmp_0 = spl_0;
	tmp_0 += load2f64a (stage_arr [cnt    ]._mem );
	tmp_0 *= load2f64a (stage_arr [cnt    ]._coef);
	tmp_0 -= load2f64a (stage_arr [cnt - 2]._mem );

	auto           tmp_1 = spl_1;
	tmp_1 += load2f64a (stage_arr [cnt + 1]._mem );
	tmp_1 *= load2f64a (stage_arr [cnt + 1]._coef);
	tmp_1 -= load2f64a (stage_arr [cnt - 1]._mem );

	storea (stage_arr [cnt - 2]._mem, spl_0);
	storea (stage_arr [cnt - 1]._mem, spl_1);

	spl_0 = tmp_0;
	spl_1 = tmp_1;

	StageProc2F64Neon <REMAINING - 2>::process_sample_neg (
		nbr_coefs,
		spl_0,
		spl_1,
		stage_arr
	);
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace hiir



#endif // hiir_StageProc2F64Neon_CODEHEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
