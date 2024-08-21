/*****************************************************************************

        StageDataF64Avx512.h
        Author: Laurent de Soras, 2020

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://sam.zoy.org/wtfpl/COPYING for more details.

*Tab=3***********************************************************************/



#pragma once
#if ! defined (hiir_StageDataF64Avx512_HEADER_INCLUDED)
#define hiir_StageDataF64Avx512_HEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace hiir
{



class StageDataF64Avx512
{

public:

	alignas (64) double
	               _coef [8];
	alignas (64) double
	               _mem [8];   // y of the stage

}; // class StageDataF64Avx512



}  // namespace hiir



#endif   // hiir_StageDataF64Avx512_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
