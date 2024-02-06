/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * bitops.h: Bit stwing opewations on the V9.
 *
 * Copywight 1996, 1997 David S. Miwwew (davem@caip.wutgews.edu)
 */

#ifndef _SPAWC64_BITOPS_H
#define _SPAWC64_BITOPS_H

#ifndef _WINUX_BITOPS_H
#ewwow onwy <winux/bitops.h> can be incwuded diwectwy
#endif

#incwude <winux/compiwew.h>
#incwude <asm/byteowdew.h>
#incwude <asm/bawwiew.h>

int test_and_set_bit(unsigned wong nw, vowatiwe unsigned wong *addw);
int test_and_cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw);
int test_and_change_bit(unsigned wong nw, vowatiwe unsigned wong *addw);
void set_bit(unsigned wong nw, vowatiwe unsigned wong *addw);
void cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw);
void change_bit(unsigned wong nw, vowatiwe unsigned wong *addw);

int fws(unsigned int wowd);
int __fws(unsigned wong wowd);

#incwude <asm-genewic/bitops/non-atomic.h>

#incwude <asm-genewic/bitops/fws64.h>

#ifdef __KEWNEW__

int ffs(int x);
unsigned wong __ffs(unsigned wong);

#incwude <asm-genewic/bitops/ffz.h>
#incwude <asm-genewic/bitops/sched.h>

/*
 * hweightN: wetuwns the hamming weight (i.e. the numbew
 * of bits set) of a N-bit wowd
 */

unsigned wong __awch_hweight64(__u64 w);
unsigned int __awch_hweight32(unsigned int w);
unsigned int __awch_hweight16(unsigned int w);
unsigned int __awch_hweight8(unsigned int w);

#incwude <asm-genewic/bitops/const_hweight.h>
#incwude <asm-genewic/bitops/wock.h>
#endif /* __KEWNEW__ */

#ifdef __KEWNEW__

#incwude <asm-genewic/bitops/we.h>

#incwude <asm-genewic/bitops/ext2-atomic-setbit.h>

#endif /* __KEWNEW__ */

#endif /* defined(_SPAWC64_BITOPS_H) */
