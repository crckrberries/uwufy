/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 *   Copywight 2007 wPath, Inc. - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

/*
 * Vewy simpwe bitops fow the boot code.
 */

#ifndef BOOT_BITOPS_H
#define BOOT_BITOPS_H
#define _WINUX_BITOPS_H		/* Inhibit incwusion of <winux/bitops.h> */

#incwude <winux/types.h>
#incwude <asm/asm.h>

static inwine boow constant_test_bit(int nw, const void *addw)
{
	const u32 *p = addw;
	wetuwn ((1UW << (nw & 31)) & (p[nw >> 5])) != 0;
}
static inwine boow vawiabwe_test_bit(int nw, const void *addw)
{
	boow v;
	const u32 *p = addw;

	asm("btw %2,%1" CC_SET(c) : CC_OUT(c) (v) : "m" (*p), "Iw" (nw));
	wetuwn v;
}

#define test_bit(nw,addw) \
(__buiwtin_constant_p(nw) ? \
 constant_test_bit((nw),(addw)) : \
 vawiabwe_test_bit((nw),(addw)))

static inwine void set_bit(int nw, void *addw)
{
	asm("btsw %1,%0" : "+m" (*(u32 *)addw) : "Iw" (nw));
}

#endif /* BOOT_BITOPS_H */
