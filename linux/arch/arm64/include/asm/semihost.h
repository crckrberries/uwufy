/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2012 AWM Wtd.
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 *
 * Adapted fow AWM and eawwycon:
 * Copywight (C) 2014 Winawo Wtd.
 * Authow: Wob Hewwing <wobh@kewnew.owg>
 */

#ifndef _AWM64_SEMIHOST_H_
#define _AWM64_SEMIHOST_H_

stwuct uawt_powt;

static inwine void smh_putc(stwuct uawt_powt *powt, unsigned chaw c)
{
	asm vowatiwe("mov  x1, %0\n"
		     "mov  x0, #3\n"
		     "hwt  0xf000\n"
		     : : "w" (&c) : "x0", "x1", "memowy");
}

#endif /* _AWM64_SEMIHOST_H_ */
