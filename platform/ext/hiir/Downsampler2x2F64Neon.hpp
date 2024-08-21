/*****************************************************************************

        Downsampler2x2F64Neon.hpp
        Author: Laurent de Soras, 2024

Downsamples vectors of 2 double by a factor 2 the input signal, using Neon
instruction set.

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
#if ! defined (hiir_Downsampler2x2F64Neon_CODEHEADER_INCLUDED)
#define hiir_Downsampler2x2F64Neon_CODEHEADER_INCLUDED



/*\\\ INCLUDE FILES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

#include "hiir/fnc_neon.h"
#include "hiir/StageProc2F64Neon.h"

#include <cassert>



namespace hiir
{



/*\\\ PUBLIC \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*
==============================================================================
Name: ctor
Throws: Nothing
==============================================================================
*/

template <int NC>
Downsampler2x2F64Neon <NC>::Downsampler2x2F64Neon () noexcept
:	_filter ()
{
	for (int i = 0; i < NBR_COEFS + 2; ++i)
	{
		storea (_filter [i]._coef, vdupq_n_f64 (0));
	}

	clear_buffers ();
}



/*
==============================================================================
Name: set_coefs
Description:
	Sets filter coefficients. Generate them with the PolyphaseIir2Designer
	class.
	Call this function before doing any processing.
Input parameters:
	- coef_arr: Array of coefficients. There should be as many coefficients as
		mentioned in the class template parameter.
Throws: Nothing
==============================================================================
*/

template <int NC>
void	Downsampler2x2F64Neon <NC>::set_coefs (const double coef_arr []) noexcept
{
	assert (coef_arr != nullptr);

	for (int i = 0; i < NBR_COEFS; ++i)
	{
		storea (_filter [i + 2]._coef, vdupq_n_f64 (DataType (coef_arr [i])));
	}
}



/*
==============================================================================
Name: process_sample
Description:
	Downsamples (x2) one pair of vector of 2 samples, to generate one output
	vector.
Input parameters:
	- in_ptr: pointer on the two vectors to decimate. No alignment constraint.
Returns: Samplerate-reduced vector.
Throws: Nothing
==============================================================================
*/

template <int NC>
float64x2_t	Downsampler2x2F64Neon <NC>::process_sample (const double in_ptr [_nbr_chn * 2]) noexcept
{
	assert (in_ptr != nullptr);

	const auto     in_0 = load2f64u (in_ptr           );
	const auto     in_1 = load2f64u (in_ptr + _nbr_chn);

	return process_sample (in_0, in_1);
}



/*
==============================================================================
Name: process_sample
Description:
	Downsamples (x2) one pair of vector of 2 samples, to generate one output
	vector.
Input parameters:
	- in_0: vector at t
	- in_1: vector at t + 1
Returns: Samplerate-reduced vector.
Throws: Nothing
==============================================================================
*/

template <int NC>
float64x2_t	Downsampler2x2F64Neon <NC>::process_sample (float64x2_t in_0, float64x2_t in_1) noexcept
{
	auto            spl_0 = in_1;
	auto            spl_1 = in_0;

	StageProc2F64Neon <NBR_COEFS>::process_sample_pos (
		NBR_COEFS, spl_0, spl_1, &_filter [0]
	);

	const auto      sum = spl_0 + spl_1;
	const auto      out = sum * vdupq_n_f64 (0.5f);

	return out;
}



/*
==============================================================================
Name: process_block
Description:
	Downsamples (x2) a block of vectors of 2 samples.
	Input and output blocks may overlap, see assert() for details.
Input parameters:
	- in_ptr: Input array, containing nbr_spl * 2 vectors.
		No alignment constraint.
	- nbr_spl: Number of vectors to output, > 0
Output parameters:
	- out_ptr: Array for the output vectors, capacity: nbr_spl vectors.
		No alignment constraint.
Throws: Nothing
==============================================================================
*/

template <int NC>
void	Downsampler2x2F64Neon <NC>::process_block (double out_ptr [], const double in_ptr [], long nbr_spl) noexcept
{
	assert (in_ptr  != nullptr);
	assert (out_ptr != nullptr);
	assert (out_ptr <= in_ptr || out_ptr >= in_ptr + nbr_spl * (_nbr_chn * 2));
	assert (nbr_spl > 0);

	long           pos = 0;
	do
	{
		const auto     val = process_sample (in_ptr + pos * (_nbr_chn * 2));
		storeu (out_ptr + pos * _nbr_chn, val);
		++ pos;
	}
	while (pos < nbr_spl);
}



/*
==============================================================================
Name: process_sample_split
Description:
	Split (spectrum-wise) in half a pair of vector of 2 samples. The lower part
	of the spectrum is a classic downsampling, equivalent to the output of
	process_sample().
	The higher part is the complementary signal: original filter response
	is flipped from left to right, becoming a high-pass filter with the same
	cutoff frequency. This signal is then critically sampled (decimation by 2),
	flipping the spectrum: Fs/4...Fs/2 becomes Fs/4...0.
Input parameters:
	- in_ptr: pointer on the pair of input vectors. No alignment constraint.
Output parameters:
	- low: output vector, lower part of the spectrum (downsampling)
	- high: output vector, higher part of the spectrum.
Throws: Nothing
==============================================================================
*/

template <int NC>
void	Downsampler2x2F64Neon <NC>::process_sample_split (float64x2_t &low, float64x2_t &high, const double in_ptr [_nbr_chn * 2]) noexcept
{
	assert (in_ptr != nullptr);

	const auto     in_0 = load2f64u (in_ptr           );
	const auto     in_1 = load2f64u (in_ptr + _nbr_chn);

	process_sample_split (low, high, in_0, in_1);
}



/*
==============================================================================
Name: process_sample_split
Description:
	Split (spectrum-wise) in half a pair of vector of 2 samples. The lower part
	of the spectrum is a classic downsampling, equivalent to the output of
	process_sample().
	The higher part is the complementary signal: original filter response
	is flipped from left to right, becoming a high-pass filter with the same
	cutoff frequency. This signal is then critically sampled (decimation by 2),
	flipping the spectrum: Fs/4...Fs/2 becomes Fs/4...0.
Input parameters:
	- in_0: vector at t
	- in_1: vector at t + 1
Output parameters:
	- low: output vector, lower part of the spectrum (downsampling)
	- high: output vector, higher part of the spectrum.
Throws: Nothing
==============================================================================
*/

template <int NC>
void	Downsampler2x2F64Neon <NC>::process_sample_split (float64x2_t &low, float64x2_t &high, float64x2_t in_0, float64x2_t in_1) noexcept
{
	auto           spl_0 = in_1;
	auto           spl_1 = in_0;

	StageProc2F64Neon <NBR_COEFS>::process_sample_pos (
		NBR_COEFS, spl_0, spl_1, &_filter [0]
	);

	const auto     sum = spl_0 + spl_1;
	low  = sum * vdupq_n_f64 (0.5f);
	high = spl_0 - low;
}



/*
==============================================================================
Name: process_block_split
Description:
	Split (spectrum-wise) in half a pair of vector of 2 samples. The lower part
	of the spectrum is a classic downsampling, equivalent to the output of
	process_block().
	The higher part is the complementary signal: original filter response
	is flipped from left to right, becoming a high-pass filter with the same
	cutoff frequency. This signal is then critically sampled (decimation by 2),
	flipping the spectrum: Fs/4...Fs/2 becomes Fs/4...0.
	Input and output blocks may overlap, see assert() for details.
Input parameters:
	- in_ptr: Input array, containing nbr_spl * 2 vectors.
		No alignment constraint.
	- nbr_spl: Number of vectors for each output, > 0
Output parameters:
	- out_l_ptr: Array for the output vectors, lower part of the spectrum
		(downsampling). Capacity: nbr_spl vectors.
		No alignment constraint.
	- out_h_ptr: Array for the output vectors, higher part of the spectrum.
		Capacity: nbr_spl vectors.
		No alignment constraint.
Throws: Nothing
==============================================================================
*/

template <int NC>
void	Downsampler2x2F64Neon <NC>::process_block_split (double out_l_ptr [], double out_h_ptr [], const double in_ptr [], long nbr_spl) noexcept
{
	assert (in_ptr    != nullptr);
	assert (out_l_ptr != nullptr);
	assert (out_l_ptr <= in_ptr || out_l_ptr >= in_ptr + nbr_spl * (_nbr_chn * 2));
	assert (out_h_ptr != nullptr);
	assert (out_h_ptr <= in_ptr || out_h_ptr >= in_ptr + nbr_spl * (_nbr_chn * 2));
	assert (out_h_ptr != out_l_ptr);
	assert (nbr_spl > 0);

	long           pos = 0;
	do
	{
		float64x2_t     low;
		float64x2_t     high;
		process_sample_split (low, high, in_ptr + pos * (_nbr_chn * 2));
		storeu (out_l_ptr + pos * _nbr_chn, low);
		storeu (out_h_ptr + pos * _nbr_chn, high);
		++ pos;
	}
	while (pos < nbr_spl);
}



/*
==============================================================================
Name: clear_buffers
Description:
	Clears filter memory, as if it processed silence since an infinite amount
	of time.
Throws: Nothing
==============================================================================
*/

template <int NC>
void	Downsampler2x2F64Neon <NC>::clear_buffers () noexcept
{
	for (int i = 0; i < NBR_COEFS + 2; ++i)
	{
		storea (_filter [i]._mem, vdupq_n_f64 (0));
	}
}



/*\\\ PROTECTED \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



/*\\\ PRIVATE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/



}  // namespace hiir



#endif // hiir_Downsampler2x2F64Neon_CODEHEADER_INCLUDED



/*\\\ EOF \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/
