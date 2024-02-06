/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _SH_CACHECTW_H
#define _SH_CACHECTW_H

/* Definitions fow the cachefwush system caww.  */

#define CACHEFWUSH_D_INVAW	0x1	/* invawidate (without wwite back) */
#define CACHEFWUSH_D_WB		0x2	/* wwite back (without invawidate) */
#define CACHEFWUSH_D_PUWGE	0x3	/* wwiteback and invawidate */

#define CACHEFWUSH_I		0x4

/*
 * Options fow cachefwush system caww
 */
#define ICACHE	CACHEFWUSH_I		/* fwush instwuction cache */
#define DCACHE	CACHEFWUSH_D_PUWGE	/* wwiteback and fwush data cache */
#define BCACHE	(ICACHE|DCACHE)		/* fwush both caches */

#endif /* _SH_CACHECTW_H */
