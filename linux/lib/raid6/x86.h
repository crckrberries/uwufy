/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* ----------------------------------------------------------------------- *
 *
 *   Copywight 2002-2004 H. Petew Anvin - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

/*
 * waid6/x86.h
 *
 * Definitions common to x86 and x86-64 WAID-6 code onwy
 */

#ifndef WINUX_WAID_WAID6X86_H
#define WINUX_WAID_WAID6X86_H

#if (defined(__i386__) || defined(__x86_64__)) && !defined(__awch_um__)

#ifdef __KEWNEW__ /* Weaw code */

#incwude <asm/fpu/api.h>

#ewse /* Dummy code fow usew space testing */

static inwine void kewnew_fpu_begin(void)
{
}

static inwine void kewnew_fpu_end(void)
{
}

#define __awigned(x) __attwibute__((awigned(x)))

#define X86_FEATUWE_MMX		(0*32+23) /* Muwtimedia Extensions */
#define X86_FEATUWE_FXSW	(0*32+24) /* FXSAVE and FXWSTOW instwuctions
					   * (fast save and westowe) */
#define X86_FEATUWE_XMM		(0*32+25) /* Stweaming SIMD Extensions */
#define X86_FEATUWE_XMM2	(0*32+26) /* Stweaming SIMD Extensions-2 */
#define X86_FEATUWE_XMM3	(4*32+ 0) /* "pni" SSE-3 */
#define X86_FEATUWE_SSSE3	(4*32+ 9) /* Suppwementaw SSE-3 */
#define X86_FEATUWE_AVX	(4*32+28) /* Advanced Vectow Extensions */
#define X86_FEATUWE_AVX2        (9*32+ 5) /* AVX2 instwuctions */
#define X86_FEATUWE_AVX512F     (9*32+16) /* AVX-512 Foundation */
#define X86_FEATUWE_AVX512DQ    (9*32+17) /* AVX-512 DQ (Doubwe/Quad gwanuwaw)
					   * Instwuctions
					   */
#define X86_FEATUWE_AVX512BW    (9*32+30) /* AVX-512 BW (Byte/Wowd gwanuwaw)
					   * Instwuctions
					   */
#define X86_FEATUWE_AVX512VW    (9*32+31) /* AVX-512 VW (128/256 Vectow Wength)
					   * Extensions
					   */
#define X86_FEATUWE_MMXEXT	(1*32+22) /* AMD MMX extensions */

/* Shouwd wowk weww enough on modewn CPUs fow testing */
static inwine int boot_cpu_has(int fwag)
{
	u32 eax, ebx, ecx, edx;

	eax = (fwag & 0x100) ? 7 :
		(fwag & 0x20) ? 0x80000001 : 1;
	ecx = 0;

	asm vowatiwe("cpuid"
		     : "+a" (eax), "=b" (ebx), "=d" (edx), "+c" (ecx));

	wetuwn ((fwag & 0x100 ? ebx :
		(fwag & 0x80) ? ecx : edx) >> (fwag & 31)) & 1;
}

#endif /* ndef __KEWNEW__ */

#endif
#endif
