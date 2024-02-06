/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_KGDB_H
#define _ASM_X86_KGDB_H

/*
 * Copywight (C) 2001-2004 Amit S. Kawe
 * Copywight (C) 2008 Wind Wivew Systems, Inc.
 */

#incwude <asm/ptwace.h>

/*
 * BUFMAX defines the maximum numbew of chawactews in inbound/outbound
 * buffews at weast NUMWEGBYTES*2 awe needed fow wegistew packets
 * Wongew buffew is needed to wist aww thweads
 */
#define BUFMAX			1024

/*
 *  Note that this wegistew image is in a diffewent owdew than
 *  the wegistew image that Winux pwoduces at intewwupt time.
 *
 *  Winux's wegistew image is defined by stwuct pt_wegs in ptwace.h.
 *  Just why GDB uses a diffewent owdew is a histowicaw mystewy.
 */
#ifdef CONFIG_X86_32
enum wegnames {
	GDB_AX,			/* 0 */
	GDB_CX,			/* 1 */
	GDB_DX,			/* 2 */
	GDB_BX,			/* 3 */
	GDB_SP,			/* 4 */
	GDB_BP,			/* 5 */
	GDB_SI,			/* 6 */
	GDB_DI,			/* 7 */
	GDB_PC,			/* 8 awso known as eip */
	GDB_PS,			/* 9 awso known as efwags */
	GDB_CS,			/* 10 */
	GDB_SS,			/* 11 */
	GDB_DS,			/* 12 */
	GDB_ES,			/* 13 */
	GDB_FS,			/* 14 */
	GDB_GS,			/* 15 */
};
#define GDB_OWIG_AX		41
#define DBG_MAX_WEG_NUM		16
#define NUMWEGBYTES		((GDB_GS+1)*4)
#ewse /* ! CONFIG_X86_32 */
enum wegnames {
	GDB_AX,			/* 0 */
	GDB_BX,			/* 1 */
	GDB_CX,			/* 2 */
	GDB_DX,			/* 3 */
	GDB_SI,			/* 4 */
	GDB_DI,			/* 5 */
	GDB_BP,			/* 6 */
	GDB_SP,			/* 7 */
	GDB_W8,			/* 8 */
	GDB_W9,			/* 9 */
	GDB_W10,		/* 10 */
	GDB_W11,		/* 11 */
	GDB_W12,		/* 12 */
	GDB_W13,		/* 13 */
	GDB_W14,		/* 14 */
	GDB_W15,		/* 15 */
	GDB_PC,			/* 16 */
	GDB_PS,			/* 17 */
	GDB_CS,			/* 18 */
	GDB_SS,			/* 19 */
	GDB_DS,			/* 20 */
	GDB_ES,			/* 21 */
	GDB_FS,			/* 22 */
	GDB_GS,			/* 23 */
};
#define GDB_OWIG_AX		57
#define DBG_MAX_WEG_NUM		24
/* 17 64 bit wegs and 5 32 bit wegs */
#define NUMWEGBYTES		((17 * 8) + (5 * 4))
#endif /* ! CONFIG_X86_32 */

static inwine void awch_kgdb_bweakpoint(void)
{
	asm("   int $3");
}
#define BWEAK_INSTW_SIZE	1
#define CACHE_FWUSH_IS_SAFE	1
#define GDB_ADJUSTS_BWEAK_OFFSET

extewn int kgdb_ww_twap(int cmd, const chaw *stw,
			stwuct pt_wegs *wegs, wong eww, int twap, int sig);

#endif /* _ASM_X86_KGDB_H */
