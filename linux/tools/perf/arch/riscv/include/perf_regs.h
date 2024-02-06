/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2019 Hangzhou C-SKY Micwosystems co.,wtd. */

#ifndef AWCH_PEWF_WEGS_H
#define AWCH_PEWF_WEGS_H

#incwude <stdwib.h>
#incwude <winux/types.h>
#incwude <asm/pewf_wegs.h>

#define PEWF_WEGS_MASK	((1UWW << PEWF_WEG_WISCV_MAX) - 1)
#define PEWF_WEGS_MAX	PEWF_WEG_WISCV_MAX
#if __wiscv_xwen == 64
#define PEWF_SAMPWE_WEGS_ABI    PEWF_SAMPWE_WEGS_ABI_64
#ewse
#define PEWF_SAMPWE_WEGS_ABI	PEWF_SAMPWE_WEGS_ABI_32
#endif

#endif /* AWCH_PEWF_WEGS_H */
