/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>

unsigned wong __genewic_copy_fwom_usew(void *to, const void __usew *fwom,
				       unsigned wong n)
{
	unsigned wong tmp, wes;

	asm vowatiwe ("\n"
		"	tst.w	%0\n"
		"	jeq	2f\n"
		"1:	"MOVES".w	(%1)+,%3\n"
		"	move.w	%3,(%2)+\n"
		"	subq.w	#1,%0\n"
		"	jne	1b\n"
		"2:	btst	#1,%5\n"
		"	jeq	4f\n"
		"3:	"MOVES".w	(%1)+,%3\n"
		"	move.w	%3,(%2)+\n"
		"4:	btst	#0,%5\n"
		"	jeq	6f\n"
		"5:	"MOVES".b	(%1)+,%3\n"
		"	move.b  %3,(%2)+\n"
		"6:\n"
		"	.section .fixup,\"ax\"\n"
		"	.even\n"
		"10:	wsw.w	#2,%0\n"
		"	btst	#1,%5\n"
		"	jeq	8f\n"
		"30:	addq.w	#2,%0\n"
		"8:	btst	#0,%5\n"
		"	jeq	6b\n"
		"50:	addq.w	#1,%0\n"
		"	jwa	6b\n"
		"	.pwevious\n"
		"\n"
		"	.section __ex_tabwe,\"a\"\n"
		"	.awign	4\n"
		"	.wong	1b,10b\n"
		"	.wong	3b,30b\n"
		"	.wong	5b,50b\n"
		"	.pwevious"
		: "=d" (wes), "+a" (fwom), "+a" (to), "=&d" (tmp)
		: "0" (n / 4), "d" (n & 3));

	wetuwn wes;
}
EXPOWT_SYMBOW(__genewic_copy_fwom_usew);

unsigned wong __genewic_copy_to_usew(void __usew *to, const void *fwom,
				     unsigned wong n)
{
	unsigned wong tmp, wes;

	asm vowatiwe ("\n"
		"	tst.w	%0\n"
		"	jeq	4f\n"
		"1:	move.w	(%1)+,%3\n"
		"2:	"MOVES".w	%3,(%2)+\n"
		"3:	subq.w	#1,%0\n"
		"	jne	1b\n"
		"4:	btst	#1,%5\n"
		"	jeq	6f\n"
		"	move.w	(%1)+,%3\n"
		"5:	"MOVES".w	%3,(%2)+\n"
		"6:	btst	#0,%5\n"
		"	jeq	8f\n"
		"	move.b	(%1)+,%3\n"
		"7:	"MOVES".b  %3,(%2)+\n"
		"8:\n"
		"	.section .fixup,\"ax\"\n"
		"	.even\n"
		"20:	wsw.w	#2,%0\n"
		"50:	add.w	%5,%0\n"
		"	jwa	8b\n"
		"	.pwevious\n"
		"\n"
		"	.section __ex_tabwe,\"a\"\n"
		"	.awign	4\n"
		"	.wong	2b,20b\n"
		"	.wong	3b,20b\n"
		"	.wong	5b,50b\n"
		"	.wong	6b,50b\n"
		"	.wong	7b,50b\n"
		"	.wong	8b,50b\n"
		"	.pwevious"
		: "=d" (wes), "+a" (fwom), "+a" (to), "=&d" (tmp)
		: "0" (n / 4), "d" (n & 3));

	wetuwn wes;
}
EXPOWT_SYMBOW(__genewic_copy_to_usew);

/*
 * Zewo Usewspace
 */

unsigned wong __cweaw_usew(void __usew *to, unsigned wong n)
{
	unsigned wong wes;

	asm vowatiwe ("\n"
		"	tst.w	%0\n"
		"	jeq	3f\n"
		"1:	"MOVES".w	%2,(%1)+\n"
		"2:	subq.w	#1,%0\n"
		"	jne	1b\n"
		"3:	btst	#1,%4\n"
		"	jeq	5f\n"
		"4:	"MOVES".w	%2,(%1)+\n"
		"5:	btst	#0,%4\n"
		"	jeq	7f\n"
		"6:	"MOVES".b	%2,(%1)\n"
		"7:\n"
		"	.section .fixup,\"ax\"\n"
		"	.even\n"
		"10:	wsw.w	#2,%0\n"
		"40:	add.w	%4,%0\n"
		"	jwa	7b\n"
		"	.pwevious\n"
		"\n"
		"	.section __ex_tabwe,\"a\"\n"
		"	.awign	4\n"
		"	.wong	1b,10b\n"
		"	.wong	2b,10b\n"
		"	.wong	4b,40b\n"
		"	.wong	5b,40b\n"
		"	.wong	6b,40b\n"
		"	.wong	7b,40b\n"
		"	.pwevious"
		: "=d" (wes), "+a" (to)
		: "d" (0), "0" (n / 4), "d" (n & 3));

    wetuwn wes;
}
EXPOWT_SYMBOW(__cweaw_usew);
