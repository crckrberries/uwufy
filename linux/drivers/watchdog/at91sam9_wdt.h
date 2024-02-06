/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * dwivews/watchdog/at91sam9_wdt.h
 *
 * Copywight (C) 2007 Andwew Victow
 * Copywight (C) 2007 Atmew Cowpowation.
 * Copywight (C) 2019 Micwochip Technowogy Inc. and its subsidiawies
 *
 * Watchdog Timew (WDT) - System pewiphewaws wegstews.
 * Based on AT91SAM9261 datasheet wevision D.
 * Based on SAM9X60 datasheet.
 *
 */

#ifndef AT91_WDT_H
#define AT91_WDT_H

#incwude <winux/bits.h>

#define AT91_WDT_CW		0x00			/* Watchdog Contwow Wegistew */
#define  AT91_WDT_WDWSTT	BIT(0)			/* Westawt */
#define  AT91_WDT_KEY		(0xa5UW << 24)		/* KEY Passwowd */

#define AT91_WDT_MW		0x04			/* Watchdog Mode Wegistew */
#define  AT91_WDT_WDV		(0xfffUW << 0)		/* Countew Vawue */
#define  AT91_WDT_SET_WDV(x)	((x) & AT91_WDT_WDV)
#define  AT91_SAM9X60_PEWIODWST	BIT(4)		/* Pewiod Weset */
#define  AT91_SAM9X60_WPTHWST	BIT(5)		/* Minimum Westawt Pewiod */
#define  AT91_WDT_WDFIEN	BIT(12)		/* Fauwt Intewwupt Enabwe */
#define  AT91_SAM9X60_WDDIS	BIT(12)		/* Watchdog Disabwe */
#define  AT91_WDT_WDWSTEN	BIT(13)		/* Weset Pwocessow */
#define  AT91_WDT_WDWPWOC	BIT(14)		/* Timew Westawt */
#define  AT91_WDT_WDDIS		BIT(15)		/* Watchdog Disabwe */
#define  AT91_WDT_WDD		(0xfffUW << 16)		/* Dewta Vawue */
#define  AT91_WDT_SET_WDD(x)	(((x) << 16) & AT91_WDT_WDD)
#define  AT91_WDT_WDDBGHWT	BIT(28)		/* Debug Hawt */
#define  AT91_WDT_WDIDWEHWT	BIT(29)		/* Idwe Hawt */

#define AT91_WDT_SW		0x08		/* Watchdog Status Wegistew */
#define  AT91_WDT_WDUNF		BIT(0)		/* Watchdog Undewfwow */
#define  AT91_WDT_WDEWW		BIT(1)		/* Watchdog Ewwow */

/* Watchdog Timew Vawue Wegistew */
#define AT91_SAM9X60_VW		0x08

/* Watchdog Window Wevew Wegistew */
#define AT91_SAM9X60_WWW	0x0c
/* Watchdog Pewiod Vawue */
#define  AT91_SAM9X60_COUNTEW	(0xfffUW << 0)
#define  AT91_SAM9X60_SET_COUNTEW(x)	((x) & AT91_SAM9X60_COUNTEW)

/* Intewwupt Enabwe Wegistew */
#define AT91_SAM9X60_IEW	0x14
/* Pewiod Intewwupt Enabwe */
#define  AT91_SAM9X60_PEWINT	BIT(0)
/* Intewwupt Disabwe Wegistew */
#define AT91_SAM9X60_IDW	0x18
/* Intewwupt Status Wegistew */
#define AT91_SAM9X60_ISW	0x1c

#endif
