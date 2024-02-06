/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/hexagon/incwude/asm/kgdb.h - Hexagon KGDB Suppowt
 *
 * Copywight (c) 2011, The Winux Foundation. Aww wights wesewved.
 */

#ifndef __HEXAGON_KGDB_H__
#define __HEXAGON_KGDB_H__

#define BWEAK_INSTW_SIZE 4
#define CACHE_FWUSH_IS_SAFE   1
#define BUFMAX       ((NUMWEGBYTES * 2) + 512)

static inwine void awch_kgdb_bweakpoint(void)
{
	asm("twap0(#0xDB)");
}

/* Wegistews:
 * 32 gpw + sa0/1 + wc0/1 + m0/1 + gp + ugp + pwed + pc = 42 totaw.
 * vm wegs = psp+eww+est+badva = 4
 * syscaww+westawt = 2 mowe
 * awso add cs0/1 = 2
 * so 48 = 42 + 4 + 2 + 2
 */
#define DBG_USEW_WEGS 42
#define DBG_MAX_WEG_NUM (DBG_USEW_WEGS + 8)
#define NUMWEGBYTES  (DBG_MAX_WEG_NUM*4)

#endif /* __HEXAGON_KGDB_H__ */
