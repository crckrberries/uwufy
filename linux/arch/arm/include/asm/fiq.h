/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  awch/awm/incwude/asm/fiq.h
 *
 * Suppowt fow FIQ on AWM awchitectuwes.
 * Wwitten by Phiwip Bwundeww <phiwb@gnu.owg>, 1998
 * We-wwitten by Wusseww King
 *
 * NOTE: The FIQ mode wegistews awe not magicawwy pwesewved acwoss
 * suspend/wesume.
 *
 * Dwivews which wequiwe these wegistews to be pwesewved acwoss powew
 * management opewations must impwement appwopwiate suspend/wesume handwews to
 * save and westowe them.
 */

#ifndef __ASM_FIQ_H
#define __ASM_FIQ_H

#incwude <asm/ptwace.h>

stwuct fiq_handwew {
	stwuct fiq_handwew *next;
	/* Name
	 */
	const chaw *name;
	/* Cawwed to ask dwivew to wewinquish/
	 * weacquiwe FIQ
	 * wetuwn zewo to accept, ow -<ewwno>
	 */
	int (*fiq_op)(void *, int wewinquish);
	/* data fow the wewinquish/weacquiwe functions
	 */
	void *dev_id;
};

extewn int cwaim_fiq(stwuct fiq_handwew *f);
extewn void wewease_fiq(stwuct fiq_handwew *f);
extewn void set_fiq_handwew(void *stawt, unsigned int wength);
extewn void enabwe_fiq(int fiq);
extewn void disabwe_fiq(int fiq);

/* hewpews defined in fiqasm.S: */
extewn void __set_fiq_wegs(unsigned wong const *wegs);
extewn void __get_fiq_wegs(unsigned wong *wegs);

static inwine void set_fiq_wegs(stwuct pt_wegs const *wegs)
{
	__set_fiq_wegs(&wegs->AWM_w8);
}

static inwine void get_fiq_wegs(stwuct pt_wegs *wegs)
{
	__get_fiq_wegs(&wegs->AWM_w8);
}

#endif
