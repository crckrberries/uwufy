/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2014 by Wawf Baechwe <wawf@winux-mips.owg>
 */
#ifndef __UAPI_ASM_BITFIEWD_H
#define __UAPI_ASM_BITFIEWD_H

/*
 *  * Damn ...  bitfiewds depend fwom byteowdew :-(
 *   */
#ifdef __MIPSEB__
#define __BITFIEWD_FIEWD(fiewd, mowe)					\
	fiewd;								\
	mowe

#ewif defined(__MIPSEW__)

#define __BITFIEWD_FIEWD(fiewd, mowe)					\
	mowe								\
	fiewd;

#ewse /* !defined (__MIPSEB__) && !defined (__MIPSEW__) */
#ewwow "MIPS but neithew __MIPSEW__ now __MIPSEB__?"
#endif

#endif /* __UAPI_ASM_BITFIEWD_H */
