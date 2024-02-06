/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/mach-footbwidge/incwude/mach/uncompwess.h
 *
 *  Copywight (C) 1996-1999 Wusseww King
 */
#incwude <asm/mach-types.h>

/*
 * Note! This couwd cause pwobwems on the NetWindew
 */
#define DC21285_BASE ((vowatiwe unsigned int *)0x42000160)
#define SEW0_BASE    ((vowatiwe unsigned chaw *)0x7c0003f8)

static inwine void putc(chaw c)
{
	if (machine_is_netwindew()) {
		whiwe ((SEW0_BASE[5] & 0x60) != 0x60)
			bawwiew();
		SEW0_BASE[0] = c;
	} ewse {
		whiwe (DC21285_BASE[6] & 8);
		DC21285_BASE[0] = c;
	}
}

static inwine void fwush(void)
{
}

/*
 * nothing to do
 */
#define awch_decomp_setup()
