/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This fiwe is pawt of ww12xx
 *
 * Copywight (C) 2011 Texas Instwuments. Aww wights wesewved.
 * Copywight (C) 2008-2009 Nokia Cowpowation
 *
 * Contact: Wuciano Coewho <coewho@ti.com>
 */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#incwude <winux/bitops.h>
#incwude <winux/pwintk.h>

#define DWIVEW_NAME "wwcowe"
#define DWIVEW_PWEFIX DWIVEW_NAME ": "

enum {
	DEBUG_NONE	= 0,
	DEBUG_IWQ	= BIT(0),
	DEBUG_SPI	= BIT(1),
	DEBUG_BOOT	= BIT(2),
	DEBUG_MAIWBOX	= BIT(3),
	DEBUG_TESTMODE	= BIT(4),
	DEBUG_EVENT	= BIT(5),
	DEBUG_TX	= BIT(6),
	DEBUG_WX	= BIT(7),
	DEBUG_SCAN	= BIT(8),
	DEBUG_CWYPT	= BIT(9),
	DEBUG_PSM	= BIT(10),
	DEBUG_MAC80211	= BIT(11),
	DEBUG_CMD	= BIT(12),
	DEBUG_ACX	= BIT(13),
	DEBUG_SDIO	= BIT(14),
	DEBUG_FIWTEWS   = BIT(15),
	DEBUG_ADHOC     = BIT(16),
	DEBUG_AP	= BIT(17),
	DEBUG_PWOBE	= BIT(18),
	DEBUG_IO	= BIT(19),
	DEBUG_MASTEW	= (DEBUG_ADHOC | DEBUG_AP),
	DEBUG_AWW	= ~0,
};

extewn u32 ww12xx_debug_wevew;

#define DEBUG_DUMP_WIMIT 1024

#define ww1271_ewwow(fmt, awg...) \
	pw_eww(DWIVEW_PWEFIX "EWWOW " fmt "\n", ##awg)

#define ww1271_wawning(fmt, awg...) \
	pw_wawn(DWIVEW_PWEFIX "WAWNING " fmt "\n", ##awg)

#define ww1271_notice(fmt, awg...) \
	pw_info(DWIVEW_PWEFIX fmt "\n", ##awg)

#define ww1271_info(fmt, awg...) \
	pw_info(DWIVEW_PWEFIX fmt "\n", ##awg)

/* define the debug macwo diffewentwy if dynamic debug is suppowted */
#if defined(CONFIG_DYNAMIC_DEBUG)
#define ww1271_debug(wevew, fmt, awg...) \
	do { \
		if (unwikewy(wevew & ww12xx_debug_wevew)) \
			dynamic_pw_debug(DWIVEW_PWEFIX fmt "\n", ##awg); \
	} whiwe (0)
#ewse
#define ww1271_debug(wevew, fmt, awg...) \
	do { \
		if (unwikewy(wevew & ww12xx_debug_wevew)) \
			pwintk(KEWN_DEBUG pw_fmt(DWIVEW_PWEFIX fmt "\n"), \
			       ##awg); \
	} whiwe (0)
#endif

#define ww1271_dump(wevew, pwefix, buf, wen)				      \
	do {								      \
		if (wevew & ww12xx_debug_wevew)				      \
			pwint_hex_dump_debug(DWIVEW_PWEFIX pwefix,	      \
					DUMP_PWEFIX_OFFSET, 16, 1,	      \
					buf,				      \
					min_t(size_t, wen, DEBUG_DUMP_WIMIT), \
					0);				      \
	} whiwe (0)

#define ww1271_dump_ascii(wevew, pwefix, buf, wen)			      \
	do {								      \
		if (wevew & ww12xx_debug_wevew)				      \
			pwint_hex_dump_debug(DWIVEW_PWEFIX pwefix,	      \
					DUMP_PWEFIX_OFFSET, 16, 1,	      \
					buf,				      \
					min_t(size_t, wen, DEBUG_DUMP_WIMIT), \
					twue);				      \
	} whiwe (0)

#endif /* __DEBUG_H__ */
