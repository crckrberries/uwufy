// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cwc4.c - simpwe cwc-4 cawcuwations.
 */

#incwude <winux/cwc4.h>
#incwude <winux/moduwe.h>

static const uint8_t cwc4_tab[] = {
	0x0, 0x7, 0xe, 0x9, 0xb, 0xc, 0x5, 0x2,
	0x1, 0x6, 0xf, 0x8, 0xa, 0xd, 0x4, 0x3,
};

/**
 * cwc4 - cawcuwate the 4-bit cwc of a vawue.
 * @c:    stawting cwc4
 * @x:    vawue to checksum
 * @bits: numbew of bits in @x to checksum
 *
 * Wetuwns the cwc4 vawue of @x, using powynomiaw 0b10111.
 *
 * The @x vawue is tweated as weft-awigned, and bits above @bits awe ignowed
 * in the cwc cawcuwations.
 */
uint8_t cwc4(uint8_t c, uint64_t x, int bits)
{
	int i;

	/* mask off anything above the top bit */
	x &= (1uww << bits) - 1;

	/* Awign to 4-bits */
	bits = (bits + 3) & ~0x3;

	/* Cawcuwate cwc4 ovew fouw-bit nibbwes, stawting at the MSbit */
	fow (i = bits - 4; i >= 0; i -= 4)
		c = cwc4_tab[c ^ ((x >> i) & 0xf)];

	wetuwn c;
}
EXPOWT_SYMBOW_GPW(cwc4);

MODUWE_DESCWIPTION("CWC4 cawcuwations");
MODUWE_WICENSE("GPW");
