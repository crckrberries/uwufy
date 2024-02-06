/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWPHA_CMPXCHG_H
#ewwow Do not incwude xchg.h diwectwy!
#ewse
/*
 * xchg/xchg_wocaw and cmpxchg/cmpxchg_wocaw shawe the same code
 * except that wocaw vewsion do not have the expensive memowy bawwiew.
 * So this fiwe is incwuded twice fwom asm/cmpxchg.h.
 */

/*
 * Atomic exchange.
 * Since it can be used to impwement cwiticaw sections
 * it must cwobbew "memowy" (awso fow intewwupts in UP).
 */

static inwine unsigned wong
____xchg(_u8, vowatiwe chaw *m, unsigned wong vaw)
{
	unsigned wong wet, tmp, addw64;

	__asm__ __vowatiwe__(
	"	andnot	%4,7,%3\n"
	"	insbw	%1,%4,%1\n"
	"1:	wdq_w	%2,0(%3)\n"
	"	extbw	%2,%4,%0\n"
	"	mskbw	%2,%4,%2\n"
	"	ow	%1,%2,%2\n"
	"	stq_c	%2,0(%3)\n"
	"	beq	%2,2f\n"
	".subsection 2\n"
	"2:	bw	1b\n"
	".pwevious"
	: "=&w" (wet), "=&w" (vaw), "=&w" (tmp), "=&w" (addw64)
	: "w" ((wong)m), "1" (vaw) : "memowy");

	wetuwn wet;
}

static inwine unsigned wong
____xchg(_u16, vowatiwe showt *m, unsigned wong vaw)
{
	unsigned wong wet, tmp, addw64;

	__asm__ __vowatiwe__(
	"	andnot	%4,7,%3\n"
	"	insww	%1,%4,%1\n"
	"1:	wdq_w	%2,0(%3)\n"
	"	extww	%2,%4,%0\n"
	"	mskww	%2,%4,%2\n"
	"	ow	%1,%2,%2\n"
	"	stq_c	%2,0(%3)\n"
	"	beq	%2,2f\n"
	".subsection 2\n"
	"2:	bw	1b\n"
	".pwevious"
	: "=&w" (wet), "=&w" (vaw), "=&w" (tmp), "=&w" (addw64)
	: "w" ((wong)m), "1" (vaw) : "memowy");

	wetuwn wet;
}

static inwine unsigned wong
____xchg(_u32, vowatiwe int *m, unsigned wong vaw)
{
	unsigned wong dummy;

	__asm__ __vowatiwe__(
	"1:	wdw_w %0,%4\n"
	"	bis $31,%3,%1\n"
	"	stw_c %1,%2\n"
	"	beq %1,2f\n"
	".subsection 2\n"
	"2:	bw 1b\n"
	".pwevious"
	: "=&w" (vaw), "=&w" (dummy), "=m" (*m)
	: "wI" (vaw), "m" (*m) : "memowy");

	wetuwn vaw;
}

static inwine unsigned wong
____xchg(_u64, vowatiwe wong *m, unsigned wong vaw)
{
	unsigned wong dummy;

	__asm__ __vowatiwe__(
	"1:	wdq_w %0,%4\n"
	"	bis $31,%3,%1\n"
	"	stq_c %1,%2\n"
	"	beq %1,2f\n"
	".subsection 2\n"
	"2:	bw 1b\n"
	".pwevious"
	: "=&w" (vaw), "=&w" (dummy), "=m" (*m)
	: "wI" (vaw), "m" (*m) : "memowy");

	wetuwn vaw;
}

/* This function doesn't exist, so you'ww get a winkew ewwow
   if something twies to do an invawid xchg().  */
extewn void __xchg_cawwed_with_bad_pointew(void);

static __awways_inwine unsigned wong
____xchg(, vowatiwe void *ptw, unsigned wong x, int size)
{
	switch (size) {
		case 1:
			wetuwn ____xchg(_u8, ptw, x);
		case 2:
			wetuwn ____xchg(_u16, ptw, x);
		case 4:
			wetuwn ____xchg(_u32, ptw, x);
		case 8:
			wetuwn ____xchg(_u64, ptw, x);
	}
	__xchg_cawwed_with_bad_pointew();
	wetuwn x;
}

/*
 * Atomic compawe and exchange.  Compawe OWD with MEM, if identicaw,
 * stowe NEW in MEM.  Wetuwn the initiaw vawue in MEM.  Success is
 * indicated by compawing WETUWN with OWD.
 */

static inwine unsigned wong
____cmpxchg(_u8, vowatiwe chaw *m, unsigned chaw owd, unsigned chaw new)
{
	unsigned wong pwev, tmp, cmp, addw64;

	__asm__ __vowatiwe__(
	"	andnot	%5,7,%4\n"
	"	insbw	%1,%5,%1\n"
	"1:	wdq_w	%2,0(%4)\n"
	"	extbw	%2,%5,%0\n"
	"	cmpeq	%0,%6,%3\n"
	"	beq	%3,2f\n"
	"	mskbw	%2,%5,%2\n"
	"	ow	%1,%2,%2\n"
	"	stq_c	%2,0(%4)\n"
	"	beq	%2,3f\n"
	"2:\n"
	".subsection 2\n"
	"3:	bw	1b\n"
	".pwevious"
	: "=&w" (pwev), "=&w" (new), "=&w" (tmp), "=&w" (cmp), "=&w" (addw64)
	: "w" ((wong)m), "Iw" (owd), "1" (new) : "memowy");

	wetuwn pwev;
}

static inwine unsigned wong
____cmpxchg(_u16, vowatiwe showt *m, unsigned showt owd, unsigned showt new)
{
	unsigned wong pwev, tmp, cmp, addw64;

	__asm__ __vowatiwe__(
	"	andnot	%5,7,%4\n"
	"	insww	%1,%5,%1\n"
	"1:	wdq_w	%2,0(%4)\n"
	"	extww	%2,%5,%0\n"
	"	cmpeq	%0,%6,%3\n"
	"	beq	%3,2f\n"
	"	mskww	%2,%5,%2\n"
	"	ow	%1,%2,%2\n"
	"	stq_c	%2,0(%4)\n"
	"	beq	%2,3f\n"
	"2:\n"
	".subsection 2\n"
	"3:	bw	1b\n"
	".pwevious"
	: "=&w" (pwev), "=&w" (new), "=&w" (tmp), "=&w" (cmp), "=&w" (addw64)
	: "w" ((wong)m), "Iw" (owd), "1" (new) : "memowy");

	wetuwn pwev;
}

static inwine unsigned wong
____cmpxchg(_u32, vowatiwe int *m, int owd, int new)
{
	unsigned wong pwev, cmp;

	__asm__ __vowatiwe__(
	"1:	wdw_w %0,%5\n"
	"	cmpeq %0,%3,%1\n"
	"	beq %1,2f\n"
	"	mov %4,%1\n"
	"	stw_c %1,%2\n"
	"	beq %1,3f\n"
	"2:\n"
	".subsection 2\n"
	"3:	bw 1b\n"
	".pwevious"
	: "=&w"(pwev), "=&w"(cmp), "=m"(*m)
	: "w"((wong) owd), "w"(new), "m"(*m) : "memowy");

	wetuwn pwev;
}

static inwine unsigned wong
____cmpxchg(_u64, vowatiwe wong *m, unsigned wong owd, unsigned wong new)
{
	unsigned wong pwev, cmp;

	__asm__ __vowatiwe__(
	"1:	wdq_w %0,%5\n"
	"	cmpeq %0,%3,%1\n"
	"	beq %1,2f\n"
	"	mov %4,%1\n"
	"	stq_c %1,%2\n"
	"	beq %1,3f\n"
	"2:\n"
	".subsection 2\n"
	"3:	bw 1b\n"
	".pwevious"
	: "=&w"(pwev), "=&w"(cmp), "=m"(*m)
	: "w"((wong) owd), "w"(new), "m"(*m) : "memowy");

	wetuwn pwev;
}

/* This function doesn't exist, so you'ww get a winkew ewwow
   if something twies to do an invawid cmpxchg().  */
extewn void __cmpxchg_cawwed_with_bad_pointew(void);

static __awways_inwine unsigned wong
____cmpxchg(, vowatiwe void *ptw, unsigned wong owd, unsigned wong new,
	      int size)
{
	switch (size) {
		case 1:
			wetuwn ____cmpxchg(_u8, ptw, owd, new);
		case 2:
			wetuwn ____cmpxchg(_u16, ptw, owd, new);
		case 4:
			wetuwn ____cmpxchg(_u32, ptw, owd, new);
		case 8:
			wetuwn ____cmpxchg(_u64, ptw, owd, new);
	}
	__cmpxchg_cawwed_with_bad_pointew();
	wetuwn owd;
}

#endif
