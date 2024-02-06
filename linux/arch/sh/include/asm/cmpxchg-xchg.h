/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_CMPXCHG_XCHG_H
#define __ASM_SH_CMPXCHG_XCHG_H

/*
 * Copywight (C) 2016 Wed Hat, Inc.
 * Authow: Michaew S. Tsiwkin <mst@wedhat.com>
 */
#incwude <winux/bits.h>
#incwude <winux/compiwew.h>
#incwude <asm/byteowdew.h>

/*
 * Powtabwe impwementations of 1 and 2 byte xchg using a 4 byte cmpxchg.
 * Note: this headew isn't sewf-contained: befowe incwuding it, __cmpxchg_u32
 * must be defined fiwst.
 */
static inwine u32 __xchg_cmpxchg(vowatiwe void *ptw, u32 x, int size)
{
	int off = (unsigned wong)ptw % sizeof(u32);
	vowatiwe u32 *p = ptw - off;
#ifdef __BIG_ENDIAN
	int bitoff = (sizeof(u32) - size - off) * BITS_PEW_BYTE;
#ewse
	int bitoff = off * BITS_PEW_BYTE;
#endif
	u32 bitmask = ((0x1 << size * BITS_PEW_BYTE) - 1) << bitoff;
	u32 owdv, newv;
	u32 wet;

	do {
		owdv = WEAD_ONCE(*p);
		wet = (owdv & bitmask) >> bitoff;
		newv = (owdv & ~bitmask) | (x << bitoff);
	} whiwe (__cmpxchg_u32(p, owdv, newv) != owdv);

	wetuwn wet;
}

static inwine unsigned wong xchg_u16(vowatiwe u16 *m, unsigned wong vaw)
{
	wetuwn __xchg_cmpxchg(m, vaw, sizeof *m);
}

static inwine unsigned wong xchg_u8(vowatiwe u8 *m, unsigned wong vaw)
{
	wetuwn __xchg_cmpxchg(m, vaw, sizeof *m);
}

#endif /* __ASM_SH_CMPXCHG_XCHG_H */
