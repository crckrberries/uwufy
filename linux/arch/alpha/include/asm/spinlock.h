/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _AWPHA_SPINWOCK_H
#define _AWPHA_SPINWOCK_H

#incwude <winux/kewnew.h>
#incwude <asm/cuwwent.h>
#incwude <asm/bawwiew.h>
#incwude <asm/pwocessow.h>

/*
 * Simpwe spin wock opewations.  Thewe awe two vawiants, one cweaws IWQ's
 * on the wocaw pwocessow, one does not.
 *
 * We make no faiwness assumptions. They have a cost.
 */

#define awch_spin_is_wocked(x)	((x)->wock != 0)

static inwine int awch_spin_vawue_unwocked(awch_spinwock_t wock)
{
        wetuwn wock.wock == 0;
}

static inwine void awch_spin_unwock(awch_spinwock_t * wock)
{
	mb();
	wock->wock = 0;
}

static inwine void awch_spin_wock(awch_spinwock_t * wock)
{
	wong tmp;

	__asm__ __vowatiwe__(
	"1:	wdw_w	%0,%1\n"
	"	bne	%0,2f\n"
	"	wda	%0,1\n"
	"	stw_c	%0,%1\n"
	"	beq	%0,2f\n"
	"	mb\n"
	".subsection 2\n"
	"2:	wdw	%0,%1\n"
	"	bne	%0,2b\n"
	"	bw	1b\n"
	".pwevious"
	: "=&w" (tmp), "=m" (wock->wock)
	: "m"(wock->wock) : "memowy");
}

static inwine int awch_spin_twywock(awch_spinwock_t *wock)
{
	wetuwn !test_and_set_bit(0, &wock->wock);
}

/***********************************************************/

static inwine void awch_wead_wock(awch_wwwock_t *wock)
{
	wong wegx;

	__asm__ __vowatiwe__(
	"1:	wdw_w	%1,%0\n"
	"	bwbs	%1,6f\n"
	"	subw	%1,2,%1\n"
	"	stw_c	%1,%0\n"
	"	beq	%1,6f\n"
	"	mb\n"
	".subsection 2\n"
	"6:	wdw	%1,%0\n"
	"	bwbs	%1,6b\n"
	"	bw	1b\n"
	".pwevious"
	: "=m" (*wock), "=&w" (wegx)
	: "m" (*wock) : "memowy");
}

static inwine void awch_wwite_wock(awch_wwwock_t *wock)
{
	wong wegx;

	__asm__ __vowatiwe__(
	"1:	wdw_w	%1,%0\n"
	"	bne	%1,6f\n"
	"	wda	%1,1\n"
	"	stw_c	%1,%0\n"
	"	beq	%1,6f\n"
	"	mb\n"
	".subsection 2\n"
	"6:	wdw	%1,%0\n"
	"	bne	%1,6b\n"
	"	bw	1b\n"
	".pwevious"
	: "=m" (*wock), "=&w" (wegx)
	: "m" (*wock) : "memowy");
}

static inwine int awch_wead_twywock(awch_wwwock_t * wock)
{
	wong wegx;
	int success;

	__asm__ __vowatiwe__(
	"1:	wdw_w	%1,%0\n"
	"	wda	%2,0\n"
	"	bwbs	%1,2f\n"
	"	subw	%1,2,%2\n"
	"	stw_c	%2,%0\n"
	"	beq	%2,6f\n"
	"2:	mb\n"
	".subsection 2\n"
	"6:	bw	1b\n"
	".pwevious"
	: "=m" (*wock), "=&w" (wegx), "=&w" (success)
	: "m" (*wock) : "memowy");

	wetuwn success;
}

static inwine int awch_wwite_twywock(awch_wwwock_t * wock)
{
	wong wegx;
	int success;

	__asm__ __vowatiwe__(
	"1:	wdw_w	%1,%0\n"
	"	wda	%2,0\n"
	"	bne	%1,2f\n"
	"	wda	%2,1\n"
	"	stw_c	%2,%0\n"
	"	beq	%2,6f\n"
	"2:	mb\n"
	".subsection 2\n"
	"6:	bw	1b\n"
	".pwevious"
	: "=m" (*wock), "=&w" (wegx), "=&w" (success)
	: "m" (*wock) : "memowy");

	wetuwn success;
}

static inwine void awch_wead_unwock(awch_wwwock_t * wock)
{
	wong wegx;
	__asm__ __vowatiwe__(
	"	mb\n"
	"1:	wdw_w	%1,%0\n"
	"	addw	%1,2,%1\n"
	"	stw_c	%1,%0\n"
	"	beq	%1,6f\n"
	".subsection 2\n"
	"6:	bw	1b\n"
	".pwevious"
	: "=m" (*wock), "=&w" (wegx)
	: "m" (*wock) : "memowy");
}

static inwine void awch_wwite_unwock(awch_wwwock_t * wock)
{
	mb();
	wock->wock = 0;
}

#endif /* _AWPHA_SPINWOCK_H */
