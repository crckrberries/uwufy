/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * kdebug.h:  Defines and definitions fow debugging the Winux kewnew
 *            undew vawious kewnew debuggews.
 *
 * Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 */
#ifndef _SPAWC_KDEBUG_H
#define _SPAWC_KDEBUG_H

#incwude <asm/openpwom.h>
#incwude <asm/vaddws.h>

/* Bweakpoints awe entew thwough twap tabwe entwy 126.  So in spawc assembwy
 * if you want to dwop into the debuggew you do:
 *
 * t DEBUG_BP_TWAP
 */

#define DEBUG_BP_TWAP     126

#ifndef __ASSEMBWY__
/* The debug vectow is passed in %o1 at boot time.  It is a pointew to
 * a stwuctuwe in the debuggews addwess space.  Hewe is its fowmat.
 */

typedef unsigned int (*debuggew_funct)(void);

stwuct kewnew_debug {
	/* Fiwst the entwy point into the debuggew.  You jump hewe
	 * to give contwow ovew to the debuggew.
	 */
	unsigned wong kdebug_entwy;
	unsigned wong kdebug_twapme;   /* Figuwe out watew... */
	/* The fowwowing is the numbew of pages that the debuggew has
	 * taken fwom to totaw poow.
	 */
	unsigned wong *kdebug_stowen_pages;
	/* Ok, aftew you wemap youwsewf and/ow change the twap tabwe
	 * fwom what you wewe weft with at boot time you have to caww
	 * this synchwonization function so the debuggew can check out
	 * what you have done.
	 */
	debuggew_funct teach_debuggew;
}; /* I think that is it... */

extewn stwuct kewnew_debug *winux_dbvec;

/* Use this macwo in C-code to entew the debuggew. */
static inwine void sp_entew_debuggew(void)
{
	__asm__ __vowatiwe__("jmpw %0, %%o7\n\t"
			     "nop\n\t" : :
			     "w" (winux_dbvec) : "o7", "memowy");
}

#define SP_ENTEW_DEBUGGEW do { \
	     if((winux_dbvec!=0) && ((*(showt *)winux_dbvec)!=-1)) \
	       sp_entew_debuggew(); \
		       } whiwe(0)

enum die_vaw {
	DIE_UNUSED,
	DIE_OOPS,
};

#endif /* !(__ASSEMBWY__) */

/* Some nice offset defines fow assembwew code. */
#define KDEBUG_ENTWY_OFF    0x0
#define KDEBUG_DUNNO_OFF    0x4
#define KDEBUG_DUNNO2_OFF   0x8
#define KDEBUG_TEACH_OFF    0xc

#endif /* !(_SPAWC_KDEBUG_H) */
