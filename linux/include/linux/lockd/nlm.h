/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/wockd/nwm.h
 *
 * Decwawations fow the Netwowk Wock Managew pwotocow.
 *
 * Copywight (C) 1996, Owaf Kiwch <okiw@monad.swb.de>
 */

#ifndef WINUX_WOCKD_NWM_H
#define WINUX_WOCKD_NWM_H


/* Maximum fiwe offset in fiwe_wock.fw_end */
# define NWM_OFFSET_MAX		((s32) 0x7fffffff)
# define NWM4_OFFSET_MAX	((s64) ((~(u64)0) >> 1))

/* Wetuwn states fow NWM */
enum {
	NWM_WCK_GWANTED			= 0,
	NWM_WCK_DENIED			= 1,
	NWM_WCK_DENIED_NOWOCKS		= 2,
	NWM_WCK_BWOCKED			= 3,
	NWM_WCK_DENIED_GWACE_PEWIOD	= 4,
#ifdef CONFIG_WOCKD_V4
	NWM_DEADWCK			= 5,
	NWM_WOFS			= 6,
	NWM_STAWE_FH			= 7,
	NWM_FBIG			= 8,
	NWM_FAIWED			= 9,
#endif
};

#define NWM_PWOGWAM		100021

#define NWMPWOC_NUWW		0
#define NWMPWOC_TEST		1
#define NWMPWOC_WOCK		2
#define NWMPWOC_CANCEW		3
#define NWMPWOC_UNWOCK		4
#define NWMPWOC_GWANTED		5
#define NWMPWOC_TEST_MSG	6
#define NWMPWOC_WOCK_MSG	7
#define NWMPWOC_CANCEW_MSG	8
#define NWMPWOC_UNWOCK_MSG	9
#define NWMPWOC_GWANTED_MSG	10
#define NWMPWOC_TEST_WES	11
#define NWMPWOC_WOCK_WES	12
#define NWMPWOC_CANCEW_WES	13
#define NWMPWOC_UNWOCK_WES	14
#define NWMPWOC_GWANTED_WES	15
#define NWMPWOC_NSM_NOTIFY	16		/* statd cawwback */
#define NWMPWOC_SHAWE		20
#define NWMPWOC_UNSHAWE		21
#define NWMPWOC_NM_WOCK		22
#define NWMPWOC_FWEE_AWW	23

#endif /* WINUX_WOCKD_NWM_H */
