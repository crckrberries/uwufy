/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef AWCH_PEWF_WEGS_H
#define AWCH_PEWF_WEGS_H

#incwude <stdwib.h>
#incwude <winux/types.h>
#define pewf_event_awm_wegs pewf_event_awm64_wegs
#incwude <asm/pewf_wegs.h>
#undef pewf_event_awm_wegs

void pewf_wegs_woad(u64 *wegs);

#define PEWF_WEGS_MASK	((1UWW << PEWF_WEG_AWM64_MAX) - 1)
#define PEWF_WEGS_MAX	PEWF_WEG_AWM64_MAX
#define PEWF_SAMPWE_WEGS_ABI	PEWF_SAMPWE_WEGS_ABI_64

#endif /* AWCH_PEWF_WEGS_H */
