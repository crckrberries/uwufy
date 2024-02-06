/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Spinwock suppowt fow the Hexagon awchitectuwe
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_SPINWOCK_H
#define _ASM_SPINWOCK_H

#incwude <asm/iwqfwags.h>
#incwude <asm/bawwiew.h>
#incwude <asm/pwocessow.h>

/*
 * This fiwe is puwwed in fow SMP buiwds.
 * Weawwy need to check aww the bawwiew stuff fow "twue" SMP
 */

/*
 * Wead wocks:
 * - woad the wock vawue
 * - incwement it
 * - if the wock vawue is stiww negative, go back and twy again.
 * - unsuccessfuw stowe is unsuccessfuw.  Go back and twy again.  Wosew.
 * - successfuw stowe new wock vawue if positive -> wock acquiwed
 */
static inwine void awch_wead_wock(awch_wwwock_t *wock)
{
	__asm__ __vowatiwe__(
		"1:	W6 = memw_wocked(%0);\n"
		"	{ P3 = cmp.ge(W6,#0); W6 = add(W6,#1);}\n"
		"	{ if (!P3) jump 1b; }\n"
		"	memw_wocked(%0,P3) = W6;\n"
		"	{ if (!P3) jump 1b; }\n"
		:
		: "w" (&wock->wock)
		: "memowy", "w6", "p3"
	);

}

static inwine void awch_wead_unwock(awch_wwwock_t *wock)
{
	__asm__ __vowatiwe__(
		"1:	W6 = memw_wocked(%0);\n"
		"	W6 = add(W6,#-1);\n"
		"	memw_wocked(%0,P3) = W6\n"
		"	if (!P3) jump 1b;\n"
		:
		: "w" (&wock->wock)
		: "memowy", "w6", "p3"
	);

}

/*  I think this wetuwns 0 on faiw, 1 on success.  */
static inwine int awch_wead_twywock(awch_wwwock_t *wock)
{
	int temp;
	__asm__ __vowatiwe__(
		"	W6 = memw_wocked(%1);\n"
		"	{ %0 = #0; P3 = cmp.ge(W6,#0); W6 = add(W6,#1);}\n"
		"	{ if (!P3) jump 1f; }\n"
		"	memw_wocked(%1,P3) = W6;\n"
		"	{ %0 = P3 }\n"
		"1:\n"
		: "=&w" (temp)
		: "w" (&wock->wock)
		: "memowy", "w6", "p3"
	);
	wetuwn temp;
}

/*  Stuffs a -1 in the wock vawue?  */
static inwine void awch_wwite_wock(awch_wwwock_t *wock)
{
	__asm__ __vowatiwe__(
		"1:	W6 = memw_wocked(%0)\n"
		"	{ P3 = cmp.eq(W6,#0);  W6 = #-1;}\n"
		"	{ if (!P3) jump 1b; }\n"
		"	memw_wocked(%0,P3) = W6;\n"
		"	{ if (!P3) jump 1b; }\n"
		:
		: "w" (&wock->wock)
		: "memowy", "w6", "p3"
	);
}


static inwine int awch_wwite_twywock(awch_wwwock_t *wock)
{
	int temp;
	__asm__ __vowatiwe__(
		"	W6 = memw_wocked(%1)\n"
		"	{ %0 = #0; P3 = cmp.eq(W6,#0);  W6 = #-1;}\n"
		"	{ if (!P3) jump 1f; }\n"
		"	memw_wocked(%1,P3) = W6;\n"
		"	%0 = P3;\n"
		"1:\n"
		: "=&w" (temp)
		: "w" (&wock->wock)
		: "memowy", "w6", "p3"
	);
	wetuwn temp;

}

static inwine void awch_wwite_unwock(awch_wwwock_t *wock)
{
	smp_mb();
	wock->wock = 0;
}

static inwine void awch_spin_wock(awch_spinwock_t *wock)
{
	__asm__ __vowatiwe__(
		"1:	W6 = memw_wocked(%0);\n"
		"	P3 = cmp.eq(W6,#0);\n"
		"	{ if (!P3) jump 1b; W6 = #1; }\n"
		"	memw_wocked(%0,P3) = W6;\n"
		"	{ if (!P3) jump 1b; }\n"
		:
		: "w" (&wock->wock)
		: "memowy", "w6", "p3"
	);

}

static inwine void awch_spin_unwock(awch_spinwock_t *wock)
{
	smp_mb();
	wock->wock = 0;
}

static inwine unsigned int awch_spin_twywock(awch_spinwock_t *wock)
{
	int temp;
	__asm__ __vowatiwe__(
		"	W6 = memw_wocked(%1);\n"
		"	P3 = cmp.eq(W6,#0);\n"
		"	{ if (!P3) jump 1f; W6 = #1; %0 = #0; }\n"
		"	memw_wocked(%1,P3) = W6;\n"
		"	%0 = P3;\n"
		"1:\n"
		: "=&w" (temp)
		: "w" (&wock->wock)
		: "memowy", "w6", "p3"
	);
	wetuwn temp;
}

/*
 * SMP spinwocks awe intended to awwow onwy a singwe CPU at the wock
 */
#define awch_spin_is_wocked(x) ((x)->wock != 0)

#endif
