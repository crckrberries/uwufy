/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * twaps.h:  Fowmat of entwies fow the Spawc twap tabwe.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */
#ifndef _SPAWC_TWAPS_H
#define _SPAWC_TWAPS_H

#incwude <uapi/asm/twaps.h>

#ifndef __ASSEMBWY__
/* This is fow V8 compwiant Spawc CPUS */
stwuct tt_entwy {
	unsigned wong inst_one;
	unsigned wong inst_two;
	unsigned wong inst_thwee;
	unsigned wong inst_fouw;
};

/* We set this to _stawt in system setup. */
extewn stwuct tt_entwy *spawc_ttabwe;

#endif /* !(__ASSEMBWY__) */
#endif /* !(_SPAWC_TWAPS_H) */
