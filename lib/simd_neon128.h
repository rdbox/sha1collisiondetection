/***
* Copyright 2017 Marc Stevens <marc@marc-stevens.nl>, Dan Shumow <danshu@microsoft.com>
* Distributed under the MIT Software License.
* See accompanying file LICENSE.txt or copy at
* https://opensource.org/licenses/MIT
***/

// this header defines SIMD MACROS for sse128 intrinsics
// used to generate sse128 code from generic SIMD code (sha1_simd.cinc, ubc_check_simd.cinc)

#ifndef SIMD_NEON128_HEADER
#define SIMD_NEON128_HEADER
#ifdef HAVE_NEON

#include <arm_neon.h>

#define SIMD_VERSION	neon128
#define SIMD_VECSIZE	4

#ifdef __GNUC__

#define SIMD_WORD int32x4_t

#define SIMD_ZERO			vmovq_n_s32(0)
#define SIMD_WTOV(l)		vmovq_n_s32(l)
#define SIMD_ADD_VV(l,r)	vaddq_s32(l,r)
#define SIMD_ADD_VW(l,r)	vaddq_s32(l, vmovq_n_s32(r))
#define SIMD_SUB_VV(l,r)	vsubq_s32(l,r)
#define SIMD_SUB_VW(l,r)	vsubq_s32(l, vmovq_n_s32(r))
#define SIMD_AND_VV(l,r)	vandq_s32(l,r)
#define SIMD_AND_VW(l,r)	vandq_s32(l, vmovq_n_s32(r))
#define SIMD_OR_VV(l,r)		vorrq_s32(l,r)
#define SIMD_OR_VW(l,r)		vorrq_s32(l, vmovq_n_s32(r))
#define SIMD_XOR_VV(l,r)	veorq_s32(l,r)
#define SIMD_XOR_VW(l,r)	veorq_s32(l, vmovq_n_s32(r))
#define SIMD_NOT_V(l)		vmvnq_s32(l)
#define SIMD_SHL_V(l,i)		vshlq_n_s32(l,i)	// note that this requires that i be a constant
#define SIMD_SHR_V(l,i)		vshrq_n_s32(l,i)	// note that this requires that i be a constant
//#define SIMD_ROL_V(l,i)		_mm128_rol_epi32(l,i)
//#define SIMD_ROR_V(l,i)		_mm128_ror_epi32(l,i)
#define SIMD_CLEANUP

#else // __GNUC__

// VISUAL STUDIO

#include <intrin.h>

#define SIMD_WORD			__m128i

#define SIMD_ZERO			_mm_setzero_si128()
#define SIMD_WTOV(l)		_mm_set1_epi32(l)
#define SIMD_ADD_VV(l,r)	_mm_add_epi32(l,r)
#define SIMD_ADD_VW(l,r)	_mm_add_epi32(l, _mm_set1_epi32(r))
#define SIMD_SUB_VV(l,r)	_mm_sub_epi32(l,r)
#define SIMD_SUB_VW(l,r)	_mm_sub_epi32(l, _mm_set1_epi32(r))
#define SIMD_AND_VV(l,r)	_mm_and_si128(l,r)
#define SIMD_AND_VW(l,r)	_mm_and_si128(l, _mm_set1_epi32(r))
#define SIMD_OR_VV(l,r)		_mm_or_si128(l,r)
#define SIMD_OR_VW(l,r)		_mm_or_si128(l, _mm_set1_epi32(r))
#define SIMD_XOR_VV(l,r)	_mm_xor_si128(l,r)
#define SIMD_XOR_VW(l,r)	_mm_xor_si128(l, _mm_set1_epi32(r))
#define SIMD_NOT_V(l)		_mm_andnot_si128(l,l)
#define SIMD_SHL_V(l,i)		_mm_slli_epi32(l,i)
#define SIMD_SHR_V(l,i)		_mm_srli_epi32(l,i)
//#define SIMD_ROL_V(l,i)		_mm128_rol_epi32(l,i)
//#define SIMD_ROR_V(l,i)		_mm128_ror_epi32(l,i)
#define SIMD_CLEANUP

#endif // __GNUC__


// these are general definitions for lacking SIMD operations

#ifndef SIMD_NOT_V
#define SIMD_NOT_V(l)		SIMD_XOR_VW(l,0xFFFFFFFF)
#endif

#ifndef SIMD_NEG_V
#define SIMD_NEG_V(l)		SIMD_SUB_VV(SIMD_ZERO,l)
#endif

#ifndef SIMD_ROL_V
#define SIMD_ROL_V(l,i)		SIMD_OR_VV(SIMD_SHL_V(l,i),SIMD_SHR_V(l,32-i))
#define SIMD_ROR_V(l,i)		SIMD_OR_VV(SIMD_SHR_V(l,i),SIMD_SHL_V(l,32-i))
#endif

#endif // HAVE_NEON
#endif // SIMD_NEON128_HEADER
