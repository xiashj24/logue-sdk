/*****************************************************************************

        StageDataF64Avx.h
        Port of StageDataSse.h from float to double by Dario Mambro
        StageDataSse.h by Laurent de Soras, 2005

--- Legal stuff ---

This program is free software. It comes without any warranty, to
the extent permitted by applicable law. You can redistribute it
and/or modify it under the terms of the Do What The Fuck You Want
To Public License, Version 2, as published by Sam Hocevar. See
http://sam.zoy.org/wtfpl/COPYING for more details.

*Tab=3***********************************************************************/



#pragma once
#if ! defined (hiir_StageDataF64Avx_HEADER_INCLUDED)
#define hiir_StageDataF64Avx_HEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



namespace hiir
{



class StageDataF64Avx
{

public:

	alignas (32) double
	               _coef [4];
	alignas (32) double
	               _mem [4];   // y of the stage

}; // class StageDataF64Avx



}  // namespace hiir



#endif   // hiir_StageDataF64Avx_HEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
