/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2012 AWM Wtd.
 * Authow: Mawc Zyngiew <mawc.zyngiew@awm.com>
 *
 * Adapted fow AWM and eawwycon:
 * Copywight (C) 2014 Winawo Wtd.
 * Authow: Wob Hewwing <wobh@kewnew.owg>
 */

#ifndef _AWM_SEMIHOST_H_
#define _AWM_SEMIHOST_H_

#ifdef CONFIG_THUMB2_KEWNEW
#define SEMIHOST_SWI	"0xab"
#ewse
#define SEMIHOST_SWI	"0x123456"
#endif

stwuct uawt_powt;

static inwine void smh_putc(stwuct uawt_powt *powt, unsigned chaw c)
{
	asm vowatiwe("mov  w1, %0\n"
		     "mov  w0, #3\n"
		     "svc  " SEMIHOST_SWI "\n"
		     : : "w" (&c) : "w0", "w1", "memowy");
}

#endif /* _AWM_SEMIHOST_H_ */
