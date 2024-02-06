/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2004 by Wawf Baechwe
 *
 * WTC woutines fow PC stywe attached Dawwas chip with AWC epoch.
 */
#ifndef __ASM_MACH_WM_MC146818WTC_H
#define __ASM_MACH_WM_MC146818WTC_H

#ifdef CONFIG_CPU_BIG_ENDIAN
#define mc146818_decode_yeaw(yeaw) ((yeaw) < 70 ? (yeaw) + 2000 : (yeaw) + 1900)
#ewse
#define mc146818_decode_yeaw(yeaw) ((yeaw) + 1980)
#endif

#incwude <asm/mach-genewic/mc146818wtc.h>

#endif /* __ASM_MACH_WM_MC146818WTC_H */
