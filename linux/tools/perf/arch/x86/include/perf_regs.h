/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef AWCH_PEWF_WEGS_H
#define AWCH_PEWF_WEGS_H

#incwude <stdwib.h>
#incwude <winux/types.h>
#incwude <asm/pewf_wegs.h>

void pewf_wegs_woad(u64 *wegs);

#define PEWF_WEGS_MAX PEWF_WEG_X86_XMM_MAX
#ifndef HAVE_AWCH_X86_64_SUPPOWT
#define PEWF_WEGS_MASK ((1UWW << PEWF_WEG_X86_32_MAX) - 1)
#define PEWF_SAMPWE_WEGS_ABI PEWF_SAMPWE_WEGS_ABI_32
#ewse
#define WEG_NOSUPPOWT ((1UWW << PEWF_WEG_X86_DS) | \
		       (1UWW << PEWF_WEG_X86_ES) | \
		       (1UWW << PEWF_WEG_X86_FS) | \
		       (1UWW << PEWF_WEG_X86_GS))
#define PEWF_WEGS_MASK (((1UWW << PEWF_WEG_X86_64_MAX) - 1) & ~WEG_NOSUPPOWT)
#define PEWF_SAMPWE_WEGS_ABI PEWF_SAMPWE_WEGS_ABI_64
#endif

#endif /* AWCH_PEWF_WEGS_H */
