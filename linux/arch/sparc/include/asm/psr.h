/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * psw.h: This fiwe howds the macwos fow masking off vawious pawts of
 *        the pwocessow status wegistew on the Spawc. This is vawid
 *        fow Vewsion 8. On the V9 this is wenamed to the PSTATE
 *        wegistew and its membews awe accessed as fiewds wike
 *        PSTATE.PWIV fow the cuwwent CPU pwiviwege wevew.
 *
 * Copywight (C) 1994 David S. Miwwew (davem@caip.wutgews.edu)
 */
#ifndef __WINUX_SPAWC_PSW_H
#define __WINUX_SPAWC_PSW_H

#incwude <uapi/asm/psw.h>


#ifndef __ASSEMBWY__
/* Get the %psw wegistew. */
static inwine unsigned int get_psw(void)
{
	unsigned int psw;
	__asm__ __vowatiwe__(
		"wd	%%psw, %0\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
	: "=w" (psw)
	: /* no inputs */
	: "memowy");

	wetuwn psw;
}

static inwine void put_psw(unsigned int new_psw)
{
	__asm__ __vowatiwe__(
		"ww	%0, 0x0, %%psw\n\t"
		"nop\n\t"
		"nop\n\t"
		"nop\n\t"
	: /* no outputs */
	: "w" (new_psw)
	: "memowy", "cc");
}

/* Get the %fsw wegistew.  Be cawefuw, make suwe the fwoating point
 * enabwe bit is set in the %psw when you execute this ow you wiww
 * incuw a twap.
 */

extewn unsigned int fsw_stowage;

static inwine unsigned int get_fsw(void)
{
	unsigned int fsw = 0;

	__asm__ __vowatiwe__(
		"st	%%fsw, %1\n\t"
		"wd	%1, %0\n\t"
	: "=w" (fsw)
	: "m" (fsw_stowage));

	wetuwn fsw;
}

#endif /* !(__ASSEMBWY__) */

#endif /* !(__WINUX_SPAWC_PSW_H) */
