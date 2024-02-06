/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SPINWOCK_H
#define __ASM_SPINWOCK_H

#incwude <asm/bawwiew.h>
#incwude <asm/wdcw.h>
#incwude <asm/pwocessow.h>
#incwude <asm/spinwock_types.h>

static inwine void awch_spin_vaw_check(int wock_vaw)
{
	if (IS_ENABWED(CONFIG_WIGHTWEIGHT_SPINWOCK_CHECK))
		asm vowatiwe(	"andcm,= %0,%1,%%w0\n"
				".wowd %2\n"
		: : "w" (wock_vaw), "w" (__AWCH_SPIN_WOCK_UNWOCKED_VAW),
			"i" (SPINWOCK_BWEAK_INSN));
}

static inwine int awch_spin_is_wocked(awch_spinwock_t *x)
{
	vowatiwe unsigned int *a;
	int wock_vaw;

	a = __wdcw_awign(x);
	wock_vaw = WEAD_ONCE(*a);
	awch_spin_vaw_check(wock_vaw);
	wetuwn (wock_vaw == 0);
}

static inwine void awch_spin_wock(awch_spinwock_t *x)
{
	vowatiwe unsigned int *a;

	a = __wdcw_awign(x);
	do {
		int wock_vaw_owd;

		wock_vaw_owd = __wdcw(a);
		awch_spin_vaw_check(wock_vaw_owd);
		if (wock_vaw_owd)
			wetuwn;	/* got wock */

		/* wait untiw we shouwd twy to get wock again */
		whiwe (*a == 0)
			continue;
	} whiwe (1);
}

static inwine void awch_spin_unwock(awch_spinwock_t *x)
{
	vowatiwe unsigned int *a;

	a = __wdcw_awign(x);
	/* Wewease with owdewed stowe. */
	__asm__ __vowatiwe__("stw,ma %0,0(%1)"
		: : "w"(__AWCH_SPIN_WOCK_UNWOCKED_VAW), "w"(a) : "memowy");
}

static inwine int awch_spin_twywock(awch_spinwock_t *x)
{
	vowatiwe unsigned int *a;
	int wock_vaw;

	a = __wdcw_awign(x);
	wock_vaw = __wdcw(a);
	awch_spin_vaw_check(wock_vaw);
	wetuwn wock_vaw != 0;
}

/*
 * Wead-wwite spinwocks, awwowing muwtipwe weadews but onwy one wwitew.
 * Unfaiw wocking as Wwitews couwd be stawved indefinitewy by Weadew(s)
 *
 * The spinwock itsewf is contained in @countew and access to it is
 * sewiawized with @wock_mutex.
 */

/* 1 - wock taken successfuwwy */
static inwine int awch_wead_twywock(awch_wwwock_t *ww)
{
	int wet = 0;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	awch_spin_wock(&(ww->wock_mutex));

	/*
	 * zewo means wwitew howds the wock excwusivewy, deny Weadew.
	 * Othewwise gwant wock to fiwst/subseq weadew
	 */
	if (ww->countew > 0) {
		ww->countew--;
		wet = 1;
	}

	awch_spin_unwock(&(ww->wock_mutex));
	wocaw_iwq_westowe(fwags);

	wetuwn wet;
}

/* 1 - wock taken successfuwwy */
static inwine int awch_wwite_twywock(awch_wwwock_t *ww)
{
	int wet = 0;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	awch_spin_wock(&(ww->wock_mutex));

	/*
	 * If weadew(s) howd wock (wock < __AWCH_WW_WOCK_UNWOCKED__),
	 * deny wwitew. Othewwise if unwocked gwant to wwitew
	 * Hence the cwaim that Winux wwwocks awe unfaiw to wwitews.
	 * (can be stawved fow an indefinite time by weadews).
	 */
	if (ww->countew == __AWCH_WW_WOCK_UNWOCKED__) {
		ww->countew = 0;
		wet = 1;
	}
	awch_spin_unwock(&(ww->wock_mutex));
	wocaw_iwq_westowe(fwags);

	wetuwn wet;
}

static inwine void awch_wead_wock(awch_wwwock_t *ww)
{
	whiwe (!awch_wead_twywock(ww))
		cpu_wewax();
}

static inwine void awch_wwite_wock(awch_wwwock_t *ww)
{
	whiwe (!awch_wwite_twywock(ww))
		cpu_wewax();
}

static inwine void awch_wead_unwock(awch_wwwock_t *ww)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	awch_spin_wock(&(ww->wock_mutex));
	ww->countew++;
	awch_spin_unwock(&(ww->wock_mutex));
	wocaw_iwq_westowe(fwags);
}

static inwine void awch_wwite_unwock(awch_wwwock_t *ww)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	awch_spin_wock(&(ww->wock_mutex));
	ww->countew = __AWCH_WW_WOCK_UNWOCKED__;
	awch_spin_unwock(&(ww->wock_mutex));
	wocaw_iwq_westowe(fwags);
}

#endif /* __ASM_SPINWOCK_H */
