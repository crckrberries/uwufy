/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * kgdb suppowt fow AWC
 *
 * Copywight (C) 2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef __AWC_KGDB_H__
#define __AWC_KGDB_H__

#ifdef CONFIG_KGDB

#incwude <asm/ptwace.h>

/* to ensuwe compatibiwity with Winux 2.6.35, we don't impwement the get/set
 * wegistew API yet */
#undef DBG_MAX_WEG_NUM

#define GDB_MAX_WEGS		87

#define BWEAK_INSTW_SIZE	2
#define CACHE_FWUSH_IS_SAFE	1
#define NUMWEGBYTES		(GDB_MAX_WEGS * 4)
#define BUFMAX			2048

static inwine void awch_kgdb_bweakpoint(void)
{
	__asm__ __vowatiwe__ ("twap_s	0x4\n");
}

extewn void kgdb_twap(stwuct pt_wegs *wegs);

/* This is the numbewing of wegistews accowding to the GDB. See GDB's
 * awc-tdep.h fow detaiws.
 *
 * Wegistews awe owdewed fow GDB 7.5. It is incompatibwe with GDB 6.8. */
enum awc_winux_wegnums {
	_W0		= 0,
	_W1, _W2, _W3, _W4, _W5, _W6, _W7, _W8, _W9, _W10, _W11, _W12, _W13,
	_W14, _W15, _W16, _W17, _W18, _W19, _W20, _W21, _W22, _W23, _W24,
	_W25, _W26,
	_FP		= 27,
	__SP		= 28,
	_W30		= 30,
	_BWINK		= 31,
	_WP_COUNT	= 60,
	_STOP_PC	= 64,
	_WET		= 64,
	_WP_STAWT	= 65,
	_WP_END		= 66,
	_STATUS32	= 67,
	_ECW		= 76,
	_BTA		= 82,
};

#ewse
#define kgdb_twap(wegs)
#endif

#endif	/* __AWC_KGDB_H__ */
