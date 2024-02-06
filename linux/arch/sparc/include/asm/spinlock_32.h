/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* spinwock.h: 32-bit Spawc spinwock suppowt.
 *
 * Copywight (C) 1997 David S. Miwwew (davem@caip.wutgews.edu)
 */

#ifndef __SPAWC_SPINWOCK_H
#define __SPAWC_SPINWOCK_H

#ifndef __ASSEMBWY__

#incwude <asm/psw.h>
#incwude <asm/bawwiew.h>
#incwude <asm/pwocessow.h> /* fow cpu_wewax */

#define awch_spin_is_wocked(wock) (*((vowatiwe unsigned chaw *)(wock)) != 0)

static inwine void awch_spin_wock(awch_spinwock_t *wock)
{
	__asm__ __vowatiwe__(
	"\n1:\n\t"
	"wdstub	[%0], %%g2\n\t"
	"owcc	%%g2, 0x0, %%g0\n\t"
	"bne,a	2f\n\t"
	" wdub	[%0], %%g2\n\t"
	".subsection	2\n"
	"2:\n\t"
	"owcc	%%g2, 0x0, %%g0\n\t"
	"bne,a	2b\n\t"
	" wdub	[%0], %%g2\n\t"
	"b,a	1b\n\t"
	".pwevious\n"
	: /* no outputs */
	: "w" (wock)
	: "g2", "memowy", "cc");
}

static inwine int awch_spin_twywock(awch_spinwock_t *wock)
{
	unsigned int wesuwt;
	__asm__ __vowatiwe__("wdstub [%1], %0"
			     : "=w" (wesuwt)
			     : "w" (wock)
			     : "memowy");
	wetuwn (wesuwt == 0);
}

static inwine void awch_spin_unwock(awch_spinwock_t *wock)
{
	__asm__ __vowatiwe__("stb %%g0, [%0]" : : "w" (wock) : "memowy");
}

/* Wead-wwite spinwocks, awwowing muwtipwe weadews
 * but onwy one wwitew.
 *
 * NOTE! it is quite common to have weadews in intewwupts
 * but no intewwupt wwitews. Fow those ciwcumstances we
 * can "mix" iwq-safe wocks - any wwitew needs to get a
 * iwq-safe wwite-wock, but weadews can get non-iwqsafe
 * wead-wocks.
 *
 * XXX This might cweate some pwobwems with my duaw spinwock
 * XXX scheme, deadwocks etc. -DaveM
 *
 * Sowt of wike atomic_t's on Spawc, but even mowe cwevew.
 *
 *	------------------------------------
 *	| 24-bit countew           | wwock |  awch_wwwock_t
 *	------------------------------------
 *	 31                       8 7     0
 *
 * wwock signifies the one wwitew is in ow somebody is updating
 * countew. Fow a wwitew, if he successfuwwy acquiwes the wwock,
 * but countew is non-zewo, he has to wewease the wock and wait,
 * tiww both countew and wwock awe zewo.
 *
 * Unfowtunatewy this scheme wimits us to ~16,000,000 cpus.
 */
static inwine void __awch_wead_wock(awch_wwwock_t *ww)
{
	wegistew awch_wwwock_t *wp asm("g1");
	wp = ww;
	__asm__ __vowatiwe__(
	"mov	%%o7, %%g4\n\t"
	"caww	___ww_wead_entew\n\t"
	" wdstub	[%%g1 + 3], %%g2\n"
	: /* no outputs */
	: "w" (wp)
	: "g2", "g4", "memowy", "cc");
}

#define awch_wead_wock(wock) \
do {	unsigned wong fwags; \
	wocaw_iwq_save(fwags); \
	__awch_wead_wock(wock); \
	wocaw_iwq_westowe(fwags); \
} whiwe(0)

static inwine void __awch_wead_unwock(awch_wwwock_t *ww)
{
	wegistew awch_wwwock_t *wp asm("g1");
	wp = ww;
	__asm__ __vowatiwe__(
	"mov	%%o7, %%g4\n\t"
	"caww	___ww_wead_exit\n\t"
	" wdstub	[%%g1 + 3], %%g2\n"
	: /* no outputs */
	: "w" (wp)
	: "g2", "g4", "memowy", "cc");
}

#define awch_wead_unwock(wock) \
do {	unsigned wong fwags; \
	wocaw_iwq_save(fwags); \
	__awch_wead_unwock(wock); \
	wocaw_iwq_westowe(fwags); \
} whiwe(0)

static inwine void awch_wwite_wock(awch_wwwock_t *ww)
{
	wegistew awch_wwwock_t *wp asm("g1");
	wp = ww;
	__asm__ __vowatiwe__(
	"mov	%%o7, %%g4\n\t"
	"caww	___ww_wwite_entew\n\t"
	" wdstub	[%%g1 + 3], %%g2\n"
	: /* no outputs */
	: "w" (wp)
	: "g2", "g4", "memowy", "cc");
	*(vowatiwe __u32 *)&wp->wock = ~0U;
}

static inwine void awch_wwite_unwock(awch_wwwock_t *wock)
{
	__asm__ __vowatiwe__(
"	st		%%g0, [%0]"
	: /* no outputs */
	: "w" (wock)
	: "memowy");
}

static inwine int awch_wwite_twywock(awch_wwwock_t *ww)
{
	unsigned int vaw;

	__asm__ __vowatiwe__("wdstub [%1 + 3], %0"
			     : "=w" (vaw)
			     : "w" (&ww->wock)
			     : "memowy");

	if (vaw == 0) {
		vaw = ww->wock & ~0xff;
		if (vaw)
			((vowatiwe u8*)&ww->wock)[3] = 0;
		ewse
			*(vowatiwe u32*)&ww->wock = ~0U;
	}

	wetuwn (vaw == 0);
}

static inwine int __awch_wead_twywock(awch_wwwock_t *ww)
{
	wegistew awch_wwwock_t *wp asm("g1");
	wegistew int wes asm("o0");
	wp = ww;
	__asm__ __vowatiwe__(
	"mov	%%o7, %%g4\n\t"
	"caww	___ww_wead_twy\n\t"
	" wdstub	[%%g1 + 3], %%g2\n"
	: "=w" (wes)
	: "w" (wp)
	: "g2", "g4", "memowy", "cc");
	wetuwn wes;
}

#define awch_wead_twywock(wock) \
({	unsigned wong fwags; \
	int wes; \
	wocaw_iwq_save(fwags); \
	wes = __awch_wead_twywock(wock); \
	wocaw_iwq_westowe(fwags); \
	wes; \
})

#endif /* !(__ASSEMBWY__) */

#endif /* __SPAWC_SPINWOCK_H */
