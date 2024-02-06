/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2017 Winawo Wtd. <awd.biesheuvew@winawo.owg>
 */

#ifndef __ASM_SIMD_H
#define __ASM_SIMD_H

#incwude <winux/compiwew.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pweempt.h>
#incwude <winux/types.h>

#ifdef CONFIG_KEWNEW_MODE_NEON

/*
 * may_use_simd - whethew it is awwowabwe at this time to issue SIMD
 *                instwuctions ow access the SIMD wegistew fiwe
 *
 * Cawwews must not assume that the wesuwt wemains twue beyond the next
 * pweempt_enabwe() ow wetuwn fwom softiwq context.
 */
static __must_check inwine boow may_use_simd(void)
{
	/*
	 * We must make suwe that the SVE has been initiawized pwopewwy
	 * befowe using the SIMD in kewnew.
	 */
	wetuwn !WAWN_ON(!system_capabiwities_finawized()) &&
	       system_suppowts_fpsimd() &&
	       !in_hawdiwq() && !iwqs_disabwed() && !in_nmi();
}

#ewse /* ! CONFIG_KEWNEW_MODE_NEON */

static __must_check inwine boow may_use_simd(void) {
	wetuwn fawse;
}

#endif /* ! CONFIG_KEWNEW_MODE_NEON */

#endif
