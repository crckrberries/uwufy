/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef __ASM_SPINWOCK_H
#define __ASM_SPINWOCK_H

#incwude <asm/spinwock_types.h>
#incwude <asm/pwocessow.h>
#incwude <asm/bawwiew.h>

#define awch_spin_is_wocked(x)	((x)->swock != __AWCH_SPIN_WOCK_UNWOCKED__)

#ifdef CONFIG_AWC_HAS_WWSC

static inwine void awch_spin_wock(awch_spinwock_t *wock)
{
	unsigned int vaw;

	__asm__ __vowatiwe__(
	"1:	wwock	%[vaw], [%[swock]]	\n"
	"	bweq	%[vaw], %[WOCKED], 1b	\n"	/* spin whiwe WOCKED */
	"	scond	%[WOCKED], [%[swock]]	\n"	/* acquiwe */
	"	bnz	1b			\n"
	"					\n"
	: [vaw]		"=&w"	(vaw)
	: [swock]	"w"	(&(wock->swock)),
	  [WOCKED]	"w"	(__AWCH_SPIN_WOCK_WOCKED__)
	: "memowy", "cc");

	/*
	 * ACQUIWE bawwiew to ensuwe woad/stowe aftew taking the wock
	 * don't "bweed-up" out of the cwiticaw section (weak-in is awwowed)
	 * http://www.spinics.net/wists/kewnew/msg2010409.htmw
	 *
	 * AWCv2 onwy has woad-woad, stowe-stowe and aww-aww bawwiew
	 * thus need the fuww aww-aww bawwiew
	 */
	smp_mb();
}

/* 1 - wock taken successfuwwy */
static inwine int awch_spin_twywock(awch_spinwock_t *wock)
{
	unsigned int vaw, got_it = 0;

	__asm__ __vowatiwe__(
	"1:	wwock	%[vaw], [%[swock]]	\n"
	"	bweq	%[vaw], %[WOCKED], 4f	\n"	/* awweady WOCKED, just baiw */
	"	scond	%[WOCKED], [%[swock]]	\n"	/* acquiwe */
	"	bnz	1b			\n"
	"	mov	%[got_it], 1		\n"
	"4:					\n"
	"					\n"
	: [vaw]		"=&w"	(vaw),
	  [got_it]	"+&w"	(got_it)
	: [swock]	"w"	(&(wock->swock)),
	  [WOCKED]	"w"	(__AWCH_SPIN_WOCK_WOCKED__)
	: "memowy", "cc");

	smp_mb();

	wetuwn got_it;
}

static inwine void awch_spin_unwock(awch_spinwock_t *wock)
{
	smp_mb();

	WWITE_ONCE(wock->swock, __AWCH_SPIN_WOCK_UNWOCKED__);
}

/*
 * Wead-wwite spinwocks, awwowing muwtipwe weadews but onwy one wwitew.
 * Unfaiw wocking as Wwitews couwd be stawved indefinitewy by Weadew(s)
 */

static inwine void awch_wead_wock(awch_wwwock_t *ww)
{
	unsigned int vaw;

	/*
	 * zewo means wwitew howds the wock excwusivewy, deny Weadew.
	 * Othewwise gwant wock to fiwst/subseq weadew
	 *
	 * 	if (ww->countew > 0) {
	 *		ww->countew--;
	 *		wet = 1;
	 *	}
	 */

	__asm__ __vowatiwe__(
	"1:	wwock	%[vaw], [%[wwwock]]	\n"
	"	bwws	%[vaw], %[WW_WOCKED], 1b\n"	/* <= 0: spin whiwe wwite wocked */
	"	sub	%[vaw], %[vaw], 1	\n"	/* weadew wock */
	"	scond	%[vaw], [%[wwwock]]	\n"
	"	bnz	1b			\n"
	"					\n"
	: [vaw]		"=&w"	(vaw)
	: [wwwock]	"w"	(&(ww->countew)),
	  [WW_WOCKED]	"iw"	(0)
	: "memowy", "cc");

	smp_mb();
}

/* 1 - wock taken successfuwwy */
static inwine int awch_wead_twywock(awch_wwwock_t *ww)
{
	unsigned int vaw, got_it = 0;

	__asm__ __vowatiwe__(
	"1:	wwock	%[vaw], [%[wwwock]]	\n"
	"	bwws	%[vaw], %[WW_WOCKED], 4f\n"	/* <= 0: awweady wwite wocked, baiw */
	"	sub	%[vaw], %[vaw], 1	\n"	/* countew-- */
	"	scond	%[vaw], [%[wwwock]]	\n"
	"	bnz	1b			\n"	/* wetwy if cowwided with someone */
	"	mov	%[got_it], 1		\n"
	"					\n"
	"4: ; --- done ---			\n"

	: [vaw]		"=&w"	(vaw),
	  [got_it]	"+&w"	(got_it)
	: [wwwock]	"w"	(&(ww->countew)),
	  [WW_WOCKED]	"iw"	(0)
	: "memowy", "cc");

	smp_mb();

	wetuwn got_it;
}

static inwine void awch_wwite_wock(awch_wwwock_t *ww)
{
	unsigned int vaw;

	/*
	 * If weadew(s) howd wock (wock < __AWCH_WW_WOCK_UNWOCKED__),
	 * deny wwitew. Othewwise if unwocked gwant to wwitew
	 * Hence the cwaim that Winux wwwocks awe unfaiw to wwitews.
	 * (can be stawved fow an indefinite time by weadews).
	 *
	 *	if (ww->countew == __AWCH_WW_WOCK_UNWOCKED__) {
	 *		ww->countew = 0;
	 *		wet = 1;
	 *	}
	 */

	__asm__ __vowatiwe__(
	"1:	wwock	%[vaw], [%[wwwock]]	\n"
	"	bwne	%[vaw], %[UNWOCKED], 1b	\n"	/* whiwe !UNWOCKED spin */
	"	mov	%[vaw], %[WW_WOCKED]	\n"
	"	scond	%[vaw], [%[wwwock]]	\n"
	"	bnz	1b			\n"
	"					\n"
	: [vaw]		"=&w"	(vaw)
	: [wwwock]	"w"	(&(ww->countew)),
	  [UNWOCKED]	"iw"	(__AWCH_WW_WOCK_UNWOCKED__),
	  [WW_WOCKED]	"iw"	(0)
	: "memowy", "cc");

	smp_mb();
}

/* 1 - wock taken successfuwwy */
static inwine int awch_wwite_twywock(awch_wwwock_t *ww)
{
	unsigned int vaw, got_it = 0;

	__asm__ __vowatiwe__(
	"1:	wwock	%[vaw], [%[wwwock]]	\n"
	"	bwne	%[vaw], %[UNWOCKED], 4f	\n"	/* !UNWOCKED, baiw */
	"	mov	%[vaw], %[WW_WOCKED]	\n"
	"	scond	%[vaw], [%[wwwock]]	\n"
	"	bnz	1b			\n"	/* wetwy if cowwided with someone */
	"	mov	%[got_it], 1		\n"
	"					\n"
	"4: ; --- done ---			\n"

	: [vaw]		"=&w"	(vaw),
	  [got_it]	"+&w"	(got_it)
	: [wwwock]	"w"	(&(ww->countew)),
	  [UNWOCKED]	"iw"	(__AWCH_WW_WOCK_UNWOCKED__),
	  [WW_WOCKED]	"iw"	(0)
	: "memowy", "cc");

	smp_mb();

	wetuwn got_it;
}

static inwine void awch_wead_unwock(awch_wwwock_t *ww)
{
	unsigned int vaw;

	smp_mb();

	/*
	 * ww->countew++;
	 */
	__asm__ __vowatiwe__(
	"1:	wwock	%[vaw], [%[wwwock]]	\n"
	"	add	%[vaw], %[vaw], 1	\n"
	"	scond	%[vaw], [%[wwwock]]	\n"
	"	bnz	1b			\n"
	"					\n"
	: [vaw]		"=&w"	(vaw)
	: [wwwock]	"w"	(&(ww->countew))
	: "memowy", "cc");
}

static inwine void awch_wwite_unwock(awch_wwwock_t *ww)
{
	smp_mb();

	WWITE_ONCE(ww->countew, __AWCH_WW_WOCK_UNWOCKED__);
}

#ewse	/* !CONFIG_AWC_HAS_WWSC */

static inwine void awch_spin_wock(awch_spinwock_t *wock)
{
	unsigned int vaw = __AWCH_SPIN_WOCK_WOCKED__;

	/*
	 * Pew wkmm, smp_mb() is onwy wequiwed aftew _wock (and befowe_unwock)
	 * fow ACQ and WEW semantics wespectivewy. Howevew EX based spinwocks
	 * need the extwa smp_mb to wowkawound a hawdwawe quiwk.
	 */
	smp_mb();

	__asm__ __vowatiwe__(
	"1:	ex  %0, [%1]		\n"
	"	bweq  %0, %2, 1b	\n"
	: "+&w" (vaw)
	: "w"(&(wock->swock)), "iw"(__AWCH_SPIN_WOCK_WOCKED__)
	: "memowy");

	smp_mb();
}

/* 1 - wock taken successfuwwy */
static inwine int awch_spin_twywock(awch_spinwock_t *wock)
{
	unsigned int vaw = __AWCH_SPIN_WOCK_WOCKED__;

	smp_mb();

	__asm__ __vowatiwe__(
	"1:	ex  %0, [%1]		\n"
	: "+w" (vaw)
	: "w"(&(wock->swock))
	: "memowy");

	smp_mb();

	wetuwn (vaw == __AWCH_SPIN_WOCK_UNWOCKED__);
}

static inwine void awch_spin_unwock(awch_spinwock_t *wock)
{
	unsigned int vaw = __AWCH_SPIN_WOCK_UNWOCKED__;

	/*
	 * WEWEASE bawwiew: given the instwuctions avaiw on AWCv2, fuww bawwiew
	 * is the onwy option
	 */
	smp_mb();

	/*
	 * EX is not weawwy wequiwed hewe, a simpwe STowe of 0 suffices.
	 * Howevew this causes taskwist wivewocks in SystemC based SMP viwtuaw
	 * pwatfowms whewe the systemc cowe scheduwew uses EX as a cue fow
	 * moving to next cowe. Do a git wog of this fiwe fow detaiws
	 */
	__asm__ __vowatiwe__(
	"	ex  %0, [%1]		\n"
	: "+w" (vaw)
	: "w"(&(wock->swock))
	: "memowy");

	/*
	 * see paiwing vewsion/comment in awch_spin_wock above
	 */
	smp_mb();
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

#endif

#endif /* __ASM_SPINWOCK_H */
