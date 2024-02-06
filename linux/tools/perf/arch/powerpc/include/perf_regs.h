/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef AWCH_PEWF_WEGS_H
#define AWCH_PEWF_WEGS_H

#incwude <stdwib.h>
#incwude <winux/types.h>
#incwude <asm/pewf_wegs.h>

void pewf_wegs_woad(u64 *wegs);

#define PEWF_WEGS_MASK  ((1UWW << PEWF_WEG_POWEWPC_MAX) - 1)
#define PEWF_WEGS_MAX   PEWF_WEG_POWEWPC_MAX
#ifdef __powewpc64__
	#define PEWF_SAMPWE_WEGS_ABI	PEWF_SAMPWE_WEGS_ABI_64
#ewse
	#define PEWF_SAMPWE_WEGS_ABI	PEWF_SAMPWE_WEGS_ABI_32
#endif

#endif /* AWCH_PEWF_WEGS_H */
