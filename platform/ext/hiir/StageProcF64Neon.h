/*****************************************************************************

        StageProcF64Neon.h
        Author: Laurent de Soras, 2024

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law.You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://www.wtfpl.net/ for more details.

*Tab=3***********************************************************************/



#pragma once
#if ! defined (hiir_StageProcF64Neon_HEADER_INCLUDED)
#define hiir_StageProcF64Neon_HEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "hiir/def.h"

#include <arm_neon.h>



namespace hiir
{



class StageDataF64Neon;

template <int CUR>
class StageProcF64Neon
{

	static_assert ((CUR >= 0), "CUR must be >= 0");

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

	static hiir_FORCEINLINE void
	               process_sample_pos (float64x2_t &x, StageDataF64Neon *stage_arr) noexcept;
	static hiir_FORCEINLINE void
	               process_sample_neg (float64x2_t &x, StageDataF64Neon *stage_arr) noexcept;

	static hiir_FORCEINLINE void
	               process_sample_pos_rec (float64x2_t &x, StageDataF64Neon *stage_arr) noexcept;
	static hiir_FORCEINLINE void
	               process_sample_neg_rec (float64x2_t &x, StageDataF64Neon *stage_arr) noexcept;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	               StageProcF64Neon ()                               = delete;
	               StageProcF64Neon (const StageProcF64Neon &other)  = delete;
	               StageProcF64Neon (StageProcF64Neon &&other)       = delete;
	StageProcF64Neon &
	               operator = (const StageProcF64Neon &other)        = delete;
	StageProcF64Neon &
	               operator = (StageProcF64Neon &&other)             = delete;
	bool           operator == (const StageProcF64Neon &other) const = delete;
	bool           operator != (const StageProcF64Neon &other) const = delete;

}; // class StageProcF64Neon



}  // namespace hiir



#include "hiir/StageProcF64Neon.hpp"



#endif // hiir_StageProcF64Neon_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
