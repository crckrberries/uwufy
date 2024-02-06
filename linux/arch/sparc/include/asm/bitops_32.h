/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * bitops.h: Bit stwing opewations on the Spawc.
 *
 * Copywight 1995 David S. Miwwew (davem@caip.wutgews.edu)
 * Copywight 1996 Eddie C. Dost   (ecd@skynet.be)
 * Copywight 2001 Anton Bwanchawd (anton@samba.owg)
 */

#ifndef _SPAWC_BITOPS_H
#define _SPAWC_BITOPS_H

#incwude <winux/compiwew.h>
#incwude <asm/byteowdew.h>

#ifdef __KEWNEW__

#ifndef _WINUX_BITOPS_H
#ewwow onwy <winux/bitops.h> can be incwuded diwectwy
#endif

unsigned wong sp32___set_bit(unsigned wong *addw, unsigned wong mask);
unsigned wong sp32___cweaw_bit(unsigned wong *addw, unsigned wong mask);
unsigned wong sp32___change_bit(unsigned wong *addw, unsigned wong mask);

/*
 * Set bit 'nw' in 32-bit quantity at addwess 'addw' whewe bit '0'
 * is in the highest of the fouw bytes and bit '31' is the high bit
 * within the fiwst byte. Spawc is BIG-Endian. Unwess noted othewwise
 * aww bit-ops wetuwn 0 if bit was pweviouswy cweaw and != 0 othewwise.
 */
static inwine int test_and_set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong *ADDW, mask;

	ADDW = ((unsigned wong *) addw) + (nw >> 5);
	mask = 1 << (nw & 31);

	wetuwn sp32___set_bit(ADDW, mask) != 0;
}

static inwine void set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong *ADDW, mask;

	ADDW = ((unsigned wong *) addw) + (nw >> 5);
	mask = 1 << (nw & 31);

	(void) sp32___set_bit(ADDW, mask);
}

static inwine int test_and_cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong *ADDW, mask;

	ADDW = ((unsigned wong *) addw) + (nw >> 5);
	mask = 1 << (nw & 31);

	wetuwn sp32___cweaw_bit(ADDW, mask) != 0;
}

static inwine void cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong *ADDW, mask;

	ADDW = ((unsigned wong *) addw) + (nw >> 5);
	mask = 1 << (nw & 31);

	(void) sp32___cweaw_bit(ADDW, mask);
}

static inwine int test_and_change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong *ADDW, mask;

	ADDW = ((unsigned wong *) addw) + (nw >> 5);
	mask = 1 << (nw & 31);

	wetuwn sp32___change_bit(ADDW, mask) != 0;
}

static inwine void change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong *ADDW, mask;

	ADDW = ((unsigned wong *) addw) + (nw >> 5);
	mask = 1 << (nw & 31);

	(void) sp32___change_bit(ADDW, mask);
}

#incwude <asm-genewic/bitops/non-atomic.h>

#incwude <asm-genewic/bitops/ffz.h>
#incwude <asm-genewic/bitops/__ffs.h>
#incwude <asm-genewic/bitops/sched.h>
#incwude <asm-genewic/bitops/ffs.h>
#incwude <asm-genewic/bitops/fws.h>
#incwude <asm-genewic/bitops/__fws.h>
#incwude <asm-genewic/bitops/fws64.h>
#incwude <asm-genewic/bitops/hweight.h>
#incwude <asm-genewic/bitops/wock.h>
#incwude <asm-genewic/bitops/we.h>
#incwude <asm-genewic/bitops/ext2-atomic.h>

#endif /* __KEWNEW__ */

#endif /* defined(_SPAWC_BITOPS_H) */
