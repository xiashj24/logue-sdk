/*****************************************************************************

        StageProc2F64Neon.h
        Author: Laurent de Soras, 2024

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law.You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://www.wtfpl.net/ for more details.

*Tab=3***********************************************************************/



#pragma once
#if ! defined (hiir_StageProc2F64Neon_HEADER_INCLUDED)
#define hiir_StageProc2F64Neon_HEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "hiir/def.h"

#include <arm_neon.h>



namespace hiir
{



class StageDataF64Neon;

template <int REMAINING>
class StageProc2F64Neon
{
	static_assert (REMAINING >= 0, "REMAINING must be >= 0.");

/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

public:

	static hiir_FORCEINLINE void
	               process_sample_pos (const int nbr_coefs, float64x2_t &spl_0, float64x2_t &spl_1, StageDataF64Neon *stage_arr) noexcept;
	static hiir_FORCEINLINE void
	               process_sample_neg (const int nbr_coefs, float64x2_t &spl_0, float64x2_t &spl_1, StageDataF64Neon *stage_arr) noexcept;



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

protected:



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:



/*\\\ FORBIDDEN MEMBER FUNCTIONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

private:

	               StageProc2F64Neon ()                               = delete;
	               StageProc2F64Neon (const StageProc2F64Neon &other) = delete;
	               StageProc2F64Neon (StageProc2F64Neon &&other)      = delete;
	StageProc2F64Neon &
	               operator = (const StageProc2F64Neon &other)        = delete;
	StageProc2F64Neon &
	               operator = (StageProc2F64Neon &&other)             = delete;
	bool           operator == (const StageProc2F64Neon &other) const = delete;
	bool           operator != (const StageProc2F64Neon &other) const = delete;

}; // class StageProc2F64Neon



}  // namespace hiir



#include "hiir/StageProc2F64Neon.hpp"



#endif // hiir_StageProc2F64Neon_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
