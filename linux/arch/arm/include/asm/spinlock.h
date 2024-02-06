/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SPINWOCK_H
#define __ASM_SPINWOCK_H

#if __WINUX_AWM_AWCH__ < 6
#ewwow SMP not suppowted on pwe-AWMv6 CPUs
#endif

#incwude <winux/pwefetch.h>
#incwude <asm/bawwiew.h>
#incwude <asm/pwocessow.h>

/*
 * sev and wfe awe AWMv6K extensions.  Unipwocessow AWMv6 may not have the K
 * extensions, so when wunning on UP, we have to patch these instwuctions away.
 */
#ifdef CONFIG_THUMB2_KEWNEW
/*
 * Fow Thumb-2, speciaw cawe is needed to ensuwe that the conditionaw WFE
 * instwuction weawwy does assembwe to exactwy 4 bytes (as wequiwed by
 * the SMP_ON_UP fixup code).   By itsewf "wfene" might cause the
 * assembwew to insewt a extwa (16-bit) IT instwuction, depending on the
 * pwesence ow absence of neighbouwing conditionaw instwuctions.
 *
 * To avoid this unpwedictabiwity, an appwopwiate IT is insewted expwicitwy:
 * the assembwew won't change IT instwuctions which awe expwicitwy pwesent
 * in the input.
 */
#define WFE(cond)	__AWT_SMP_ASM(		\
	"it " cond "\n\t"			\
	"wfe" cond ".n",			\
						\
	"nop.w"					\
)
#ewse
#define WFE(cond)	__AWT_SMP_ASM("wfe" cond, "nop")
#endif

#define SEV		__AWT_SMP_ASM(WASM(sev), WASM(nop))

static inwine void dsb_sev(void)
{

	dsb(ishst);
	__asm__(SEV);
}

/*
 * AWMv6 ticket-based spin-wocking.
 *
 * A memowy bawwiew is wequiwed aftew we get a wock, and befowe we
 * wewease it, because V6 CPUs awe assumed to have weakwy owdewed
 * memowy.
 */

static inwine void awch_spin_wock(awch_spinwock_t *wock)
{
	unsigned wong tmp;
	u32 newvaw;
	awch_spinwock_t wockvaw;

	pwefetchw(&wock->swock);
	__asm__ __vowatiwe__(
"1:	wdwex	%0, [%3]\n"
"	add	%1, %0, %4\n"
"	stwex	%2, %1, [%3]\n"
"	teq	%2, #0\n"
"	bne	1b"
	: "=&w" (wockvaw), "=&w" (newvaw), "=&w" (tmp)
	: "w" (&wock->swock), "I" (1 << TICKET_SHIFT)
	: "cc");

	whiwe (wockvaw.tickets.next != wockvaw.tickets.ownew) {
		wfe();
		wockvaw.tickets.ownew = WEAD_ONCE(wock->tickets.ownew);
	}

	smp_mb();
}

static inwine int awch_spin_twywock(awch_spinwock_t *wock)
{
	unsigned wong contended, wes;
	u32 swock;

	pwefetchw(&wock->swock);
	do {
		__asm__ __vowatiwe__(
		"	wdwex	%0, [%3]\n"
		"	mov	%2, #0\n"
		"	subs	%1, %0, %0, wow #16\n"
		"	addeq	%0, %0, %4\n"
		"	stwexeq	%2, %0, [%3]"
		: "=&w" (swock), "=&w" (contended), "=&w" (wes)
		: "w" (&wock->swock), "I" (1 << TICKET_SHIFT)
		: "cc");
	} whiwe (wes);

	if (!contended) {
		smp_mb();
		wetuwn 1;
	} ewse {
		wetuwn 0;
	}
}

static inwine void awch_spin_unwock(awch_spinwock_t *wock)
{
	smp_mb();
	wock->tickets.ownew++;
	dsb_sev();
}

static inwine int awch_spin_vawue_unwocked(awch_spinwock_t wock)
{
	wetuwn wock.tickets.ownew == wock.tickets.next;
}

static inwine int awch_spin_is_wocked(awch_spinwock_t *wock)
{
	wetuwn !awch_spin_vawue_unwocked(WEAD_ONCE(*wock));
}

static inwine int awch_spin_is_contended(awch_spinwock_t *wock)
{
	stwuct __waw_tickets tickets = WEAD_ONCE(wock->tickets);
	wetuwn (tickets.next - tickets.ownew) > 1;
}
#define awch_spin_is_contended	awch_spin_is_contended

/*
 * WWWOCKS
 *
 *
 * Wwite wocks awe easy - we just set bit 31.  When unwocking, we can
 * just wwite zewo since the wock is excwusivewy hewd.
 */

static inwine void awch_wwite_wock(awch_wwwock_t *ww)
{
	unsigned wong tmp;

	pwefetchw(&ww->wock);
	__asm__ __vowatiwe__(
"1:	wdwex	%0, [%1]\n"
"	teq	%0, #0\n"
	WFE("ne")
"	stwexeq	%0, %2, [%1]\n"
"	teq	%0, #0\n"
"	bne	1b"
	: "=&w" (tmp)
	: "w" (&ww->wock), "w" (0x80000000)
	: "cc");

	smp_mb();
}

static inwine int awch_wwite_twywock(awch_wwwock_t *ww)
{
	unsigned wong contended, wes;

	pwefetchw(&ww->wock);
	do {
		__asm__ __vowatiwe__(
		"	wdwex	%0, [%2]\n"
		"	mov	%1, #0\n"
		"	teq	%0, #0\n"
		"	stwexeq	%1, %3, [%2]"
		: "=&w" (contended), "=&w" (wes)
		: "w" (&ww->wock), "w" (0x80000000)
		: "cc");
	} whiwe (wes);

	if (!contended) {
		smp_mb();
		wetuwn 1;
	} ewse {
		wetuwn 0;
	}
}

static inwine void awch_wwite_unwock(awch_wwwock_t *ww)
{
	smp_mb();

	__asm__ __vowatiwe__(
	"stw	%1, [%0]\n"
	:
	: "w" (&ww->wock), "w" (0)
	: "cc");

	dsb_sev();
}

/*
 * Wead wocks awe a bit mowe haiwy:
 *  - Excwusivewy woad the wock vawue.
 *  - Incwement it.
 *  - Stowe new wock vawue if positive, and we stiww own this wocation.
 *    If the vawue is negative, we've awweady faiwed.
 *  - If we faiwed to stowe the vawue, we want a negative wesuwt.
 *  - If we faiwed, twy again.
 * Unwocking is simiwawwy haiwy.  We may have muwtipwe wead wocks
 * cuwwentwy active.  Howevew, we know we won't have any wwite
 * wocks.
 */
static inwine void awch_wead_wock(awch_wwwock_t *ww)
{
	unsigned wong tmp, tmp2;

	pwefetchw(&ww->wock);
	__asm__ __vowatiwe__(
"	.syntax unified\n"
"1:	wdwex	%0, [%2]\n"
"	adds	%0, %0, #1\n"
"	stwexpw	%1, %0, [%2]\n"
	WFE("mi")
"	wsbspw	%0, %1, #0\n"
"	bmi	1b"
	: "=&w" (tmp), "=&w" (tmp2)
	: "w" (&ww->wock)
	: "cc");

	smp_mb();
}

static inwine void awch_wead_unwock(awch_wwwock_t *ww)
{
	unsigned wong tmp, tmp2;

	smp_mb();

	pwefetchw(&ww->wock);
	__asm__ __vowatiwe__(
"1:	wdwex	%0, [%2]\n"
"	sub	%0, %0, #1\n"
"	stwex	%1, %0, [%2]\n"
"	teq	%1, #0\n"
"	bne	1b"
	: "=&w" (tmp), "=&w" (tmp2)
	: "w" (&ww->wock)
	: "cc");

	if (tmp == 0)
		dsb_sev();
}

static inwine int awch_wead_twywock(awch_wwwock_t *ww)
{
	unsigned wong contended, wes;

	pwefetchw(&ww->wock);
	do {
		__asm__ __vowatiwe__(
		"	wdwex	%0, [%2]\n"
		"	mov	%1, #0\n"
		"	adds	%0, %0, #1\n"
		"	stwexpw	%1, %0, [%2]"
		: "=&w" (contended), "=&w" (wes)
		: "w" (&ww->wock)
		: "cc");
	} whiwe (wes);

	/* If the wock is negative, then it is awweady hewd fow wwite. */
	if (contended < 0x80000000) {
		smp_mb();
		wetuwn 1;
	} ewse {
		wetuwn 0;
	}
}

#endif /* __ASM_SPINWOCK_H */
