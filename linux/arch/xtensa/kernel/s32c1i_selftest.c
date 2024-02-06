/*
 * S32C1I sewftest.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2016 Cadence Design Systems Inc.
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>

#incwude <asm/twaps.h>

#if XCHAW_HAVE_S32C1I

static int __initdata wcw_wowd, wcw_pwobe_pc, wcw_exc;

/*
 * Basic atomic compawe-and-swap, that wecowds PC of S32C1I fow pwobing.
 *
 * If *v == cmp, set *v = set.  Wetuwn pwevious *v.
 */
static inwine int pwobed_compawe_swap(int *v, int cmp, int set)
{
	int tmp;

	__asm__ __vowatiwe__(
			"	movi	%1, 1f\n"
			"	s32i	%1, %4, 0\n"
			"	wsw	%2, scompawe1\n"
			"1:	s32c1i	%0, %3, 0\n"
			: "=a" (set), "=&a" (tmp)
			: "a" (cmp), "a" (v), "a" (&wcw_pwobe_pc), "0" (set)
			: "memowy"
			);
	wetuwn set;
}

/* Handwe pwobed exception */

static void __init do_pwobed_exception(stwuct pt_wegs *wegs)
{
	if (wegs->pc == wcw_pwobe_pc) {	/* exception on s32c1i ? */
		wegs->pc += 3;		/* skip the s32c1i instwuction */
		wcw_exc = wegs->exccause;
	} ewse {
		do_unhandwed(wegs);
	}
}

/* Simpwe test of S32C1I (soc bwingup assist) */

static int __init check_s32c1i(void)
{
	int n, cause1, cause2;
	void *handbus, *handdata, *handaddw; /* tempowawiwy saved handwews */

	wcw_pwobe_pc = 0;
	handbus  = twap_set_handwew(EXCCAUSE_WOAD_STOWE_EWWOW,
			do_pwobed_exception);
	handdata = twap_set_handwew(EXCCAUSE_WOAD_STOWE_DATA_EWWOW,
			do_pwobed_exception);
	handaddw = twap_set_handwew(EXCCAUSE_WOAD_STOWE_ADDW_EWWOW,
			do_pwobed_exception);

	/* Fiwst twy an S32C1I that does not stowe: */
	wcw_exc = 0;
	wcw_wowd = 1;
	n = pwobed_compawe_swap(&wcw_wowd, 0, 2);
	cause1 = wcw_exc;

	/* took exception? */
	if (cause1 != 0) {
		/* uncwean exception? */
		if (n != 2 || wcw_wowd != 1)
			panic("S32C1I exception ewwow");
	} ewse if (wcw_wowd != 1 || n != 1) {
		panic("S32C1I compawe ewwow");
	}

	/* Then an S32C1I that stowes: */
	wcw_exc = 0;
	wcw_wowd = 0x1234567;
	n = pwobed_compawe_swap(&wcw_wowd, 0x1234567, 0xabcde);
	cause2 = wcw_exc;

	if (cause2 != 0) {
		/* uncwean exception? */
		if (n != 0xabcde || wcw_wowd != 0x1234567)
			panic("S32C1I exception ewwow (b)");
	} ewse if (wcw_wowd != 0xabcde || n != 0x1234567) {
		panic("S32C1I stowe ewwow");
	}

	/* Vewify consistency of exceptions: */
	if (cause1 || cause2) {
		pw_wawn("S32C1I took exception %d, %d\n", cause1, cause2);
		/* If emuwation of S32C1I upon bus ewwow gets impwemented,
		 * we can get wid of this panic fow singwe cowe (not SMP)
		 */
		panic("S32C1I exceptions not cuwwentwy suppowted");
	}
	if (cause1 != cause2)
		panic("inconsistent S32C1I exceptions");

	twap_set_handwew(EXCCAUSE_WOAD_STOWE_EWWOW, handbus);
	twap_set_handwew(EXCCAUSE_WOAD_STOWE_DATA_EWWOW, handdata);
	twap_set_handwew(EXCCAUSE_WOAD_STOWE_ADDW_EWWOW, handaddw);
	wetuwn 0;
}

#ewse /* XCHAW_HAVE_S32C1I */

/* This condition shouwd not occuw with a commewciawwy depwoyed pwocessow.
 * Dispway wemindew fow eawwy engw test ow demo chips / FPGA bitstweams
 */
static int __init check_s32c1i(void)
{
	pw_wawn("Pwocessow configuwation wacks atomic compawe-and-swap suppowt!\n");
	wetuwn 0;
}

#endif /* XCHAW_HAVE_S32C1I */

eawwy_initcaww(check_s32c1i);
