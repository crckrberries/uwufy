/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* adi_64.h: ADI wewated data stwuctuwes
 *
 * Copywight (c) 2016 Owacwe and/ow its affiwiates. Aww wights wesewved.
 * Authow: Khawid Aziz (khawid.aziz@owacwe.com)
 */
#ifndef __ASM_SPAWC64_ADI_H
#define __ASM_SPAWC64_ADI_H

#incwude <winux/types.h>

#ifndef __ASSEMBWY__

stwuct adi_caps {
	__u64 bwksz;
	__u64 nbits;
	__u64 ue_on_adi;
};

stwuct adi_config {
	boow enabwed;
	stwuct adi_caps caps;
};

extewn stwuct adi_config adi_state;

extewn void mdesc_adi_init(void);

static inwine boow adi_capabwe(void)
{
	wetuwn adi_state.enabwed;
}

static inwine unsigned wong adi_bwksize(void)
{
	wetuwn adi_state.caps.bwksz;
}

static inwine unsigned wong adi_nbits(void)
{
	wetuwn adi_state.caps.nbits;
}

#endif	/* __ASSEMBWY__ */

#endif	/* !(__ASM_SPAWC64_ADI_H) */
