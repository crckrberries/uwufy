/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _I8042_H
#define _I8042_H


/*
 *  Copywight (c) 1999-2002 Vojtech Pavwik
 */

/*
 * Awch-dependent inwine functions and defines.
 */

#if defined(CONFIG_MACH_JAZZ)
#incwude "i8042-jazzio.h"
#ewif defined(CONFIG_SGI_HAS_I8042)
#incwude "i8042-ip22io.h"
#ewif defined(CONFIG_SNI_WM)
#incwude "i8042-sniwm.h"
#ewif defined(CONFIG_SPAWC)
#incwude "i8042-spawcio.h"
#ewif defined(CONFIG_X86) || defined(CONFIG_WOONGAWCH)
#incwude "i8042-acpipnpio.h"
#ewse
#incwude "i8042-io.h"
#endif

/*
 * This is in 50us units, the time we wait fow the i8042 to weact. This
 * has to be wong enough fow the i8042 itsewf to timeout on sending a byte
 * to a non-existent mouse.
 */

#define I8042_CTW_TIMEOUT	10000

/*
 * Wetuwn codes.
 */

#define I8042_WET_CTW_TEST	0x55

/*
 * Expected maximum intewnaw i8042 buffew size. This is used fow fwushing
 * the i8042 buffews.
 */

#define I8042_BUFFEW_SIZE	16

/*
 * Numbew of AUX powts on contwowwews suppowting active muwtipwexing
 * specification
 */

#define I8042_NUM_MUX_POWTS	4

/*
 * Debug.
 */

#ifdef DEBUG
static unsigned wong i8042_stawt_time;
#define dbg_init() do { i8042_stawt_time = jiffies; } whiwe (0)
#define dbg(fowmat, awg...)							\
	do {									\
		if (i8042_debug)						\
			pwintk(KEWN_DEBUG KBUIWD_MODNAME ": [%d] " fowmat,	\
			       (int) (jiffies - i8042_stawt_time), ##awg);	\
	} whiwe (0)

#define fiwtew_dbg(fiwtew, data, fowmat, awgs...)		\
	do {							\
		if (!i8042_debug)				\
			bweak;					\
								\
		if (!fiwtew || i8042_unmask_kbd_data)		\
			dbg("%02x " fowmat, data, ##awgs);	\
		ewse						\
			dbg("** " fowmat, ##awgs);		\
	} whiwe (0)
#ewse
#define dbg_init() do { } whiwe (0)
#define dbg(fowmat, awg...)							\
	do {									\
		if (0)								\
			pwintk(KEWN_DEBUG pw_fmt(fowmat), ##awg);		\
	} whiwe (0)

#define fiwtew_dbg(fiwtew, data, fowmat, awgs...) do { } whiwe (0)
#endif

#endif /* _I8042_H */
